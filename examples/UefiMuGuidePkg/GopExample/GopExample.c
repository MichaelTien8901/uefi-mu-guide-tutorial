/** @file
  GopExample.c -- Graphics Output Protocol demonstration.

  Demonstrates:
    - Locating the Graphics Output Protocol (GOP)
    - Enumerating available video modes
    - Drawing colored rectangles using BLT (Block Transfer)

  Copyright (c) 2026, UEFI Mu Guide Contributors. All rights reserved.
  SPDX-License-Identifier: BSD-2-Clause-Patent
**/

#include <UefiMuGuide.h>
#include <Protocol/GraphicsOutput.h>

/**
  List all available video modes.
**/
STATIC
VOID
ListVideoModes (
  IN EFI_GRAPHICS_OUTPUT_PROTOCOL  *Gop
  )
{
  EFI_STATUS                            Status;
  UINT32                                Mode;
  UINTN                                 InfoSize;
  EFI_GRAPHICS_OUTPUT_MODE_INFORMATION  *Info;

  Print (L"[GOP] Available video modes (%u total):\n", Gop->Mode->MaxMode);
  Print (L"  %-6s  %-12s  %s\n", L"Mode", L"Resolution", L"PixelFormat");
  Print (L"  %-6s  %-12s  %s\n", L"----", L"----------", L"-----------");

  for (Mode = 0; Mode < Gop->Mode->MaxMode; Mode++) {
    Status = Gop->QueryMode (Gop, Mode, &InfoSize, &Info);
    if (EFI_ERROR (Status)) {
      continue;
    }

    Print (L"  %-6u  %4ux%-7u  %u",
           Mode,
           Info->HorizontalResolution,
           Info->VerticalResolution,
           Info->PixelFormat);

    if (Mode == Gop->Mode->Mode) {
      Print (L"  <-- current");
    }

    Print (L"\n");
    gBS->FreePool (Info);
  }

  Print (L"\n  Current: %ux%u, FrameBuffer at 0x%lX (%lu bytes)\n\n",
         Gop->Mode->Info->HorizontalResolution,
         Gop->Mode->Info->VerticalResolution,
         Gop->Mode->FrameBufferBase,
         Gop->Mode->FrameBufferSize);
}

/**
  Draw a filled rectangle using BLT.

  @param[in] Gop     Graphics Output Protocol.
  @param[in] X       Left edge.
  @param[in] Y       Top edge.
  @param[in] Width   Rectangle width in pixels.
  @param[in] Height  Rectangle height in pixels.
  @param[in] Red     Red component (0-255).
  @param[in] Green   Green component (0-255).
  @param[in] Blue    Blue component (0-255).
**/
STATIC
EFI_STATUS
DrawRect (
  IN EFI_GRAPHICS_OUTPUT_PROTOCOL  *Gop,
  IN UINTN                        X,
  IN UINTN                        Y,
  IN UINTN                        Width,
  IN UINTN                        Height,
  IN UINT8                        Red,
  IN UINT8                        Green,
  IN UINT8                        Blue
  )
{
  EFI_GRAPHICS_OUTPUT_BLT_PIXEL  Fill;

  Fill.Red      = Red;
  Fill.Green    = Green;
  Fill.Blue     = Blue;
  Fill.Reserved = 0;

  return Gop->Blt (
                Gop,
                &Fill,
                EfiBltVideoFill,
                0, 0,           // Source X, Y (ignored for fill)
                X, Y,           // Destination X, Y
                Width, Height,
                0               // Delta (0 = use Width)
                );
}

/**
  Application entry point.
**/
EFI_STATUS
EFIAPI
GopExampleEntry (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
  EFI_STATUS                     Status;
  EFI_GRAPHICS_OUTPUT_PROTOCOL   *Gop;
  UINTN                          ScreenW;
  UINTN                          ScreenH;

  Print (L"=== GOP Example ===\n\n");

  //
  // Locate the Graphics Output Protocol.
  //
  Status = gBS->LocateProtocol (
                  &gEfiGraphicsOutputProtocolGuid,
                  NULL,
                  (VOID **)&Gop
                  );
  if (EFI_ERROR (Status)) {
    Print (L"ERROR: GOP not found - %r\n", Status);
    Print (L"  (This is normal when running in a text-only console.)\n");
    WAIT_FOR_KEY (SystemTable);
    return Status;
  }

  //
  // List available modes.
  //
  ListVideoModes (Gop);

  ScreenW = Gop->Mode->Info->HorizontalResolution;
  ScreenH = Gop->Mode->Info->VerticalResolution;

  //
  // Draw colored rectangles.
  //
  Print (L"[GOP] Drawing colored rectangles...\n");

  // Red rectangle (top-left area)
  DrawRect (Gop, 50, 50, 200, 150, 255, 0, 0);

  // Green rectangle (overlapping)
  DrawRect (Gop, 150, 100, 200, 150, 0, 200, 0);

  // Blue rectangle
  DrawRect (Gop, 250, 150, 200, 150, 0, 0, 255);

  // Yellow rectangle
  DrawRect (Gop, 100, 200, 200, 100, 255, 255, 0);

  // White border at top
  DrawRect (Gop, 0, 0, ScreenW, 3, 255, 255, 255);

  Print (L"  Rectangles drawn. Screen size: %ux%u\n", ScreenW, ScreenH);

  WAIT_FOR_KEY (SystemTable);
  return EFI_SUCCESS;
}
