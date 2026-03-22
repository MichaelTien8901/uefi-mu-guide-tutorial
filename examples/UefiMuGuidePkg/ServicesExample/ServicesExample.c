/** @file
  ServicesExample.c -- Timer events and boot/runtime services demonstration.

  Demonstrates:
    - Creating timer events with CreateEvent
    - Setting periodic and one-shot timers with SetTimer
    - Waiting for events with WaitForEvent
    - Querying EFI_BOOT_SERVICES and EFI_RUNTIME_SERVICES table info

  Copyright (c) 2026, UEFI Mu Guide Contributors. All rights reserved.
  SPDX-License-Identifier: BSD-2-Clause-Patent
**/

#include <UefiMuGuide.h>

STATIC volatile UINTN  mTimerCount = 0;

/**
  Timer notification callback.  Increments a counter each time fired.
**/
STATIC
VOID
EFIAPI
TimerNotify (
  IN EFI_EVENT  Event,
  IN VOID       *Context
  )
{
  mTimerCount++;
  DEBUG ((DEBUG_INFO, "ServicesExample: Timer fired, count = %u\n", mTimerCount));
}

/**
  Demonstrate creating and using a periodic timer event.
**/
STATIC
EFI_STATUS
DemoTimerEvent (
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
  EFI_STATUS  Status;
  EFI_EVENT   TimerEvent;
  UINTN       Index;

  Print (L"[Timer] Creating periodic timer (100ms interval)...\n");

  Status = gBS->CreateEvent (
                  EVT_TIMER | EVT_NOTIFY_SIGNAL,
                  TPL_CALLBACK,
                  TimerNotify,
                  NULL,
                  &TimerEvent
                  );
  CHECK_STATUS_RETURN (Status, "CreateEvent");

  //
  // Set a periodic timer: 100ms = 1,000,000 * 100ns ticks.
  //
  Status = gBS->SetTimer (TimerEvent, TimerPeriodic, 1000000);
  CHECK_STATUS_RETURN (Status, "SetTimer");

  //
  // Wait approximately 500ms by stalling.
  //
  Print (L"  Waiting ~500ms for timer callbacks...\n");
  gBS->Stall (500000);  // 500,000 microseconds

  //
  // Cancel the timer and close the event.
  //
  gBS->SetTimer (TimerEvent, TimerCancel, 0);
  gBS->CloseEvent (TimerEvent);

  Print (L"  Timer fired %u times.\n\n", mTimerCount);

  //
  // Demonstrate a one-shot WaitForEvent with the keyboard.
  //
  Print (L"[WaitForEvent] Waiting for a keypress (5s timeout)...\n");

  //
  // Create a one-shot timer for the timeout.
  //
  Status = gBS->CreateEvent (EVT_TIMER, TPL_APPLICATION, NULL, NULL, &TimerEvent);
  CHECK_STATUS_RETURN (Status, "CreateEvent (timeout)");

  Status = gBS->SetTimer (TimerEvent, TimerRelative, 50000000);  // 5 seconds
  CHECK_STATUS_RETURN (Status, "SetTimer (timeout)");

  //
  // Wait for either the key or the timeout.
  //
  {
    EFI_EVENT  WaitList[2];

    WaitList[0] = SystemTable->ConIn->WaitForKey;
    WaitList[1] = TimerEvent;

    Status = gBS->WaitForEvent (2, WaitList, &Index);
    if (!EFI_ERROR (Status)) {
      if (Index == 0) {
        EFI_INPUT_KEY  Key;

        SystemTable->ConIn->ReadKeyStroke (SystemTable->ConIn, &Key);
        Print (L"  Key pressed! (Unicode=0x%04X)\n", Key.UnicodeChar);
      } else {
        Print (L"  Timeout -- no key pressed within 5 seconds.\n");
      }
    }
  }

  gBS->CloseEvent (TimerEvent);
  return EFI_SUCCESS;
}

/**
  Print information about Boot Services and Runtime Services tables.
**/
STATIC
VOID
PrintServiceTableInfo (
  VOID
  )
{
  Print (L"\n[Service Tables]\n");
  Print (L"  Boot Services Table:\n");
  Print (L"    Signature : 0x%lX\n", gBS->Hdr.Signature);
  Print (L"    Revision  : 0x%08X\n", gBS->Hdr.Revision);
  Print (L"    HeaderSize: %u bytes\n", gBS->Hdr.HeaderSize);

  Print (L"  Runtime Services Table:\n");
  Print (L"    Signature : 0x%lX\n", gRT->Hdr.Signature);
  Print (L"    Revision  : 0x%08X\n", gRT->Hdr.Revision);
  Print (L"    HeaderSize: %u bytes\n", gRT->Hdr.HeaderSize);

  //
  // Demonstrate GetNextMonotonicCount.
  //
  {
    UINT64      MonotonicCount;
    EFI_STATUS  Status;

    Status = gBS->GetNextMonotonicCount (&MonotonicCount);
    if (!EFI_ERROR (Status)) {
      Print (L"\n  Monotonic Count: %lu\n", MonotonicCount);
    }
  }

  //
  // Read the current time via Runtime Services.
  //
  {
    EFI_TIME    Time;
    EFI_STATUS  Status;

    Status = gRT->GetTime (&Time, NULL);
    if (!EFI_ERROR (Status)) {
      Print (L"  Current Time   : %04u-%02u-%02u %02u:%02u:%02u\n",
             Time.Year, Time.Month, Time.Day,
             Time.Hour, Time.Minute, Time.Second);
    }
  }
}

/**
  Application entry point.
**/
EFI_STATUS
EFIAPI
ServicesExampleEntry (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
  Print (L"=== Services Example ===\n\n");

  DemoTimerEvent (SystemTable);
  PrintServiceTableInfo ();

  WAIT_FOR_KEY (SystemTable);
  return EFI_SUCCESS;
}
