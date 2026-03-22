/** @file
  ConsoleExample.c -- Console I/O, text colors, cursor, and key input.

  Demonstrates:
    - SetAttribute for foreground/background colors
    - SetCursorPosition for text placement
    - ReadKeyStroke in a loop to display key information
    - Querying console mode dimensions

  Copyright (c) 2026, UEFI Mu Guide Contributors. All rights reserved.
  SPDX-License-Identifier: BSD-2-Clause-Patent
**/

#include <UefiMuGuide.h>

//
// Color names for display.
//
STATIC CONST CHAR16  *mColorNames[] = {
  L"Black", L"Blue", L"Green", L"Cyan",
  L"Red", L"Magenta", L"Brown", L"LightGray",
  L"DarkGray", L"LightBlue", L"LightGreen", L"LightCyan",
  L"LightRed", L"LightMagenta", L"Yellow", L"White"
};

/**
  Demonstrate text color attributes.
**/
STATIC
VOID
DemoColors (
  IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL  *ConOut
  )
{
  UINTN  Fg;

  Print (L"[Colors] Foreground color demo:\n");

  for (Fg = 0; Fg < 16; Fg++) {
    ConOut->SetAttribute (ConOut, EFI_TEXT_ATTR ((UINTN)Fg, EFI_BLACK));
    Print (L"  %-14s", mColorNames[Fg]);
    if ((Fg % 4) == 3) {
      Print (L"\n");
    }
  }

  //
  // Background color demo (only 0-7 valid for background).
  //
  Print (L"\n[Colors] Background color demo:\n");
  {
    UINTN  Bg;

    for (Bg = 0; Bg < 8; Bg++) {
      ConOut->SetAttribute (ConOut, EFI_TEXT_ATTR (EFI_WHITE, Bg));
      Print (L"  BG=%s ", mColorNames[Bg]);
    }
  }

  //
  // Reset to default.
  //
  ConOut->SetAttribute (ConOut, EFI_TEXT_ATTR (EFI_LIGHTGRAY, EFI_BLACK));
  Print (L"\n\n");
}

/**
  Demonstrate cursor positioning.
**/
STATIC
VOID
DemoCursor (
  IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL  *ConOut
  )
{
  UINTN   Columns;
  UINTN   Rows;
  UINTN   Col;

  ConOut->QueryMode (ConOut, ConOut->Mode->Mode, &Columns, &Rows);
  Print (L"[Cursor] Console mode: %u columns x %u rows\n", Columns, Rows);

  //
  // Draw a line of asterisks at a specific row using SetCursorPosition.
  //
  Print (L"[Cursor] Drawing asterisks at row 15:\n");
  for (Col = 5; Col < 45 && Col < Columns; Col++) {
    ConOut->SetCursorPosition (ConOut, Col, 15);
    ConOut->SetAttribute (ConOut, EFI_TEXT_ATTR (EFI_YELLOW, EFI_BLUE));
    Print (L"*");
  }

  ConOut->SetAttribute (ConOut, EFI_TEXT_ATTR (EFI_LIGHTGRAY, EFI_BLACK));
  ConOut->SetCursorPosition (ConOut, 0, 17);
  Print (L"\n");
}

/**
  Interactive key reading loop.
**/
STATIC
VOID
DemoKeyInput (
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
  EFI_STATUS     Status;
  EFI_INPUT_KEY  Key;
  UINTN          EventIndex;
  UINTN          Count;

  Print (L"[KeyInput] Press keys to see their codes (ESC to stop):\n\n");
  Print (L"  %-10s  %-14s  %s\n", L"Key#", L"Unicode", L"ScanCode");
  Print (L"  %-10s  %-14s  %s\n", L"----", L"-------", L"--------");

  for (Count = 1; Count <= 20; Count++) {
    Status = gBS->WaitForEvent (
                    1,
                    &SystemTable->ConIn->WaitForKey,
                    &EventIndex
                    );
    if (EFI_ERROR (Status)) {
      break;
    }

    Status = SystemTable->ConIn->ReadKeyStroke (SystemTable->ConIn, &Key);
    if (EFI_ERROR (Status)) {
      continue;
    }

    Print (L"  %-10u  0x%04X ('%c')   0x%04X\n",
           Count,
           Key.UnicodeChar,
           (Key.UnicodeChar >= 0x20 && Key.UnicodeChar < 0x7F)
             ? Key.UnicodeChar : L'.',
           Key.ScanCode);

    //
    // ESC key has ScanCode = 0x17.
    //
    if (Key.ScanCode == SCAN_ESC) {
      Print (L"\n  ESC pressed -- exiting key loop.\n");
      break;
    }
  }

  if (Count > 20) {
    Print (L"\n  Reached 20-key limit.\n");
  }
}

/**
  Application entry point.
**/
EFI_STATUS
EFIAPI
ConsoleExampleEntry (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
  SystemTable->ConOut->ClearScreen (SystemTable->ConOut);
  Print (L"=== Console Example ===\n\n");

  DemoColors (SystemTable->ConOut);
  DemoCursor (SystemTable->ConOut);
  DemoKeyInput (SystemTable);

  return EFI_SUCCESS;
}
