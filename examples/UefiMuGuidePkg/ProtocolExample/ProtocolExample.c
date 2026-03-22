/** @file
  ProtocolExample.c -- Custom UEFI protocol definition and usage.

  Demonstrates:
    - Defining a custom protocol structure (CALCULATOR_PROTOCOL)
    - Installing a protocol onto a new handle
    - Locating a protocol by GUID
    - Using the protocol's functions
    - Uninstalling the protocol on cleanup

  Copyright (c) 2026, UEFI Mu Guide Contributors. All rights reserved.
  SPDX-License-Identifier: BSD-2-Clause-Patent
**/

#include <UefiMuGuide.h>

//
// Protocol GUID -- must match the .dec declaration.
//
extern EFI_GUID  gCalculatorProtocolGuid;

//
// Forward declarations for protocol function types.
//
typedef struct _CALCULATOR_PROTOCOL CALCULATOR_PROTOCOL;

typedef
EFI_STATUS
(EFIAPI *CALCULATOR_ADD)(
  IN  CALCULATOR_PROTOCOL  *This,
  IN  INTN                 A,
  IN  INTN                 B,
  OUT INTN                 *Result
  );

typedef
EFI_STATUS
(EFIAPI *CALCULATOR_SUBTRACT)(
  IN  CALCULATOR_PROTOCOL  *This,
  IN  INTN                 A,
  IN  INTN                 B,
  OUT INTN                 *Result
  );

//
// Protocol structure.
//
struct _CALCULATOR_PROTOCOL {
  UINT64               Revision;
  CALCULATOR_ADD       Add;
  CALCULATOR_SUBTRACT  Subtract;
};

//
// ----- Protocol implementation -----
//

STATIC
EFI_STATUS
EFIAPI
CalcAdd (
  IN  CALCULATOR_PROTOCOL  *This,
  IN  INTN                 A,
  IN  INTN                 B,
  OUT INTN                 *Result
  )
{
  if (Result == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  *Result = A + B;
  DEBUG ((DEBUG_INFO, "Calculator: %d + %d = %d\n", A, B, *Result));
  return EFI_SUCCESS;
}

STATIC
EFI_STATUS
EFIAPI
CalcSubtract (
  IN  CALCULATOR_PROTOCOL  *This,
  IN  INTN                 A,
  IN  INTN                 B,
  OUT INTN                 *Result
  )
{
  if (Result == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  *Result = A - B;
  DEBUG ((DEBUG_INFO, "Calculator: %d - %d = %d\n", A, B, *Result));
  return EFI_SUCCESS;
}

//
// Protocol instance.
//
STATIC CALCULATOR_PROTOCOL  mCalculator = {
  0x00010000,   // Revision 1.0
  CalcAdd,
  CalcSubtract
};

/**
  Entry point: install the protocol, locate it, exercise it, then clean up.
**/
EFI_STATUS
EFIAPI
ProtocolExampleEntry (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
  EFI_STATUS           Status;
  EFI_HANDLE           ProtocolHandle;
  CALCULATOR_PROTOCOL  *Calc;
  INTN                 Result;

  Print (L"ProtocolExample: Installing Calculator Protocol...\n");

  //
  // Install the protocol on a new (NULL) handle.
  //
  ProtocolHandle = NULL;
  Status = gBS->InstallProtocolInterface (
                  &ProtocolHandle,
                  &gCalculatorProtocolGuid,
                  EFI_NATIVE_INTERFACE,
                  &mCalculator
                  );
  CHECK_STATUS_RETURN (Status, "InstallProtocolInterface");
  Print (L"  Installed on handle 0x%p\n", ProtocolHandle);

  //
  // Locate the protocol we just installed.
  //
  Status = gBS->LocateProtocol (
                  &gCalculatorProtocolGuid,
                  NULL,
                  (VOID **)&Calc
                  );
  CHECK_STATUS_RETURN (Status, "LocateProtocol");
  Print (L"  Located protocol at 0x%p  (Revision 0x%08lX)\n",
         Calc, Calc->Revision);

  //
  // Use the protocol.
  //
  Print (L"\nPerforming calculations:\n");

  Status = Calc->Add (Calc, 42, 18, &Result);
  if (!EFI_ERROR (Status)) {
    Print (L"  42 + 18 = %d\n", Result);
  }

  Status = Calc->Subtract (Calc, 100, 37, &Result);
  if (!EFI_ERROR (Status)) {
    Print (L"  100 - 37 = %d\n", Result);
  }

  Status = Calc->Add (Calc, -5, 15, &Result);
  if (!EFI_ERROR (Status)) {
    Print (L"  -5 + 15 = %d\n", Result);
  }

  //
  // Test error handling: pass NULL result.
  //
  Status = Calc->Add (Calc, 1, 2, NULL);
  Print (L"  Add(1,2,NULL) => %r (expected INVALID_PARAMETER)\n", Status);

  //
  // Uninstall the protocol.
  //
  Print (L"\nUninstalling Calculator Protocol...\n");
  Status = gBS->UninstallProtocolInterface (
                  ProtocolHandle,
                  &gCalculatorProtocolGuid,
                  &mCalculator
                  );
  CHECK_STATUS (Status, "UninstallProtocolInterface");
  Print (L"  Done.\n");

  WAIT_FOR_KEY (SystemTable);
  return EFI_SUCCESS;
}
