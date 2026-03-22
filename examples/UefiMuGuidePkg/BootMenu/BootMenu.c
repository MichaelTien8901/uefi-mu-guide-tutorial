/** @file
  BootMenu.c -- Boot option menu display and selection.

  Demonstrates:
    - Reading BootOrder and Boot#### variables
    - Parsing EFI_LOAD_OPTION structures
    - Displaying a numbered boot menu
    - Accepting user selection via key input

  Copyright (c) 2026, UEFI Mu Guide Contributors. All rights reserved.
  SPDX-License-Identifier: BSD-2-Clause-Patent
**/

#include <UefiMuGuide.h>
#include <Guid/GlobalVariable.h>
#include <Library/DevicePathLib.h>

#define MAX_BOOT_OPTIONS  32

//
// EFI_LOAD_OPTION layout (UEFI Spec 3.1.3):
//   UINT32   Attributes
//   UINT16   FilePathListLength
//   CHAR16   Description[]       (null-terminated)
//   ... DevicePath ...
//   ... OptionalData ...
//

/**
  Read a Boot#### variable and print its description.

  @param[in] OptionNum  The 4-digit hex boot option number.
  @param[in] MenuIndex  Display index for the menu.

  @retval EFI_SUCCESS  Variable read and description printed.
**/
STATIC
EFI_STATUS
PrintBootOption (
  IN UINT16  OptionNum,
  IN UINTN   MenuIndex
  )
{
  EFI_STATUS  Status;
  CHAR16      VarName[16];
  UINT8       *Data;
  UINTN       DataSize;
  UINT32      Attributes;
  CHAR16      *Description;

  UnicodeSPrint (VarName, sizeof (VarName), L"Boot%04X", OptionNum);

  //
  // Get variable size.
  //
  DataSize = 0;
  Status = gRT->GetVariable (VarName, &gEfiGlobalVariableGuid, NULL, &DataSize, NULL);
  if (Status != EFI_BUFFER_TOO_SMALL) {
    return EFI_NOT_FOUND;
  }

  Data = AllocatePool (DataSize);
  if (Data == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  Status = gRT->GetVariable (VarName, &gEfiGlobalVariableGuid, NULL, &DataSize, Data);
  if (EFI_ERROR (Status)) {
    FreePool (Data);
    return Status;
  }

  //
  // Parse the EFI_LOAD_OPTION header.
  //
  if (DataSize < sizeof (UINT32) + sizeof (UINT16) + sizeof (CHAR16)) {
    FreePool (Data);
    return EFI_INVALID_PARAMETER;
  }

  Attributes  = *(UINT32 *)Data;
  Description = (CHAR16 *)(Data + sizeof (UINT32) + sizeof (UINT16));

  Print (L"  [%u] Boot%04X: %s", MenuIndex, OptionNum, Description);
  if (!(Attributes & 0x00000001)) {  // LOAD_OPTION_ACTIVE
    Print (L"  (inactive)");
  }

  Print (L"\n");

  FreePool (Data);
  return EFI_SUCCESS;
}

/**
  Application entry point.
**/
EFI_STATUS
EFIAPI
BootMenuEntry (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
  EFI_STATUS     Status;
  UINT16         *BootOrder;
  UINTN          DataSize;
  UINTN          OptionCount;
  UINTN          Index;
  EFI_INPUT_KEY  Key;
  UINTN          EventIndex;
  UINTN          Selection;

  Print (L"=== Boot Menu ===\n\n");

  //
  // Read BootOrder.
  //
  DataSize = 0;
  Status = gRT->GetVariable (
                  L"BootOrder",
                  &gEfiGlobalVariableGuid,
                  NULL,
                  &DataSize,
                  NULL
                  );
  if (Status != EFI_BUFFER_TOO_SMALL) {
    Print (L"BootOrder variable not found.\n");
    Print (L"  (This is expected in some QEMU/test environments.)\n");
    WAIT_FOR_KEY (SystemTable);
    return EFI_SUCCESS;
  }

  BootOrder = AllocatePool (DataSize);
  if (BootOrder == NULL) {
    Print (L"Memory allocation failed.\n");
    return EFI_OUT_OF_RESOURCES;
  }

  Status = gRT->GetVariable (
                  L"BootOrder",
                  &gEfiGlobalVariableGuid,
                  NULL,
                  &DataSize,
                  BootOrder
                  );
  if (EFI_ERROR (Status)) {
    Print (L"Failed to read BootOrder: %r\n", Status);
    FreePool (BootOrder);
    WAIT_FOR_KEY (SystemTable);
    return Status;
  }

  OptionCount = DataSize / sizeof (UINT16);
  if (OptionCount > MAX_BOOT_OPTIONS) {
    OptionCount = MAX_BOOT_OPTIONS;
  }

  //
  // Display the boot menu.
  //
  Print (L"Boot Options:\n\n");

  for (Index = 0; Index < OptionCount; Index++) {
    Status = PrintBootOption (BootOrder[Index], Index + 1);
    if (EFI_ERROR (Status)) {
      Print (L"  [%u] Boot%04X: (unreadable - %r)\n",
             Index + 1, BootOrder[Index], Status);
    }
  }

  Print (L"\n  [0] Cancel\n");

  //
  // Get user selection.
  //
  Print (L"\nSelect boot option (0-%u): ", OptionCount);

  Status = gBS->WaitForEvent (1, &SystemTable->ConIn->WaitForKey, &EventIndex);
  if (EFI_ERROR (Status)) {
    FreePool (BootOrder);
    return Status;
  }

  Status = SystemTable->ConIn->ReadKeyStroke (SystemTable->ConIn, &Key);
  if (EFI_ERROR (Status)) {
    FreePool (BootOrder);
    return Status;
  }

  //
  // Convert key to number.
  //
  if (Key.UnicodeChar >= L'0' && Key.UnicodeChar <= L'9') {
    Selection = Key.UnicodeChar - L'0';
    Print (L"%u\n", Selection);

    if (Selection == 0) {
      Print (L"\nCancelled.\n");
    } else if (Selection <= OptionCount) {
      Print (L"\nYou selected Boot%04X.\n", BootOrder[Selection - 1]);
      Print (L"  (In a real boot manager, we would call LoadImage/StartImage here.)\n");
    } else {
      Print (L"\nInvalid selection.\n");
    }
  } else {
    Print (L"\nInvalid key.\n");
  }

  FreePool (BootOrder);
  WAIT_FOR_KEY (SystemTable);
  return EFI_SUCCESS;
}
