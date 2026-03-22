/** @file
  BootLoader.c -- File loading and ExitBootServices pattern.

  Demonstrates:
    - Opening the file system from the loaded image's device
    - Loading a file into memory
    - Retrieving the memory map for ExitBootServices
    - The ExitBootServices call pattern (demonstrated but not executed
      to avoid terminating the UEFI environment)

  WARNING: This example demonstrates the ExitBootServices flow but does
  NOT actually call ExitBootServices, because doing so would prevent
  returning to the UEFI Shell. The critical code path is shown with
  detailed comments.

  Copyright (c) 2026, UEFI Mu Guide Contributors. All rights reserved.
  SPDX-License-Identifier: BSD-2-Clause-Patent
**/

#include <UefiMuGuide.h>
#include <Protocol/SimpleFileSystem.h>
#include <Protocol/LoadedImage.h>
#include <Guid/FileInfo.h>

#define PAYLOAD_FILE_NAME  L"payload.bin"

/**
  Load a file from the boot volume into an allocated buffer.

  @param[in]  Root       Open file protocol for the volume root.
  @param[in]  FileName   Name of the file to load.
  @param[out] Buffer     Allocated buffer containing file data.
  @param[out] FileSize   Size of the loaded data in bytes.

  @retval EFI_SUCCESS    File loaded.
**/
STATIC
EFI_STATUS
LoadFileToMemory (
  IN  EFI_FILE_PROTOCOL  *Root,
  IN  CONST CHAR16       *FileName,
  OUT VOID               **Buffer,
  OUT UINTN              *FileSize
  )
{
  EFI_STATUS         Status;
  EFI_FILE_PROTOCOL  *File;
  UINT8              InfoBuffer[256];
  EFI_FILE_INFO      *Info;
  UINTN              InfoSize;
  UINTN              Size;
  VOID               *Data;

  Status = Root->Open (Root, &File, (CHAR16 *)FileName, EFI_FILE_MODE_READ, 0);
  if (EFI_ERROR (Status)) {
    Print (L"  Could not open '%s': %r\n", FileName, Status);
    return Status;
  }

  //
  // Get file size via GetInfo.
  //
  InfoSize = sizeof (InfoBuffer);
  Status = File->GetInfo (File, &gEfiFileInfoGuid, &InfoSize, InfoBuffer);
  if (EFI_ERROR (Status)) {
    Print (L"  GetInfo failed: %r\n", Status);
    File->Close (File);
    return Status;
  }

  Info = (EFI_FILE_INFO *)InfoBuffer;
  Size = (UINTN)Info->FileSize;
  Print (L"  File '%s': %u bytes\n", FileName, Size);

  //
  // Allocate pages for the file content (page-aligned for potential
  // use as executable code).
  //
  Data = AllocatePages (BYTES_TO_PAGES (Size));
  if (Data == NULL) {
    Print (L"  AllocatePages failed.\n");
    File->Close (File);
    return EFI_OUT_OF_RESOURCES;
  }

  //
  // Read the entire file.
  //
  Status = File->Read (File, &Size, Data);
  File->Close (File);

  if (EFI_ERROR (Status)) {
    Print (L"  Read failed: %r\n", Status);
    FreePages (Data, BYTES_TO_PAGES (Size));
    return Status;
  }

  *Buffer  = Data;
  *FileSize = Size;
  return EFI_SUCCESS;
}

/**
  Demonstrate the ExitBootServices pattern without actually calling it.
**/
STATIC
VOID
DemoExitBootServices (
  IN EFI_HANDLE  ImageHandle
  )
{
  EFI_STATUS             Status;
  UINTN                  MemMapSize;
  EFI_MEMORY_DESCRIPTOR  *MemMap;
  UINTN                  MapKey;
  UINTN                  DescSize;
  UINT32                 DescVersion;

  Print (L"\n[ExitBootServices Pattern]\n");
  Print (L"  Step 1: Get the memory map.\n");

  MemMapSize = 0;
  Status = gBS->GetMemoryMap (&MemMapSize, NULL, &MapKey, &DescSize, &DescVersion);
  if (Status != EFI_BUFFER_TOO_SMALL) {
    Print (L"  Unexpected GetMemoryMap status: %r\n", Status);
    return;
  }

  //
  // Allocate extra space; the allocation itself changes the map.
  //
  MemMapSize += 2 * DescSize;
  MemMap = AllocatePool (MemMapSize);
  if (MemMap == NULL) {
    Print (L"  AllocatePool for memory map failed.\n");
    return;
  }

  Status = gBS->GetMemoryMap (&MemMapSize, MemMap, &MapKey, &DescSize, &DescVersion);
  if (EFI_ERROR (Status)) {
    Print (L"  GetMemoryMap failed: %r\n", Status);
    FreePool (MemMap);
    return;
  }

  Print (L"  Memory map: %u entries, MapKey=0x%lX\n",
         MemMapSize / DescSize, (UINT64)MapKey);

  Print (L"\n  Step 2: Call ExitBootServices(ImageHandle, MapKey).\n");
  Print (L"  *** SKIPPING actual ExitBootServices call ***\n");
  Print (L"  *** (Calling it would terminate the UEFI Shell.) ***\n");

  Print (L"\n  In a real boot loader, the code would be:\n");
  Print (L"    Status = gBS->ExitBootServices(ImageHandle, MapKey);\n");
  Print (L"    if (Status == EFI_INVALID_PARAMETER) {\n");
  Print (L"      // Map changed -- re-get map (no more allocations!) and retry.\n");
  Print (L"      gBS->GetMemoryMap(&Size, MemMap, &MapKey, &DescSz, &DescVer);\n");
  Print (L"      gBS->ExitBootServices(ImageHandle, MapKey);\n");
  Print (L"    }\n");
  Print (L"    // After ExitBootServices: no Boot Services, no console, no timers.\n");
  Print (L"    // Jump to your OS kernel entry point.\n");

  FreePool (MemMap);
}

/**
  Application entry point.
**/
EFI_STATUS
EFIAPI
BootLoaderEntry (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
  EFI_STATUS                       Status;
  EFI_LOADED_IMAGE_PROTOCOL        *LoadedImage;
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL  *Fs;
  EFI_FILE_PROTOCOL                *Root;
  VOID                             *PayloadBuffer;
  UINTN                            PayloadSize;

  Print (L"=== Boot Loader Example ===\n\n");

  //
  // Get our loaded image protocol to find which device we booted from.
  //
  Status = gBS->HandleProtocol (
                  ImageHandle,
                  &gEfiLoadedImageProtocolGuid,
                  (VOID **)&LoadedImage
                  );
  CHECK_STATUS_RETURN (Status, "HandleProtocol LoadedImage");

  Print (L"Loaded from device: 0x%p\n", LoadedImage->DeviceHandle);

  //
  // Open the file system on our boot device.
  //
  Status = gBS->HandleProtocol (
                  LoadedImage->DeviceHandle,
                  &gEfiSimpleFileSystemProtocolGuid,
                  (VOID **)&Fs
                  );
  if (EFI_ERROR (Status)) {
    Print (L"No file system on boot device: %r\n", Status);
    WAIT_FOR_KEY (SystemTable);
    return Status;
  }

  Status = Fs->OpenVolume (Fs, &Root);
  CHECK_STATUS_RETURN (Status, "OpenVolume");

  //
  // Attempt to load a payload file.
  //
  Print (L"\n[File Loading]\n");
  Print (L"  Attempting to load '%s'...\n", PAYLOAD_FILE_NAME);

  PayloadBuffer = NULL;
  PayloadSize   = 0;
  Status = LoadFileToMemory (Root, PAYLOAD_FILE_NAME, &PayloadBuffer, &PayloadSize);

  if (EFI_ERROR (Status)) {
    Print (L"  Payload not found (this is expected in the example).\n");
    Print (L"  Create a '%s' file on the boot volume to test loading.\n",
           PAYLOAD_FILE_NAME);
  } else {
    Print (L"  Loaded %u bytes at 0x%p\n", PayloadSize, PayloadBuffer);
    Print (L"  First 16 bytes: ");
    {
      UINTN  i;
      UINT8  *Bytes;

      Bytes = (UINT8 *)PayloadBuffer;
      for (i = 0; i < 16 && i < PayloadSize; i++) {
        Print (L"%02X ", Bytes[i]);
      }
    }
    Print (L"\n");

    FreePages (PayloadBuffer, BYTES_TO_PAGES (PayloadSize));
  }

  Root->Close (Root);

  //
  // Demonstrate the ExitBootServices pattern.
  //
  DemoExitBootServices (ImageHandle);

  Print (L"\nBoot loader example complete.\n");
  WAIT_FOR_KEY (SystemTable);
  return EFI_SUCCESS;
}
