/** @file
  MemoryExample.c -- Memory allocation and memory map demonstration.

  Demonstrates:
    - AllocatePool / FreePool
    - AllocatePages / FreePages
    - GetMemoryMap and interpreting memory descriptors

  Copyright (c) 2026, UEFI Mu Guide Contributors. All rights reserved.
  SPDX-License-Identifier: BSD-2-Clause-Patent
**/

#include <UefiMuGuide.h>

//
// Readable names for EFI memory types.
//
STATIC CONST CHAR16  *mMemTypeNames[] = {
  L"Reserved",       L"LoaderCode",     L"LoaderData",
  L"BootServCode",   L"BootServData",   L"RuntimeCode",
  L"RuntimeData",    L"Conventional",   L"Unusable",
  L"ACPIReclaim",    L"ACPINvs",        L"MemMapIO",
  L"MemMapIOPort",   L"PalCode",        L"Persistent"
};

/**
  Print a human-readable memory type name.
**/
STATIC
CONST CHAR16 *
MemTypeName (
  IN UINT32  Type
  )
{
  if (Type < ARRAY_SIZE (mMemTypeNames)) {
    return mMemTypeNames[Type];
  }

  return L"Unknown";
}

/**
  Demonstrate pool (heap) allocation.
**/
STATIC
VOID
DemoPoolAllocation (
  VOID
  )
{
  EFI_STATUS  Status;
  VOID        *Buffer;
  UINTN       Size;

  Size = 256;
  Print (L"[Pool] Allocating %u bytes...\n", Size);

  Status = gBS->AllocatePool (EfiLoaderData, Size, &Buffer);
  CHECK_STATUS (Status, "AllocatePool");
  if (EFI_ERROR (Status)) {
    return;
  }

  Print (L"  Buffer at 0x%p\n", Buffer);

  //
  // Write and read back to verify.
  //
  SetMem (Buffer, Size, 0xAB);
  Print (L"  Filled with 0xAB -- first byte = 0x%02X\n",
         *((UINT8 *)Buffer));

  gBS->FreePool (Buffer);
  Print (L"  Freed.\n\n");
}

/**
  Demonstrate page allocation.
**/
STATIC
VOID
DemoPageAllocation (
  VOID
  )
{
  EFI_STATUS            Status;
  EFI_PHYSICAL_ADDRESS  Address;
  UINTN                 PageCount;

  PageCount = 4;  // 16 KiB
  Print (L"[Pages] Allocating %u pages (%u bytes)...\n",
         PageCount, PAGES_TO_BYTES (PageCount));

  Status = gBS->AllocatePages (AllocateAnyPages, EfiLoaderData,
                               PageCount, &Address);
  CHECK_STATUS (Status, "AllocatePages");
  if (EFI_ERROR (Status)) {
    return;
  }

  Print (L"  Pages at 0x%lX\n", Address);

  gBS->FreePages (Address, PageCount);
  Print (L"  Freed.\n\n");
}

/**
  Retrieve and summarize the memory map.
**/
STATIC
VOID
DemoMemoryMap (
  VOID
  )
{
  EFI_STATUS             Status;
  UINTN                  MemMapSize;
  EFI_MEMORY_DESCRIPTOR  *MemMap;
  UINTN                  MapKey;
  UINTN                  DescSize;
  UINT32                 DescVersion;
  UINTN                  EntryCount;
  UINTN                  Index;
  EFI_MEMORY_DESCRIPTOR  *Desc;
  UINT64                 TotalPages;

  //
  // First call: get the required buffer size.
  //
  MemMapSize = 0;
  Status = gBS->GetMemoryMap (&MemMapSize, NULL, &MapKey, &DescSize, &DescVersion);
  if (Status != EFI_BUFFER_TOO_SMALL) {
    Print (L"[MemMap] Unexpected status from GetMemoryMap: %r\n", Status);
    return;
  }

  //
  // Add extra space because the allocation itself changes the map.
  //
  MemMapSize += 2 * DescSize;
  MemMap = AllocatePool (MemMapSize);
  if (MemMap == NULL) {
    Print (L"[MemMap] AllocatePool failed.\n");
    return;
  }

  Status = gBS->GetMemoryMap (&MemMapSize, MemMap, &MapKey, &DescSize, &DescVersion);
  if (EFI_ERROR (Status)) {
    Print (L"[MemMap] GetMemoryMap failed: %r\n", Status);
    FreePool (MemMap);
    return;
  }

  EntryCount = MemMapSize / DescSize;
  Print (L"[MemMap] %u entries, descriptor size %u, version %u\n\n",
         EntryCount, DescSize, DescVersion);

  //
  // Print a summary of each entry (first 20 to avoid scrolling).
  //
  Print (L"  %-16s  %-18s  %-10s  %s\n",
         L"Type", L"PhysicalStart", L"Pages", L"Attributes");
  Print (L"  %-16s  %-18s  %-10s  %s\n",
         L"----", L"-------------", L"-----", L"----------");

  TotalPages = 0;
  for (Index = 0; Index < EntryCount && Index < 20; Index++) {
    Desc = (EFI_MEMORY_DESCRIPTOR *)((UINT8 *)MemMap + Index * DescSize);
    Print (L"  %-16s  0x%016lX  %-10lu  0x%lX\n",
           MemTypeName (Desc->Type),
           Desc->PhysicalStart,
           Desc->NumberOfPages,
           Desc->Attribute);
    TotalPages += Desc->NumberOfPages;
  }

  if (EntryCount > 20) {
    Print (L"  ... (%u more entries)\n", EntryCount - 20);
  }

  Print (L"\n  Total pages shown: %lu (%lu MiB)\n",
         TotalPages, (TotalPages * EFI_PAGE_SIZE) / (1024 * 1024));

  FreePool (MemMap);
}

/**
  Application entry point.
**/
EFI_STATUS
EFIAPI
MemoryExampleEntry (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
  Print (L"=== Memory Example ===\n\n");

  DemoPoolAllocation ();
  DemoPageAllocation ();
  DemoMemoryMap ();

  WAIT_FOR_KEY (SystemTable);
  return EFI_SUCCESS;
}
