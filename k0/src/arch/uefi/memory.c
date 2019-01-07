// Copyright (c) 2018-2019 Nebulae Foundation. All rights reserved.
//
// Redistribution and use in source and binary forms, with or without 
// modification, are permitted provided that the following conditions are met:
// 
// 1. Redistributions of source code must retain the above copyright notice, 
// this list of conditions and the following disclaimer.
// 
// 2. Redistributions in binary form must reproduce the above copyright notice, 
// this list of conditions and the following disclaimer in the documentation 
// and/or other materials provided with the distribution.
// 
// 3. Neither the name of the copyright holder nor the names of its contributors 
// may be used to endorse or promote products derived from this software without 
// specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE 
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
// POSSIBILITY OF SUCH DAMAGE.

// Basic UEFI Libraries
#include <Library/UefiLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>

// Boot and Runtime Services
#include <Library/UefiBootServicesTableLib.h>

// Kernel Headers
#include "../../include/k0.h"
#include "../../include/deps/isaac64.h"

// Uefi Memory Header
#include "../../include/arch/uefi/memory.h"

// Architecure Specific Headers
#ifdef __NEBULAE_ARCH_X64
#include "../../include/arch/x64/x64.h"
#endif

// Memory Type Strings
const CHAR16 *EFI_MEMORY_TYPES[] = {
    L"Reserved",
    L"Loader Code",
    L"Loader Data",
    L"Boot Services Code",
    L"Boot Services Data",
    L"Runtime Services Code",
    L"Runtime Services Data",
    L"Conventional Memory",
    L"Unusable Memory",
    L"ACPI Reclaim Memory",
    L"ACPI Memory NVS",
    L"Memory Mapped I/O",
    L"Memory Mapped I/O Port Space",
    L"Pal Code",
    L"Persistent Memory"
};

#define EFI_MEMORY_RESERVED             0x00
#define EFI_MEMORY_LOADERCODE           0x01
#define EFI_MEMORY_LOADERDATA           0x02
#define EFI_MEMORY_BSCODE               0x03
#define EFI_MEMORY_BSDATA               0x04
#define EFI_MEMORY_RSCODE               0x05
#define EFI_MEMORY_RSDATA               0x06
#define EFI_MEMORY_CONVENTIONAL         0x07
#define EFI_MEMORY_UNUSUABLE            0x08
#define EFI_MEMORY_ACPIRECLAIM          0x09
#define EFI_MEMORY_ACPINVS              0x0A
#define EFI_MEMORY_MMIO                 0x0B
#define EFI_MEMORY_MMIOPORT             0x0C
#define EFI_MEMORY_PAL                  0x0D
#define EFI_MEMORY_PERSISTENT           0x0E

// Memory Subsystem Vars 
UINTN kmem_conventional_pages = 0;
VOID* kmem_largest_block = NULL;
UINTN kmem_largest_block_size = 0;
UINTN kmem_largest_block_page_count = 0;

//
// Initialize the memory subsystem by performing the following tasks:
// 
//  1) Read UEFI memmap to obtain size of memory map
//  2) Allocate a buffer large enough to hold the memory map
//  3) Calculate the number of free conventional memory pages, along
//      with the size and location of the largest block of free
//      conventional memory
//  4) Query the UEFI memmap again
UINTN InitMemSubsystem() {
    
    // Function exit status
    EFI_STATUS exit_status = EFI_SUCCESS;
    
    // Vars required for BootServices->GetMemoryMap call
    EFI_STATUS memmap_status = EFI_SUCCESS;
    memmap.size = 0;
    memmap.key = 0;
    memmap.descr_size = 0;
    memmap.descr_version = 0;
    
    // Call GetMemoryMap first with a NULL pointer to get the (rough) size of the memory map
    memmap_status = gBS->GetMemoryMap(&memmap.size, 
        NULL, 
        &memmap.key, 
        &memmap.descr_size, 
        &memmap.descr_version);

    // Check for an error, but make sure that error is simply that the buffer
    // wasn't too small, because it was.
    if (EFI_ERROR(memmap_status) && memmap_status != EFI_BUFFER_TOO_SMALL) {
        kernel_panic(L"Unable to query UEFI for memory map size: %r\n", memmap_status);
    }

    if (k0_VERBOSE_DEBUG) {
        Print(L"Map Size: %lu, Map Key: %lu, Desc. Size: %lu, Desc. Version: %u\n",
            memmap.size, memmap.key, memmap.descr_size, memmap.descr_version);
    }

    // Allocate enough memory to hold a temporary copy of the memory map
    memmap.page_count = (memmap.size / EFI_PAGE_SIZE) + 1;
    memmap.memory_map = (EFI_MEMORY_DESCRIPTOR*)AllocatePages(memmap.page_count);
    if (memmap.memory_map == NULL) {
        kernel_panic(L"Unable to allocate pages for memory map\n");
    }

    if (k0_VERBOSE_DEBUG) {
        Print(L"Allocated %u page(s)\n", memmap.page_count);
    }

    // Call GetMemoryMap again to get the actual memory map
    memmap_status = gBS->GetMemoryMap(&memmap.size, 
        memmap.memory_map, 
        &memmap.key, 
        &memmap.descr_size, 
        &memmap.descr_version);

    if (EFI_ERROR(memmap_status)) {
        kernel_panic(L"Unable to query UEFI for memory map: %r\n", memmap_status);
    }

    // Parse the UEFI memory map in order to count the available
    // conventional memory
    EFI_MEMORY_DESCRIPTOR *memmap_entry = NULL;
    UINT64 memmap_entries = memmap.size / memmap.descr_size;
    VOID *memmap_iter = memmap.memory_map;

    UINTN i;
    for (i = 0; i < memmap_entries; i++) {
        memmap_entry = (EFI_MEMORY_DESCRIPTOR *)memmap_iter;
        if (memmap_entry->Type == EFI_MEMORY_CONVENTIONAL ||
            memmap_entry->Type == EFI_MEMORY_BSCODE ||
            memmap_entry->Type == EFI_MEMORY_BSDATA) {
            kmem_conventional_pages += memmap_entry->NumberOfPages;
            if (k0_VERBOSE_DEBUG) {
                Print(L"T: %s, P: %lu, V: %lu, #: %lu, A: %lx\n",
                    EFI_MEMORY_TYPES[memmap_entry->Type], memmap_entry->PhysicalStart, memmap_entry->VirtualStart,
                    memmap_entry->NumberOfPages, memmap_entry->Attribute);
            }
            if (memmap_entry->NumberOfPages > kmem_largest_block_page_count) {
                kmem_largest_block_page_count = memmap_entry->NumberOfPages;
                kmem_largest_block_size = kmem_largest_block_page_count * EFI_PAGE_SIZE;
                kmem_largest_block = (VOID*)memmap_entry->PhysicalStart;
            }
        }

        memmap_iter = (CHAR8*)memmap_iter + memmap.descr_size;
    }

    if (k0_VERBOSE_DEBUG) {
        Print(L"Pages of Conventional Memory: %lu\n", kmem_conventional_pages);
        Print(L"Largest Block: %lu\n", kmem_largest_block);
        Print(L"Largest Block Size: %lu\n", kmem_largest_block_size);
        Print(L"Largest Block Page Count: %lu\n", kmem_largest_block_page_count);
        Print(L"Memory subsystem initialized\n");
    }

    return memmap.key;
}

// De-initialize the memory subsystem
void ShutdownMemSubsystem() {
    FreePages(memmap.memory_map, memmap.page_count);

    if (k0_VERBOSE_DEBUG) {
        Print(L"Freed %lu pages of memory @ %x\n", memmap.page_count, memmap.memory_map);
        Print(L"Memory subsystem shutdown\n", kmem_largest_block);
    }
}
