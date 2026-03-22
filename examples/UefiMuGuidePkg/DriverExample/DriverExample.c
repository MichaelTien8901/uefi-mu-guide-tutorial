/** @file
  DriverExample.c -- Simple DXE driver with EFI_DRIVER_BINDING_PROTOCOL.

  Demonstrates the UEFI driver model:
    - Implementing Supported/Start/Stop functions
    - Installing the Driver Binding Protocol on the image handle
    - Unloading the driver cleanly

  Copyright (c) 2026, UEFI Mu Guide Contributors. All rights reserved.
  SPDX-License-Identifier: BSD-2-Clause-Patent
**/

#include <UefiMuGuide.h>
#include <Protocol/DriverBinding.h>
#include <Protocol/ComponentName.h>

//
// Forward declarations for the Driver Binding Protocol functions.
//
EFI_STATUS EFIAPI DriverSupported (
  IN EFI_DRIVER_BINDING_PROTOCOL  *This,
  IN EFI_HANDLE                   ControllerHandle,
  IN EFI_DEVICE_PATH_PROTOCOL     *RemainingDevicePath OPTIONAL
  );

EFI_STATUS EFIAPI DriverStart (
  IN EFI_DRIVER_BINDING_PROTOCOL  *This,
  IN EFI_HANDLE                   ControllerHandle,
  IN EFI_DEVICE_PATH_PROTOCOL     *RemainingDevicePath OPTIONAL
  );

EFI_STATUS EFIAPI DriverStop (
  IN EFI_DRIVER_BINDING_PROTOCOL  *This,
  IN EFI_HANDLE                   ControllerHandle,
  IN UINTN                        NumberOfChildren,
  IN EFI_HANDLE                   *ChildHandleBuffer OPTIONAL
  );

//
// Driver Binding Protocol instance.
//
STATIC EFI_DRIVER_BINDING_PROTOCOL  gDriverBinding = {
  DriverSupported,
  DriverStart,
  DriverStop,
  0x10,       // Version
  NULL,       // ImageHandle  (filled in at entry)
  NULL        // DriverBindingHandle (filled in at entry)
};

/**
  Test whether this driver supports a given controller.

  In this example we always return EFI_UNSUPPORTED because this is a
  skeleton driver.  A real driver would check for required protocols
  on the controller handle (e.g., PciIo, UsbIo).

  @retval EFI_UNSUPPORTED  Always -- skeleton only.
**/
EFI_STATUS
EFIAPI
DriverSupported (
  IN EFI_DRIVER_BINDING_PROTOCOL  *This,
  IN EFI_HANDLE                   ControllerHandle,
  IN EFI_DEVICE_PATH_PROTOCOL     *RemainingDevicePath OPTIONAL
  )
{
  DEBUG ((DEBUG_VERBOSE, "DriverExample: Supported() called for handle 0x%p\n",
          ControllerHandle));
  //
  // A real driver would open protocols on ControllerHandle here and
  // return EFI_SUCCESS if it can manage the device.
  //
  return EFI_UNSUPPORTED;
}

/**
  Start managing a controller.

  @retval EFI_UNSUPPORTED  Always -- skeleton only.
**/
EFI_STATUS
EFIAPI
DriverStart (
  IN EFI_DRIVER_BINDING_PROTOCOL  *This,
  IN EFI_HANDLE                   ControllerHandle,
  IN EFI_DEVICE_PATH_PROTOCOL     *RemainingDevicePath OPTIONAL
  )
{
  DEBUG ((DEBUG_INFO, "DriverExample: Start() called for handle 0x%p\n",
          ControllerHandle));
  //
  // A real driver would allocate private data, open protocols
  // BY_DRIVER, and install child protocols here.
  //
  return EFI_UNSUPPORTED;
}

/**
  Stop managing a controller.

  @retval EFI_SUCCESS  Always succeeds for the skeleton.
**/
EFI_STATUS
EFIAPI
DriverStop (
  IN EFI_DRIVER_BINDING_PROTOCOL  *This,
  IN EFI_HANDLE                   ControllerHandle,
  IN UINTN                        NumberOfChildren,
  IN EFI_HANDLE                   *ChildHandleBuffer OPTIONAL
  )
{
  DEBUG ((DEBUG_INFO, "DriverExample: Stop() called for handle 0x%p\n",
          ControllerHandle));
  //
  // A real driver would free resources, close protocols, and
  // uninstall child handles here.
  //
  return EFI_SUCCESS;
}

/**
  Unload handler -- called when the driver image is unloaded.

  @retval EFI_SUCCESS  Driver binding uninstalled.
**/
EFI_STATUS
EFIAPI
DriverExampleUnload (
  IN EFI_HANDLE  ImageHandle
  )
{
  EFI_STATUS  Status;

  DEBUG ((DEBUG_INFO, "DriverExample: Unloading driver.\n"));

  Status = gBS->UninstallMultipleProtocolInterfaces (
                  gDriverBinding.DriverBindingHandle,
                  &gEfiDriverBindingProtocolGuid,
                  &gDriverBinding,
                  NULL
                  );

  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "DriverExample: Failed to uninstall binding - %r\n", Status));
  }

  return Status;
}

/**
  Driver entry point.

  Installs the Driver Binding Protocol so that the UEFI connect
  controller logic can find us.

  @retval EFI_SUCCESS  Driver binding installed.
**/
EFI_STATUS
EFIAPI
DriverExampleEntry (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
  EFI_STATUS  Status;

  DEBUG ((DEBUG_INFO, "DriverExample: Entry -- installing Driver Binding.\n"));

  //
  // Fill in the image and binding handles.
  //
  gDriverBinding.ImageHandle        = ImageHandle;
  gDriverBinding.DriverBindingHandle = ImageHandle;

  //
  // Install the Driver Binding Protocol onto our image handle.
  //
  Status = gBS->InstallMultipleProtocolInterfaces (
                  &gDriverBinding.DriverBindingHandle,
                  &gEfiDriverBindingProtocolGuid,
                  &gDriverBinding,
                  NULL
                  );

  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "DriverExample: InstallProtocol failed - %r\n", Status));
  } else {
    DEBUG ((DEBUG_INFO, "DriverExample: Driver Binding installed on handle 0x%p\n",
            gDriverBinding.DriverBindingHandle));
  }

  return Status;
}
