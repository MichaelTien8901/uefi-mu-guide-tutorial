/** @file
  NetworkApp.c -- TCP4 connection example (simplified).

  Demonstrates:
    - Locating TCP4 Service Binding Protocol
    - Creating a TCP4 child instance
    - Configuring and connecting to a remote host
    - Sending an HTTP GET request
    - Receiving and printing the response
    - Destroying the TCP4 child

  NOTE: This is a simplified educational example. A production-quality
  network application would need more robust error handling, timeouts,
  and proper HTTP parsing.

  Copyright (c) 2026, UEFI Mu Guide Contributors. All rights reserved.
  SPDX-License-Identifier: BSD-2-Clause-Patent
**/

#include <UefiMuGuide.h>
#include <Protocol/Tcp4.h>
#include <Protocol/ServiceBinding.h>

//
// Hardcoded target for the example.
//
#define TARGET_IP_0    93
#define TARGET_IP_1    184
#define TARGET_IP_2    216
#define TARGET_IP_3    34
#define TARGET_PORT    80

#define LOCAL_IP_0     0
#define LOCAL_IP_1     0
#define LOCAL_IP_2     0
#define LOCAL_IP_3     0

STATIC CHAR8  mHttpGet[] = "GET / HTTP/1.0\r\nHost: example.com\r\n\r\n";

/**
  Completion callback -- signals the event to unblock WaitForEvent.
**/
STATIC
VOID
EFIAPI
TcpCompletion (
  IN EFI_EVENT  Event,
  IN VOID       *Context
  )
{
  // Nothing to do; the event signal is enough.
}

/**
  Application entry point.
**/
EFI_STATUS
EFIAPI
NetworkAppEntry (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
  EFI_STATUS                    Status;
  EFI_SERVICE_BINDING_PROTOCOL  *TcpSb;
  EFI_TCP4_PROTOCOL             *Tcp4;
  EFI_HANDLE                    TcpHandle;
  EFI_TCP4_CONFIG_DATA          ConfigData;
  EFI_TCP4_ACCESS_POINT         *AccessPoint;
  EFI_TCP4_CONNECTION_TOKEN     ConnToken;
  EFI_TCP4_IO_TOKEN             TxToken;
  EFI_TCP4_IO_TOKEN             RxToken;
  EFI_TCP4_TRANSMIT_DATA        TxData;
  EFI_TCP4_RECEIVE_DATA         RxData;
  EFI_TCP4_FRAGMENT_DATA        TxFragment;
  EFI_TCP4_FRAGMENT_DATA        RxFragment;
  CHAR8                         RxBuffer[1024];
  UINTN                         EventIndex;

  Print (L"=== Network App (TCP4) ===\n\n");

  //
  // Step 1: Locate TCP4 Service Binding.
  //
  Status = gBS->LocateProtocol (
                  &gEfiTcp4ServiceBindingProtocolGuid,
                  NULL,
                  (VOID **)&TcpSb
                  );
  if (EFI_ERROR (Status)) {
    Print (L"TCP4 Service Binding not found - %r\n", Status);
    Print (L"  (Ensure network stack is enabled in firmware.)\n");
    WAIT_FOR_KEY (SystemTable);
    return Status;
  }

  //
  // Step 2: Create a TCP4 child.
  //
  TcpHandle = NULL;
  Status = TcpSb->CreateChild (TcpSb, &TcpHandle);
  CHECK_STATUS_RETURN (Status, "CreateChild");

  Status = gBS->HandleProtocol (TcpHandle, &gEfiTcp4ProtocolGuid, (VOID **)&Tcp4);
  CHECK_STATUS_RETURN (Status, "HandleProtocol TCP4");

  Print (L"TCP4 child created on handle 0x%p\n", TcpHandle);

  //
  // Step 3: Configure the connection.
  //
  ZeroMem (&ConfigData, sizeof (ConfigData));
  ConfigData.TypeOfService          = 0;
  ConfigData.TimeToLive             = 64;

  AccessPoint = &ConfigData.AccessPoint;
  AccessPoint->UseDefaultAddress    = TRUE;
  AccessPoint->StationPort          = 0;         // Ephemeral
  AccessPoint->RemoteAddress.Addr[0] = TARGET_IP_0;
  AccessPoint->RemoteAddress.Addr[1] = TARGET_IP_1;
  AccessPoint->RemoteAddress.Addr[2] = TARGET_IP_2;
  AccessPoint->RemoteAddress.Addr[3] = TARGET_IP_3;
  AccessPoint->RemotePort            = TARGET_PORT;
  AccessPoint->ActiveFlag            = TRUE;

  Status = Tcp4->Configure (Tcp4, &ConfigData);
  if (EFI_ERROR (Status)) {
    Print (L"TCP4 Configure failed: %r\n", Status);
    goto Cleanup;
  }

  Print (L"Configured: connecting to %u.%u.%u.%u:%u...\n",
         TARGET_IP_0, TARGET_IP_1, TARGET_IP_2, TARGET_IP_3, TARGET_PORT);

  //
  // Step 4: Connect.
  //
  ZeroMem (&ConnToken, sizeof (ConnToken));
  Status = gBS->CreateEvent (EVT_NOTIFY_SIGNAL, TPL_CALLBACK,
                             TcpCompletion, NULL, &ConnToken.CompletionToken.Event);
  CHECK_STATUS_RETURN (Status, "CreateEvent (connect)");

  Status = Tcp4->Connect (Tcp4, &ConnToken);
  if (Status == EFI_SUCCESS) {
    // Completed immediately
  } else if (Status == EFI_NOT_READY) {
    gBS->WaitForEvent (1, &ConnToken.CompletionToken.Event, &EventIndex);
    Status = ConnToken.CompletionToken.Status;
  } else {
    Print (L"Connect failed: %r\n", Status);
    goto Cleanup;
  }

  if (EFI_ERROR (Status)) {
    Print (L"Connection failed: %r\n", Status);
    goto Cleanup;
  }

  Print (L"Connected!\n\n");

  //
  // Step 5: Send HTTP GET.
  //
  ZeroMem (&TxToken, sizeof (TxToken));
  Status = gBS->CreateEvent (EVT_NOTIFY_SIGNAL, TPL_CALLBACK,
                             TcpCompletion, NULL, &TxToken.CompletionToken.Event);
  CHECK_STATUS_RETURN (Status, "CreateEvent (tx)");

  TxFragment.FragmentLength = (UINT32)AsciiStrLen (mHttpGet);
  TxFragment.FragmentBuffer = mHttpGet;
  TxData.Push               = TRUE;
  TxData.Urgent             = FALSE;
  TxData.DataLength         = TxFragment.FragmentLength;
  TxData.FragmentCount      = 1;
  TxData.FragmentTable[0]   = TxFragment;
  TxToken.Packet.TxData     = &TxData;

  Print (L"Sending HTTP GET (%u bytes)...\n", TxFragment.FragmentLength);
  Status = Tcp4->Transmit (Tcp4, &TxToken);
  if (!EFI_ERROR (Status) || Status == EFI_SUCCESS) {
    gBS->WaitForEvent (1, &TxToken.CompletionToken.Event, &EventIndex);
  }

  //
  // Step 6: Receive response.
  //
  ZeroMem (&RxToken, sizeof (RxToken));
  Status = gBS->CreateEvent (EVT_NOTIFY_SIGNAL, TPL_CALLBACK,
                             TcpCompletion, NULL, &RxToken.CompletionToken.Event);
  CHECK_STATUS_RETURN (Status, "CreateEvent (rx)");

  ZeroMem (RxBuffer, sizeof (RxBuffer));
  RxFragment.FragmentLength = sizeof (RxBuffer) - 1;
  RxFragment.FragmentBuffer = RxBuffer;
  RxData.UrgentFlag         = FALSE;
  RxData.DataLength         = RxFragment.FragmentLength;
  RxData.FragmentCount      = 1;
  RxData.FragmentTable[0]   = RxFragment;
  RxToken.Packet.RxData     = &RxData;

  Print (L"Waiting for response...\n");
  Status = Tcp4->Receive (Tcp4, &RxToken);
  if (!EFI_ERROR (Status)) {
    gBS->WaitForEvent (1, &RxToken.CompletionToken.Event, &EventIndex);
    Status = RxToken.CompletionToken.Status;
  }

  if (!EFI_ERROR (Status)) {
    Print (L"\nReceived %u bytes:\n", RxFragment.FragmentLength);
    //
    // Print first portion of response as ASCII.
    //
    RxBuffer[RxFragment.FragmentLength] = '\0';
    Print (L"--- Response Start ---\n");
    Print (L"%a\n", RxBuffer);
    Print (L"--- Response End ---\n");
  } else {
    Print (L"Receive failed: %r\n", Status);
  }

Cleanup:
  //
  // Destroy the TCP4 child.
  //
  if (ConnToken.CompletionToken.Event != NULL) {
    gBS->CloseEvent (ConnToken.CompletionToken.Event);
  }

  if (TxToken.CompletionToken.Event != NULL) {
    gBS->CloseEvent (TxToken.CompletionToken.Event);
  }

  if (RxToken.CompletionToken.Event != NULL) {
    gBS->CloseEvent (RxToken.CompletionToken.Event);
  }

  Tcp4->Configure (Tcp4, NULL);
  TcpSb->DestroyChild (TcpSb, TcpHandle);
  Print (L"\nTCP4 child destroyed. Done.\n");

  WAIT_FOR_KEY (SystemTable);
  return EFI_SUCCESS;
}
