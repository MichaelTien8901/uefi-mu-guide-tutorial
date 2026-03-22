## @file
#  UefiMuGuidePkg.dsc - Build description for UEFI Mu Guide examples.
#
#  Copyright (c) 2026, UEFI Mu Guide Contributors. All rights reserved.
#  SPDX-License-Identifier: BSD-2-Clause-Patent
#
##

[Defines]
  PLATFORM_NAME                  = UefiMuGuidePkg
  PLATFORM_GUID                  = 5E6F7A8B-9C0D-4E1F-A2B3-C4D5E6F7A8B9
  PLATFORM_VERSION               = 1.0
  DSC_SPECIFICATION              = 0x00010005
  OUTPUT_DIRECTORY               = Build/UefiMuGuidePkg
  SUPPORTED_ARCHITECTURES        = X64|IA32|AARCH64
  BUILD_TARGETS                  = DEBUG|RELEASE|NOOPT
  SKUID_IDENTIFIER               = DEFAULT

[Packages]
  MdePkg/MdePkg.dec
  MdeModulePkg/MdeModulePkg.dec
  ShellPkg/ShellPkg.dec
  UefiMuGuidePkg/UefiMuGuidePkg.dec

[LibraryClasses]
  #
  # Entry point libraries
  #
  UefiApplicationEntryPoint|MdePkg/Library/UefiApplicationEntryPoint/UefiApplicationEntryPoint.inf
  UefiDriverEntryPoint|MdePkg/Library/UefiDriverEntryPoint/UefiDriverEntryPoint.inf
  ShellCEntryLib|ShellPkg/Library/UefiShellCEntryLib/UefiShellCEntryLib.inf

  #
  # Core UEFI libraries
  #
  UefiLib|MdePkg/Library/UefiLib/UefiLib.inf
  UefiBootServicesTableLib|MdePkg/Library/UefiBootServicesTableLib/UefiBootServicesTableLib.inf
  UefiRuntimeServicesTableLib|MdePkg/Library/UefiRuntimeServicesTableLib/UefiRuntimeServicesTableLib.inf

  #
  # Base libraries
  #
  BaseLib|MdePkg/Library/BaseLib/BaseLib.inf
  BaseMemoryLib|MdePkg/Library/BaseMemoryLib/BaseMemoryLib.inf
  MemoryAllocationLib|MdePkg/Library/UefiMemoryAllocationLib/UefiMemoryAllocationLib.inf
  PrintLib|MdePkg/Library/BasePrintLib/BasePrintLib.inf
  DebugLib|MdePkg/Library/UefiDebugLibConOut/UefiDebugLibConOut.inf
  DebugPrintErrorLevelLib|MdePkg/Library/BaseDebugPrintErrorLevelLib/BaseDebugPrintErrorLevelLib.inf

  #
  # Device path and misc libraries
  #
  DevicePathLib|MdePkg/Library/UefiDevicePathLib/UefiDevicePathLib.inf
  PcdLib|MdePkg/Library/BasePcdLibNull/BasePcdLibNull.inf
  RegisterFilterLib|MdePkg/Library/RegisterFilterLibNull/RegisterFilterLibNull.inf

  #
  # Shell libraries
  #
  ShellLib|ShellPkg/Library/UefiShellLib/UefiShellLib.inf
  FileHandleLib|MdePkg/Library/UefiFileHandleLib/UefiFileHandleLib.inf
  HiiLib|MdeModulePkg/Library/UefiHiiLib/UefiHiiLib.inf
  SortLib|MdeModulePkg/Library/UefiSortLib/UefiSortLib.inf
  UefiHiiServicesLib|MdeModulePkg/Library/UefiHiiServicesLib/UefiHiiServicesLib.inf

[LibraryClasses.common.UEFI_DRIVER]
  UefiDriverEntryPoint|MdePkg/Library/UefiDriverEntryPoint/UefiDriverEntryPoint.inf

[Components]
  #
  # UEFI Applications
  #
  UefiMuGuidePkg/HelloWorld/HelloWorld.inf
  UefiMuGuidePkg/ProtocolExample/ProtocolExample.inf
  UefiMuGuidePkg/MemoryExample/MemoryExample.inf
  UefiMuGuidePkg/ServicesExample/ServicesExample.inf
  UefiMuGuidePkg/ConsoleExample/ConsoleExample.inf
  UefiMuGuidePkg/GopExample/GopExample.inf
  UefiMuGuidePkg/FileSystemExample/FileSystemExample.inf
  UefiMuGuidePkg/BlockIoExample/BlockIoExample.inf
  UefiMuGuidePkg/NetworkExample/NetworkExample.inf
  UefiMuGuidePkg/VariableExample/VariableExample.inf
  UefiMuGuidePkg/NetworkApp/NetworkApp.inf
  UefiMuGuidePkg/ShellCommand/ShellCommand.inf
  UefiMuGuidePkg/BootMenu/BootMenu.inf
  UefiMuGuidePkg/BootLoader/BootLoader.inf

  #
  # UEFI Drivers
  #
  UefiMuGuidePkg/DriverExample/DriverExample.inf
