/** @file
  VariableExample.c -- UEFI variable read, write, and delete.

  Demonstrates:
    - Reading the standard BootOrder variable
    - Creating a custom UEFI variable
    - Reading it back
    - Deleting the variable

  Copyright (c) 2026, UEFI Mu Guide Contributors. All rights reserved.
  SPDX-License-Identifier: BSD-2-Clause-Patent
**/

#include <UefiMuGuide.h>
#include <Guid/GlobalVariable.h>

extern EFI_GUID  gUefiMuGuideTestVariableGuid;

#define TEST_VAR_NAME  L"MuGuideTestVar"

/**
  Read and display the BootOrder variable.
**/
STATIC
VOID
ReadBootOrder (
  VOID
  )
{
  EFI_STATUS  Status;
  UINT16      *BootOrder;
  UINTN       DataSize;
  UINT32      Attributes;
  UINTN       Count;
  UINTN       Index;

  Print (L"[BootOrder] Reading BootOrder variable...\n");

  //
  // First call to get the size.
  //
  DataSize = 0;
  Status = gRT->GetVariable (
                  L"BootOrder",
                  &gEfiGlobalVariableGuid,
                  &Attributes,
                  &DataSize,
                  NULL
                  );
  if (Status != EFI_BUFFER_TOO_SMALL) {
    Print (L"  BootOrder not found or error: %r\n\n", Status);
    return;
  }

  BootOrder = AllocatePool (DataSize);
  if (BootOrder == NULL) {
    Print (L"  Memory allocation failed.\n\n");
    return;
  }

  Status = gRT->GetVariable (
                  L"BootOrder",
                  &gEfiGlobalVariableGuid,
                  &Attributes,
                  &DataSize,
                  BootOrder
                  );
  if (EFI_ERROR (Status)) {
    Print (L"  GetVariable failed: %r\n\n", Status);
    FreePool (BootOrder);
    return;
  }

  Count = DataSize / sizeof (UINT16);
  Print (L"  Attributes: 0x%08X\n", Attributes);
  Print (L"  Boot order (%u entries):", Count);
  for (Index = 0; Index < Count; Index++) {
    Print (L" %04X", BootOrder[Index]);
  }

  Print (L"\n\n");
  FreePool (BootOrder);
}

/**
  Create, read back, and delete a custom test variable.
**/
STATIC
VOID
TestCustomVariable (
  VOID
  )
{
  EFI_STATUS  Status;
  CHAR8       WriteData[] = "Hello from MuGuide!";
  CHAR8       ReadBuffer[64];
  UINTN       DataSize;
  UINT32      Attributes;

  //
  // Step 1: Create the variable.
  //
  Print (L"[Custom Variable] Creating '%s'...\n", TEST_VAR_NAME);

  Status = gRT->SetVariable (
                  TEST_VAR_NAME,
                  &gUefiMuGuideTestVariableGuid,
                  EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS,
                  AsciiStrLen (WriteData) + 1,
                  WriteData
                  );
  if (EFI_ERROR (Status)) {
    Print (L"  SetVariable failed: %r\n", Status);
    Print (L"  (This may fail on read-only variable stores.)\n\n");
    return;
  }

  Print (L"  Written: \"%a\"\n", WriteData);

  //
  // Step 2: Read it back.
  //
  Print (L"  Reading back...\n");
  DataSize = sizeof (ReadBuffer);
  Status = gRT->GetVariable (
                  TEST_VAR_NAME,
                  &gUefiMuGuideTestVariableGuid,
                  &Attributes,
                  &DataSize,
                  ReadBuffer
                  );
  if (EFI_ERROR (Status)) {
    Print (L"  GetVariable failed: %r\n\n", Status);
    return;
  }

  Print (L"  Read back (%u bytes): \"%a\"\n", DataSize, ReadBuffer);
  Print (L"  Attributes: 0x%08X\n", Attributes);

  //
  // Step 3: Delete the variable (set with DataSize=0).
  //
  Print (L"  Deleting variable...\n");
  Status = gRT->SetVariable (
                  TEST_VAR_NAME,
                  &gUefiMuGuideTestVariableGuid,
                  0,
                  0,
                  NULL
                  );
  if (EFI_ERROR (Status)) {
    Print (L"  Delete failed: %r\n", Status);
  } else {
    Print (L"  Deleted successfully.\n");
  }

  //
  // Verify deletion.
  //
  DataSize = sizeof (ReadBuffer);
  Status = gRT->GetVariable (
                  TEST_VAR_NAME,
                  &gUefiMuGuideTestVariableGuid,
                  NULL,
                  &DataSize,
                  ReadBuffer
                  );
  Print (L"  Verify: GetVariable after delete => %r (expected NOT_FOUND)\n\n",
         Status);
}

/**
  Application entry point.
**/
EFI_STATUS
EFIAPI
VariableExampleEntry (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
  Print (L"=== Variable Example ===\n\n");

  ReadBootOrder ();
  TestCustomVariable ();

  WAIT_FOR_KEY (SystemTable);
  return EFI_SUCCESS;
}
