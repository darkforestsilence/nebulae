// Copyright (c) 2003-2018 RCH3 (nebulae@nebulae.online)
// Copyright (c) 2019 Nebulae Foundation, LLC. All rights reserved.
// Copyright (c) 2006 - 2008, Intel Corporation. All rights reserved.
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

#ifndef __K0_X64_MMIO_H
#define __K0_X64_MMIO_H

UINT64 EFIAPI IoRead64(IN UINTN Port);
UINT64 EFIAPI IoWrite64(IN UINTN Port, IN UINT64 Value);
UINT8  EFIAPI MmioRead8(IN UINTN Address);
UINT8  EFIAPI MmioWrite8(IN UINTN Address, IN UINT8 Value);
UINT16 EFIAPI MmioRead16(IN UINTN Address);
UINT16 EFIAPI MmioWrite16(IN UINTN Address, IN UINT16 Value);
UINT32 EFIAPI MmioRead32(IN UINTN Address);
UINT32 EFIAPI MmioWrite32(IN UINTN Address, IN UINT32 Value);
UINT64 EFIAPI MmioRead64(IN UINTN Address);
UINT64 EFIAPI MmioWrite64(IN UINTN Address, IN UINT64 Value);

#endif // __K0_X64_MMIO_H
