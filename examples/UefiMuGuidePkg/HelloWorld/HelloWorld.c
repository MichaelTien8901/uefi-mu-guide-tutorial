/** @file
  HelloWorld.c -- Minimal UEFI "Hello World" application.

  Demonstrates the basic structure of a UEFI application:
    - Entry point signature
    - Using SystemTable for console output
    - Using Print() from UefiLib
    - Waiting for a keypress before exit

  Copyright (c) 2026, UEFI Mu Guide Contributors. All rights reserved.
  SPDX-License-Identifier: BSD-2-Clause-Patent
**/

#include <UefiMuGuide.h>

/**
  Print basic firmware and system information from the SystemTable.

  @param[in] SystemTable  Pointer to the UEFI System Table.
**/
STATIC
VOID
PrintSystemInfo (
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
  Print (L"  Firmware Vendor : %s\n", SystemTable->FirmwareVendor);
  Print (L"  Firmware Rev    : 0x%08X\n", SystemTable->FirmwareRevision);
  Print (L"  UEFI Revision   : %d.%d\n",
         SystemTable->Hdr.Revision >> 16,
         SystemTable->Hdr.Revision & 0xFFFF);
  Print (L"  System Table Sz : %d bytes\n", SystemTable->Hdr.HeaderSize);
}

/**
  Application entry point.

  @param[in] ImageHandle  Handle for this loaded image.
  @param[in] SystemTable  Pointer to the UEFI System Table.

  @retval EFI_SUCCESS  The application completed successfully.
**/
EFI_STATUS
EFIAPI
HelloWorldEntry (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
  EFI_STATUS     Status;
  EFI_INPUT_KEY  Key;
  UINTN          EventIndex;

  //
  // Clear the console screen.
  //
  SystemTable->ConOut->ClearScreen (SystemTable->ConOut);

  //
  // Print our greeting.
  //
  Print (L"===========================================\n");
  Print (L"  Hello from Project Mu!\n");
  Print (L"===========================================\n\n");

  DEBUG ((DEBUG_INFO, "HelloWorld: Application started successfully.\n"));

  //
  // Display system information.
  //
  Print (L"System Information:\n");
  PrintSystemInfo (SystemTable);

  //
  // Demonstrate using the ImageHandle -- retrieve loaded image info.
  //
  Print (L"\n  Image Handle    : 0x%p\n", ImageHandle);
  Print (L"  Boot Services   : 0x%p\n", gBS);
  Print (L"  Runtime Services: 0x%p\n", gRT);

  //
  // Wait for a keypress using WaitForEvent.
  //
  Print (L"\nPress any key to exit...\n");

  Status = gBS->WaitForEvent (1, &SystemTable->ConIn->WaitForKey, &EventIndex);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "HelloWorld: WaitForEvent failed - %r\n", Status));
    return Status;
  }

  //
  // Read and display the key that was pressed.
  //
  Status = SystemTable->ConIn->ReadKeyStroke (SystemTable->ConIn, &Key);
  if (!EFI_ERROR (Status)) {
    Print (L"You pressed: Unicode=0x%04X  ScanCode=0x%04X\n",
           Key.UnicodeChar, Key.ScanCode);
  }

  DEBUG ((DEBUG_INFO, "HelloWorld: Exiting with EFI_SUCCESS.\n"));
  return EFI_SUCCESS;
}
