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

#ifndef X64_H
#define X64_H

// Helpful constants
#define X64_REG_EAX                 0x00
#define X64_REG_EBX                 0x01
#define X64_REG_ECX                 0x02
#define X64_REG_EDX                 0x03

// cpuinfo results structure
// cpuinfo returns its results in each
// of eax, ebx, ecx & edx depending upon
// the leaf function specified
typedef struct s_x64_cpuinfo_results {
    UINT32 reg[4];
} x64_cpuinfo_results;

// x64 cpu structure
// cpuinfo [0..2] is for cpuid
// cpuinfo [3..10] is for cpuidex
typedef struct s_x64_cpu {
    UINT32 max_cpuid_eax;
    UINT32 max_cpuidex_eax;
    x64_cpuinfo_results cpuinfo[11];
} x64_cpu;

// cpu struct
extern x64_cpu cpu;

// Function prototypes
void InitArchCPU(void);

#define X64_CPUID_0x00              0x0000000000000000ULL
#define X64_CPUID_0x01              0x0000000100000000ULL
#define X64_CPUID_0x02              0x0000000200000000ULL
#define X64_CPUID_0x03              0x0000000300000000ULL
#define X64_CPUID_0x04              0x0000000400000000ULL
#define X64_CPUID_0x05              0x0000000500000000ULL
#define X64_CPUID_0x06              0x0000000600000000ULL
#define X64_CPUID_0x07              0x0000000700000000ULL
#define X64_CPUID_0x08              0x0000000800000000ULL
#define X64_CPUID_0x09              0x0000000900000000ULL
#define X64_CPUID_0x0A              0x0000000A00000000ULL
#define X64_CPUID_MASK              0x0000000F00000000ULL

#define X64_CPUID_EAX               0x0000000000000000ULL
#define X64_CPUID_EBX               0x0000001000000000ULL
#define X64_CPUID_ECX               0x0000002000000000ULL
#define X64_CPUID_EDX               0x0000003000000000ULL
#define X64_CPUID_REG_MASK          0x000000F000000000ULL

#define X64_HAS_SSE3                ((UINT64)BIT0 | X64_CPUID_0x01 | X64_CPUID_ECX)
#define X64_HAS_PCLMULQDQ           ((UINT64)BIT1 | X64_CPUID_0x01 | X64_CPUID_ECX)
#define X64_HAS_DTES64              ((UINT64)BIT2 | X64_CPUID_0x01 | X64_CPUID_ECX)
#define X64_HAS_MONITOR             ((UINT64)BIT3 | X64_CPUID_0x01 | X64_CPUID_ECX)
#define X64_HAS_CPLDEBUGSTORE       ((UINT64)BIT4 | X64_CPUID_0x01 | X64_CPUID_ECX)
#define X64_HAS_VMX                 ((UINT64)BIT5 | X64_CPUID_0x01 | X64_CPUID_ECX)
#define X64_HAS_SMX                 ((UINT64)BIT6 | X64_CPUID_0x01 | X64_CPUID_ECX)
#define X64_HAS_SPEEDSTEP           ((UINT64)BIT7 | X64_CPUID_0x01 | X64_CPUID_ECX)
#define X64_HAS_THERMALMONITOR2     ((UINT64)BIT8 | X64_CPUID_0x01 | X64_CPUID_ECX)
#define X64_HAS_SSSE3               ((UINT64)BIT9 | X64_CPUID_0x01 | X64_CPUID_ECX)
#define X64_HAS_L1CONTEXTID         ((UINT64)BIT10 | X64_CPUID_0x01 | X64_CPUID_ECX)
#define X64_HAS_SILICONDEBUG        ((UINT64)BIT11 | X64_CPUID_0x01 | X64_CPUID_ECX)
#define X64_HAS_FMA                 ((UINT64)BIT12 | X64_CPUID_0x01 | X64_CPUID_ECX)
#define X64_HAS_CMPXCHG16B          ((UINT64)BIT13 | X64_CPUID_0x01 | X64_CPUID_ECX)
#define X64_HAS_TPRUPDATECONTROL    ((UINT64)BIT14 | X64_CPUID_0x01 | X64_CPUID_ECX)
#define X64_HAS_PDCM                ((UINT64)BIT15 | X64_CPUID_0x01 | X64_CPUID_ECX)
#define X64_HAS_PCID                ((UINT64)BIT17 | X64_CPUID_0x01 | X64_CPUID_ECX)
#define X64_HAS_DCA                 ((UINT64)BIT18 | X64_CPUID_0x01 | X64_CPUID_ECX)
#define X64_HAS_SSE41               ((UINT64)BIT19 | X64_CPUID_0x01 | X64_CPUID_ECX)
#define X64_HAS_SSE42               ((UINT64)BIT20 | X64_CPUID_0x01 | X64_CPUID_ECX)
#define X64_HAS_X2APIC              ((UINT64)BIT21 | X64_CPUID_0x01 | X64_CPUID_ECX)
#define X64_HAS_MOVBE               ((UINT64)BIT22 | X64_CPUID_0x01 | X64_CPUID_ECX)
#define X64_HAS_POPCNT              ((UINT64)BIT23 | X64_CPUID_0x01 | X64_CPUID_ECX)
#define X64_HAS_TSCDEADLINE         ((UINT64)BIT24 | X64_CPUID_0x01 | X64_CPUID_ECX)
#define X64_HAS_AESNI               ((UINT64)BIT25 | X64_CPUID_0x01 | X64_CPUID_ECX)
#define X64_HAS_XSAVE               ((UINT64)BIT26 | X64_CPUID_0x01 | X64_CPUID_ECX)
#define X64_HAS_OSXSAVE             ((UINT64)BIT27 | X64_CPUID_0x01 | X64_CPUID_ECX)
#define X64_HAS_AVX                 ((UINT64)BIT28 | X64_CPUID_0x01 | X64_CPUID_ECX)
#define X64_HAS_F16C                ((UINT64)BIT29 | X64_CPUID_0x01 | X64_CPUID_ECX)
#define X64_HAS_RDRAND              ((UINT64)BIT30 | X64_CPUID_0x01 | X64_CPUID_ECX)
#define X64_HAS_FPU                 ((UINT64)BIT0 | X64_CPUID_0x01 | X64_CPUID_EDX)
#define X64_HAS_V8086               ((UINT64)BIT1 | X64_CPUID_0x01 | X64_CPUID_EDX)
#define X64_HAS_DEBUG               ((UINT64)BIT2 | X64_CPUID_0x01 | X64_CPUID_EDX)
#define X64_HAS_PSE                 ((UINT64)BIT3 | X64_CPUID_0x01 | X64_CPUID_EDX)
#define X64_HAS_RDTSC               ((UINT64)BIT4 | X64_CPUID_0x01 | X64_CPUID_EDX)
#define X64_HAS_MSR                 ((UINT64)BIT5 | X64_CPUID_0x01 | X64_CPUID_EDX)
#define X64_HAS_PAE                 ((UINT64)BIT6 | X64_CPUID_0x01 | X64_CPUID_EDX)
#define X64_HAS_MACHINECHECKEXCEPTION ((UINT64)BIT7 | X64_CPUID_0x01 | X64_CPUID_EDX)
#define X64_HAS_CMPXCHG8B           ((UINT64)BIT8 | X64_CPUID_0x01 | X64_CPUID_EDX)
#define X64_HAS_APIC                ((UINT64)BIT9 | X64_CPUID_0x01 | X64_CPUID_EDX)
#define X64_HAS_SYSENTER            ((UINT64)BIT11 | X64_CPUID_0x01 | X64_CPUID_EDX)
#define X64_HAS_MTRR                ((UINT64)BIT12 | X64_CPUID_0x01 | X64_CPUID_EDX)
#define X64_HAS_PGE                 ((UINT64)BIT13 | X64_CPUID_0x01 | X64_CPUID_EDX)
#define X64_HAS_MACHINECHECKARCHITECTURE ((UINT64)BIT14 | X64_CPUID_0x01 | X64_CPUID_EDX)
#define X64_HAS_CMOV                ((UINT64)BIT15 | X64_CPUID_0x01 | X64_CPUID_EDX)
#define X64_HAS_PAT                 ((UINT64)BIT16 | X64_CPUID_0x01 | X64_CPUID_EDX)
#define X64_HAS_PSE36               ((UINT64)BIT17 | X64_CPUID_0x01 | X64_CPUID_EDX)
#define X64_HAS_PSN                 ((UINT64)BIT18 | X64_CPUID_0x01 | X64_CPUID_EDX)
#define X64_HAS_CLFLUSH             ((UINT64)BIT19 | X64_CPUID_0x01 | X64_CPUID_EDX)
#define X64_HAS_DEBUGSTORE          ((UINT64)BIT21 | X64_CPUID_0x01 | X64_CPUID_EDX)
#define X64_HAS_ACPI                ((UINT64)BIT22 | X64_CPUID_0x01 | X64_CPUID_EDX)
#define X64_HAS_MMX                 ((UINT64)BIT23 | X64_CPUID_0x01 | X64_CPUID_EDX)
#define X64_HAS_FXSAVE              ((UINT64)BIT24 | X64_CPUID_0x01 | X64_CPUID_EDX)
#define X64_HAS_SSE                 ((UINT64)BIT25 | X64_CPUID_0x01 | X64_CPUID_EDX)
#define X64_HAS_SSE2                ((UINT64)BIT26 | X64_CPUID_0x01 | X64_CPUID_EDX)
#define X64_HAS_SELFSNOOP           ((UINT64)BIT27 | X64_CPUID_0x01 | X64_CPUID_EDX)
#define X64_HAS_HYPERTHREADING      ((UINT64)BIT28 | X64_CPUID_0x01 | X64_CPUID_EDX)
#define X64_HAS_THERMALMONITOR      ((UINT64)BIT29 | X64_CPUID_0x01 | X64_CPUID_EDX)
#define X64_HAS_PBE                 ((UINT64)BIT31 | X64_CPUID_0x01 | X64_CPUID_EDX)

BOOLEAN ReadCpuinfoFlag(UINT64 flag);

#endif /* X64_H */