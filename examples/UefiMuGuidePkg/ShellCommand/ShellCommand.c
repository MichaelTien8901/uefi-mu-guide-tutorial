/** @file
  ShellCommand.c -- Shell application using ShellCEntryLib.

  Demonstrates:
    - Using ShellCEntryLib (ShellAppMain entry point)
    - Parsing command-line arguments (Argc/Argv)
    - Handling a -v (verbose) flag
    - Printing system information

  Usage:
    ShellCommand.efi [-v]

  Copyright (c) 2026, UEFI Mu Guide Contributors. All rights reserved.
  SPDX-License-Identifier: BSD-2-Clause-Patent
**/

#include <UefiMuGuide.h>
#include <Library/ShellLib.h>

/**
  Print basic system information.

  @param[in] Verbose  If TRUE, print extra details.
**/
STATIC
VOID
PrintSysInfo (
  IN BOOLEAN  Verbose
  )
{
  EFI_TIME  Time;

  Print (L"System Information\n");
  Print (L"==================\n\n");

  Print (L"  Firmware Vendor  : %s\n", gST->FirmwareVendor);
  Print (L"  Firmware Revision: 0x%08X\n", gST->FirmwareRevision);
  Print (L"  UEFI Revision    : %u.%u\n",
         gST->Hdr.Revision >> 16,
         gST->Hdr.Revision & 0xFFFF);

  if (!EFI_ERROR (gRT->GetTime (&Time, NULL))) {
    Print (L"  Current Time     : %04u-%02u-%02u %02u:%02u:%02u\n",
           Time.Year, Time.Month, Time.Day,
           Time.Hour, Time.Minute, Time.Second);
  }

  if (Verbose) {
    UINTN   Columns;
    UINTN   Rows;

    Print (L"\n  --- Verbose Details ---\n");
    Print (L"  Boot Services    : 0x%p\n", gBS);
    Print (L"  Runtime Services : 0x%p\n", gRT);
    Print (L"  SystemTable      : 0x%p\n", gST);
    Print (L"  SystemTable Size : %u bytes\n", gST->Hdr.HeaderSize);
    Print (L"  BS Header Size   : %u bytes\n", gBS->Hdr.HeaderSize);
    Print (L"  RT Header Size   : %u bytes\n", gRT->Hdr.HeaderSize);

    gST->ConOut->QueryMode (gST->ConOut, gST->ConOut->Mode->Mode, &Columns, &Rows);
    Print (L"  Console Mode     : %u x %u\n", Columns, Rows);

    {
      UINT64  MonoCount;

      if (!EFI_ERROR (gBS->GetNextMonotonicCount (&MonoCount))) {
        Print (L"  Monotonic Count  : %lu\n", MonoCount);
      }
    }
  }
}

/**
  Print usage information.
**/
STATIC
VOID
PrintUsage (
  VOID
  )
{
  Print (L"Usage: ShellCommand.efi [-v]\n\n");
  Print (L"Options:\n");
  Print (L"  -v    Enable verbose output\n");
  Print (L"  -h    Show this help message\n");
}

/**
  Shell application entry point (ShellCEntryLib).

  @param[in] Argc  Argument count.
  @param[in] Argv  Argument vector (wide strings).

  @retval SHELL_SUCCESS  Completed.
**/
INTN
EFIAPI
ShellAppMain (
  IN UINTN   Argc,
  IN CHAR16  **Argv
  )
{
  BOOLEAN  Verbose;
  UINTN    Index;

  Verbose = FALSE;

  //
  // Parse arguments.
  //
  for (Index = 1; Index < Argc; Index++) {
    if (StrCmp (Argv[Index], L"-v") == 0 ||
        StrCmp (Argv[Index], L"--verbose") == 0)
    {
      Verbose = TRUE;
    } else if (StrCmp (Argv[Index], L"-h") == 0 ||
               StrCmp (Argv[Index], L"--help") == 0)
    {
      PrintUsage ();
      return SHELL_SUCCESS;
    } else {
      Print (L"Unknown option: %s\n\n", Argv[Index]);
      PrintUsage ();
      return SHELL_INVALID_PARAMETER;
    }
  }

  Print (L"\n");
  PrintSysInfo (Verbose);
  Print (L"\n");

  return SHELL_SUCCESS;
}
