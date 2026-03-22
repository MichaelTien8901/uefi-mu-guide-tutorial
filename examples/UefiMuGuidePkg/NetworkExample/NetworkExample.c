/** @file
  NetworkExample.c -- Network interface enumeration and MAC display.

  Demonstrates:
    - Locating all EFI_SIMPLE_NETWORK_PROTOCOL handles
    - Reading MAC addresses from SNP mode data
    - Checking link status for each NIC

  Copyright (c) 2026, UEFI Mu Guide Contributors. All rights reserved.
  SPDX-License-Identifier: BSD-2-Clause-Patent
**/

#include <UefiMuGuide.h>
#include <Protocol/SimpleNetwork.h>

/**
  Print a MAC address.
**/
STATIC
VOID
PrintMacAddress (
  IN EFI_MAC_ADDRESS  *Mac,
  IN UINT32           Length
  )
{
  UINT32  Index;

  for (Index = 0; Index < Length; Index++) {
    Print (L"%02X", Mac->Addr[Index]);
    if (Index < Length - 1) {
      Print (L":");
    }
  }
}

/**
  Return a string describing the SNP state.
**/
STATIC
CONST CHAR16 *
SnpStateName (
  IN UINT32  State
  )
{
  switch (State) {
    case EfiSimpleNetworkStopped:
      return L"Stopped";
    case EfiSimpleNetworkStarted:
      return L"Started";
    case EfiSimpleNetworkInitialized:
      return L"Initialized";
    default:
      return L"Unknown";
  }
}

/**
  Print information about a single network interface.
**/
STATIC
VOID
PrintNicInfo (
  IN UINTN                          Index,
  IN EFI_SIMPLE_NETWORK_PROTOCOL    *Snp
  )
{
  EFI_SIMPLE_NETWORK_MODE  *Mode;

  Mode = Snp->Mode;

  Print (L"\n  NIC #%u:\n", Index);
  Print (L"    State          : %s\n", SnpStateName (Mode->State));
  Print (L"    HW Address Len : %u\n", Mode->HwAddressSize);
  Print (L"    Current MAC    : ");
  PrintMacAddress (&Mode->CurrentAddress, Mode->HwAddressSize);
  Print (L"\n");
  Print (L"    Permanent MAC  : ");
  PrintMacAddress (&Mode->PermanentAddress, Mode->HwAddressSize);
  Print (L"\n");
  Print (L"    Media Present  : %s\n",
         Mode->MediaPresentSupported
           ? (Mode->MediaPresent ? L"Yes (link up)" : L"No (link down)")
           : L"Detection not supported");
  Print (L"    Max Packet Size: %u bytes\n", Mode->MaxPacketSize);
  Print (L"    IF Type        : %u\n", Mode->IfType);
  Print (L"    Receive Filters: 0x%08X\n", Mode->ReceiveFilterSetting);
}

/**
  Application entry point.
**/
EFI_STATUS
EFIAPI
NetworkExampleEntry (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
  EFI_STATUS                      Status;
  EFI_HANDLE                      *HandleBuffer;
  UINTN                           HandleCount;
  UINTN                           Index;
  EFI_SIMPLE_NETWORK_PROTOCOL     *Snp;

  Print (L"=== Network Example ===\n\n");

  //
  // Locate all SNP handles.
  //
  Status = gBS->LocateHandleBuffer (
                  ByProtocol,
                  &gEfiSimpleNetworkProtocolGuid,
                  NULL,
                  &HandleCount,
                  &HandleBuffer
                  );
  if (EFI_ERROR (Status) || HandleCount == 0) {
    Print (L"No network interfaces found - %r\n", Status);
    Print (L"  (This is normal in some QEMU configurations.)\n");
    WAIT_FOR_KEY (SystemTable);
    return EFI_SUCCESS;
  }

  Print (L"Found %u network interface(s):\n", HandleCount);

  for (Index = 0; Index < HandleCount; Index++) {
    Status = gBS->HandleProtocol (
                    HandleBuffer[Index],
                    &gEfiSimpleNetworkProtocolGuid,
                    (VOID **)&Snp
                    );
    if (EFI_ERROR (Status)) {
      Print (L"  NIC #%u: HandleProtocol failed - %r\n", Index, Status);
      continue;
    }

    PrintNicInfo (Index, Snp);
  }

  Print (L"\n  Enumeration complete.\n");

  gBS->FreePool (HandleBuffer);
  WAIT_FOR_KEY (SystemTable);
  return EFI_SUCCESS;
}
