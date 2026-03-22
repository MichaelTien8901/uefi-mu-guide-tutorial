/** @file
  FileSystemExample.c -- File system operations demonstration.

  Demonstrates:
    - Locating EFI_SIMPLE_FILE_SYSTEM_PROTOCOL
    - Opening a volume (root directory)
    - Creating, writing, and reading a file
    - Listing directory contents

  Copyright (c) 2026, UEFI Mu Guide Contributors. All rights reserved.
  SPDX-License-Identifier: BSD-2-Clause-Patent
**/

#include <UefiMuGuide.h>
#include <Protocol/SimpleFileSystem.h>
#include <Guid/FileInfo.h>

#define TEST_FILE_NAME  L"MuGuideTest.txt"
#define TEST_DATA       "Hello from UEFI FileSystem example!\r\n"

/**
  Create and write a test file.
**/
STATIC
EFI_STATUS
WriteTestFile (
  IN EFI_FILE_PROTOCOL  *Root
  )
{
  EFI_STATUS         Status;
  EFI_FILE_PROTOCOL  *File;
  UINTN              DataSize;

  Print (L"[Write] Creating '%s'...\n", TEST_FILE_NAME);

  Status = Root->Open (
                   Root,
                   &File,
                   TEST_FILE_NAME,
                   EFI_FILE_MODE_CREATE | EFI_FILE_MODE_READ | EFI_FILE_MODE_WRITE,
                   0
                   );
  CHECK_STATUS_RETURN (Status, "Open for write");

  DataSize = AsciiStrLen (TEST_DATA);
  Status = File->Write (File, &DataSize, (VOID *)TEST_DATA);
  CHECK_STATUS (Status, "Write");

  Print (L"  Wrote %u bytes.\n", DataSize);

  File->Close (File);
  return EFI_SUCCESS;
}

/**
  Read back the test file and print its contents.
**/
STATIC
EFI_STATUS
ReadTestFile (
  IN EFI_FILE_PROTOCOL  *Root
  )
{
  EFI_STATUS         Status;
  EFI_FILE_PROTOCOL  *File;
  CHAR8              Buffer[256];
  UINTN              ReadSize;

  Print (L"\n[Read] Opening '%s'...\n", TEST_FILE_NAME);

  Status = Root->Open (Root, &File, TEST_FILE_NAME, EFI_FILE_MODE_READ, 0);
  CHECK_STATUS_RETURN (Status, "Open for read");

  ReadSize = sizeof (Buffer) - 1;
  Status = File->Read (File, &ReadSize, Buffer);
  CHECK_STATUS (Status, "Read");

  Buffer[ReadSize] = '\0';
  Print (L"  Read %u bytes: \"%a\"\n", ReadSize, Buffer);

  File->Close (File);
  return EFI_SUCCESS;
}

/**
  List contents of the root directory.
**/
STATIC
VOID
ListDirectory (
  IN EFI_FILE_PROTOCOL  *Root
  )
{
  EFI_STATUS     Status;
  UINT8          Buffer[512];
  UINTN          BufSize;
  EFI_FILE_INFO  *FileInfo;
  UINTN          Count;

  Print (L"\n[Directory] Root directory listing:\n");
  Print (L"  %-30s  %-10s  %s\n", L"Name", L"Size", L"Attr");
  Print (L"  %-30s  %-10s  %s\n", L"----", L"----", L"----");

  //
  // Reset to the beginning of the directory.
  //
  Root->SetPosition (Root, 0);

  Count = 0;
  for (;;) {
    BufSize = sizeof (Buffer);
    Status = Root->Read (Root, &BufSize, Buffer);
    if (EFI_ERROR (Status) || BufSize == 0) {
      break;
    }

    FileInfo = (EFI_FILE_INFO *)Buffer;
    Print (L"  %-30s  %-10lu  0x%lX",
           FileInfo->FileName,
           FileInfo->FileSize,
           FileInfo->Attribute);

    if (FileInfo->Attribute & EFI_FILE_DIRECTORY) {
      Print (L"  <DIR>");
    }

    Print (L"\n");
    Count++;

    if (Count >= 30) {
      Print (L"  ... (truncated)\n");
      break;
    }
  }

  Print (L"  Total: %u entries shown.\n", Count);
}

/**
  Application entry point.
**/
EFI_STATUS
EFIAPI
FileSystemExampleEntry (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
  EFI_STATUS                       Status;
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL  *Fs;
  EFI_FILE_PROTOCOL                *Root;

  Print (L"=== FileSystem Example ===\n\n");

  //
  // Locate a file system protocol instance.
  //
  Status = gBS->LocateProtocol (
                  &gEfiSimpleFileSystemProtocolGuid,
                  NULL,
                  (VOID **)&Fs
                  );
  if (EFI_ERROR (Status)) {
    Print (L"ERROR: No file system found - %r\n", Status);
    WAIT_FOR_KEY (SystemTable);
    return Status;
  }

  //
  // Open the volume root.
  //
  Status = Fs->OpenVolume (Fs, &Root);
  CHECK_STATUS_RETURN (Status, "OpenVolume");
  Print (L"Volume opened successfully.\n\n");

  //
  // Write, read, and list.
  //
  WriteTestFile (Root);
  ReadTestFile (Root);
  ListDirectory (Root);

  Root->Close (Root);

  WAIT_FOR_KEY (SystemTable);
  return EFI_SUCCESS;
}
