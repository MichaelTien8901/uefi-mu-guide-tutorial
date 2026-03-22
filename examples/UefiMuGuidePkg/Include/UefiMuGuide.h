/** @file
  UefiMuGuide.h -- Common header for UEFI Mu Guide examples.

  Provides standard UEFI includes and utility macros used across all
  example applications and drivers in this package.

  Copyright (c) 2026, UEFI Mu Guide Contributors. All rights reserved.
  SPDX-License-Identifier: BSD-2-Clause-Patent
**/

#ifndef UEFI_MU_GUIDE_H_
#define UEFI_MU_GUIDE_H_

//
// Standard UEFI headers
//
#include <Uefi.h>
#include <Library/UefiLib.h>
#include <Library/BaseLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/DebugLib.h>
#include <Library/PrintLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>

//
// Common macros
//

/// Check an EFI_STATUS and print an error message on failure.
#define CHECK_STATUS(Status, Message)                         \
  do {                                                        \
    if (EFI_ERROR (Status)) {                                 \
      DEBUG ((DEBUG_ERROR, "ERROR: %a - %r\n", Message, Status)); \
      Print (L"ERROR: %a - %r\n", Message, Status);          \
    }                                                         \
  } while (0)

/// Check an EFI_STATUS and return on failure.
#define CHECK_STATUS_RETURN(Status, Message)                   \
  do {                                                         \
    if (EFI_ERROR (Status)) {                                  \
      DEBUG ((DEBUG_ERROR, "ERROR: %a - %r\n", Message, Status)); \
      Print (L"ERROR: %a - %r\n", Message, Status);           \
      return Status;                                           \
    }                                                          \
  } while (0)

/// Size in bytes for a given number of UEFI pages (4 KiB each).
#define PAGES_TO_BYTES(Pages)  ((Pages) * EFI_PAGE_SIZE)

/// Number of pages needed for a given byte count.
#define BYTES_TO_PAGES(Bytes)  (((Bytes) + EFI_PAGE_SIZE - 1) / EFI_PAGE_SIZE)

/// Helper to wait for a single keypress.
#define WAIT_FOR_KEY(SystemTable)                              \
  do {                                                         \
    EFI_INPUT_KEY  _Key;                                       \
    UINTN          _Index;                                     \
    Print (L"\nPress any key to continue...\n");               \
    gBS->WaitForEvent (1, &(SystemTable)->ConIn->WaitForKey, &_Index); \
    (SystemTable)->ConIn->ReadKeyStroke ((SystemTable)->ConIn, &_Key); \
  } while (0)

#endif // UEFI_MU_GUIDE_H_
