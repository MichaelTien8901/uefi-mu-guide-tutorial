/** @file
  BlockIoExample.c -- Block device enumeration and media info.

  Demonstrates:
    - Using LocateHandleBuffer to find all Block I/O handles
    - Opening EFI_BLOCK_IO_PROTOCOL on each handle
    - Reading and displaying media information

  Copyright (c) 2026, UEFI Mu Guide Contributors. All rights reserved.
  SPDX-License-Identifier: BSD-2-Clause-Patent
**/

#include <UefiMuGuide.h>
#include <Protocol/BlockIo.h>

/**
  Print media information for a Block I/O device.
**/
STATIC
VOID
PrintMediaInfo (
  IN UINTN                  Index,
  IN EFI_BLOCK_IO_PROTOCOL  *BlockIo
  )
{
  EFI_BLOCK_IO_MEDIA  *Media;

  Media = BlockIo->Media;

  Print (L"\n  Device #%u:\n", Index);
  Print (L"    MediaId       : 0x%08X\n", Media->MediaId);
  Print (L"    RemovableMedia: %s\n", Media->RemovableMedia ? L"Yes" : L"No");
  Print (L"    MediaPresent  : %s\n", Media->MediaPresent   ? L"Yes" : L"No");
  Print (L"    LogicalPartition: %s\n",
         Media->LogicalPartition ? L"Yes" : L"No");
  Print (L"    ReadOnly      : %s\n", Media->ReadOnly ? L"Yes" : L"No");
  Print (L"    BlockSize     : %u bytes\n", Media->BlockSize);
  Print (L"    LastBlock     : %lu\n", Media->LastBlock);

  if (Media->BlockSize > 0) {
    UINT64  SizeMB;

    SizeMB = ((Media->LastBlock + 1) * Media->BlockSize) / (1024 * 1024);
    Print (L"    Total Size    : ~%lu MiB\n", SizeMB);
  }

  Print (L"    IoAlign       : %u\n", Media->IoAlign);
}

/**
  Application entry point.
**/
EFI_STATUS
EFIAPI
BlockIoExampleEntry (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
  EFI_STATUS             Status;
  EFI_HANDLE             *HandleBuffer;
  UINTN                  HandleCount;
  UINTN                  Index;
  EFI_BLOCK_IO_PROTOCOL  *BlockIo;

  Print (L"=== Block I/O Example ===\n\n");

  //
  // Locate all handles that support Block I/O.
  //
  Status = gBS->LocateHandleBuffer (
                  ByProtocol,
                  &gEfiBlockIoProtocolGuid,
                  NULL,
                  &HandleCount,
                  &HandleBuffer
                  );
  if (EFI_ERROR (Status)) {
    Print (L"No block devices found - %r\n", Status);
    WAIT_FOR_KEY (SystemTable);
    return Status;
  }

  Print (L"Found %u block device(s):\n", HandleCount);

  for (Index = 0; Index < HandleCount; Index++) {
    Status = gBS->HandleProtocol (
                    HandleBuffer[Index],
                    &gEfiBlockIoProtocolGuid,
                    (VOID **)&BlockIo
                    );
    if (EFI_ERROR (Status)) {
      Print (L"  Device #%u: HandleProtocol failed - %r\n", Index, Status);
      continue;
    }

    PrintMediaInfo (Index, BlockIo);
  }

  Print (L"\n  Enumeration complete.\n");

  gBS->FreePool (HandleBuffer);
  WAIT_FOR_KEY (SystemTable);
  return EFI_SUCCESS;
}
