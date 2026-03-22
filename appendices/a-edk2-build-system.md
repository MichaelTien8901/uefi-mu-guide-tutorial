---
layout: default
title: "Appendix A: EDK2 Build System"
nav_order: 1
parent: "Appendices"
permalink: /appendices/edk2-build-system/
---

# Appendix A: EDK2 Build System

This appendix provides a comprehensive reference for the four core file formats used by the EDK2/Project Mu build system: INF (module description), DEC (package declaration), DSC (platform description), and FDF (flash description). It also covers build commands and how stuart wraps the traditional build flow.

---

## A.1 Build System Overview

The EDK2 build system transforms source code and metadata files into firmware images. The flow is:

1. **DSC** (Platform Description) defines what modules to build, which packages to use, and how libraries are resolved.
2. **INF** (Module Information) describes each individual module -- its sources, dependencies, and GUIDs.
3. **DEC** (Package Declaration) defines what a package exports -- protocols, GUIDs, PCDs, include paths.
4. **FDF** (Flash Description) describes the firmware volume layout and how built modules are placed into the final flash image.

The `build` command (or `stuart_build`) reads these files, generates Makefiles, compiles sources, and links binaries.

---

## A.2 INF File Format (Module Information)

The INF file describes a single buildable module (driver, application, library, etc.).

### [Defines] Section

```ini
[Defines]
  INF_VERSION                    = 0x00010017
  BASE_NAME                      = MyDriver
  FILE_GUID                      = 12345678-1234-5678-9ABC-DEF012345678
  MODULE_TYPE                    = DXE_DRIVER
  VERSION_STRING                 = 1.0
  ENTRY_POINT                    = MyDriverEntryPoint

  # Optional defines:
  # UEFI_SPECIFICATION_VERSION   = 0x00020070
  # PI_SPECIFICATION_VERSION     = 0x00010032
  # LIBRARY_CLASS                = MyLib|DXE_DRIVER
  # CONSTRUCTOR                  = MyLibConstructor
  # DESTRUCTOR                   = MyLibDestructor
  # UNLOAD_IMAGE                 = MyDriverUnload
```

| Field | Required | Description |
|-------|----------|-------------|
| `INF_VERSION` | Yes | INF specification version (use `0x00010017` or later) |
| `BASE_NAME` | Yes | Module name used in build output |
| `FILE_GUID` | Yes | Unique GUID identifying this module in firmware volumes |
| `MODULE_TYPE` | Yes | One of: `BASE`, `SEC`, `PEI_CORE`, `PEIM`, `DXE_CORE`, `DXE_DRIVER`, `DXE_RUNTIME_DRIVER`, `DXE_SMM_DRIVER`, `SMM_CORE`, `UEFI_DRIVER`, `UEFI_APPLICATION` |
| `VERSION_STRING` | No | Human-readable version |
| `ENTRY_POINT` | Yes* | Entry point function name (*not for `BASE` library modules) |
| `LIBRARY_CLASS` | No | Declares this module as a library implementation |
| `CONSTRUCTOR` | No | Library constructor called at module load |
| `DESTRUCTOR` | No | Library destructor called at module unload |
| `UNLOAD_IMAGE` | No | Function called when driver is unloaded |

### [Sources] Section

Lists all source files for the module. Architecture-specific sections are supported.

```ini
[Sources]
  MyDriver.c
  MyDriver.h
  Utils.c

[Sources.X64]
  X64/AsmHelper.nasm

[Sources.IA32]
  Ia32/AsmHelper.nasm

[Sources.AARCH64]
  AArch64/ArmHelper.S
```

### [Packages] Section

Lists package DEC files that provide includes, protocols, and GUIDs.

```ini
[Packages]
  MdePkg/MdePkg.dec
  MdeModulePkg/MdeModulePkg.dec
  MyPlatformPkg/MyPlatformPkg.dec
```

### [LibraryClasses] Section

Lists library class dependencies. The DSC file resolves these to concrete implementations.

```ini
[LibraryClasses]
  UefiDriverEntryPoint
  UefiBootServicesTableLib
  UefiLib
  BaseMemoryLib
  DebugLib
  MemoryAllocationLib
```

### [Protocols] Section

Lists protocol GUIDs consumed or produced by this module.

```ini
[Protocols]
  gEfiPciIoProtocolGuid              ## CONSUMES
  gEfiDriverBindingProtocolGuid      ## PRODUCES
  gEfiComponentNameProtocolGuid      ## PRODUCES
```

The `## CONSUMES` / `## PRODUCES` comments are conventions for documentation; the build system does not enforce them.

### [Guids] Section

Lists non-protocol GUIDs used by the module (configuration table entries, variable namespaces, etc.).

```ini
[Guids]
  gEfiGlobalVariableGuid
  gEfiAcpi20TableGuid
  gEfiFileInfoGuid
```

### [Ppis] Section (PEI modules only)

```ini
[Ppis]
  gEfiPeiReadOnlyVariable2PpiGuid   ## CONSUMES
  gEfiPeiMemoryDiscoveredPpiGuid    ## SOMETIMES_CONSUMES
```

### [Pcd] Sections

PCDs (Platform Configuration Database) are build-time and run-time configurable values.

```ini
[Pcd]
  gEfiMdePkgTokenSpaceGuid.PcdDebugPropertyMask

[FixedPcd]
  gEfiMdePkgTokenSpaceGuid.PcdMaximumUnicodeStringLength

[FeaturePcd]
  gEfiMdePkgTokenSpaceGuid.PcdComponentNameDisable

[PatchPcd]
  gMyPkgTokenSpaceGuid.PcdMyPatchableValue
```

| PCD Type | Description | Set At |
|----------|-------------|--------|
| `FixedAtBuild` | Compiled as constants | Build time |
| `PatchableInModule` | Stored in PE data section, patchable post-build | Build or flash tool |
| `DynamicDefault` | Stored in PCD database | Boot time |
| `DynamicHii` | Backed by HII variable | Boot time |
| `DynamicVpd` | Stored in VPD region | Manufacturing |
| `FeatureFlag` | Boolean feature toggle | Build time |

### [Depex] Section

Dependency expression for dispatch ordering (DXE/PEI).

```ini
[Depex]
  gEfiPciIoProtocolGuid AND
  gEfiDevicePathProtocolGuid
```

### [BuildOptions] Section

Module-specific compiler/linker flags.

```ini
[BuildOptions]
  GCC:*_*_*_CC_FLAGS = -Wno-unused-variable
  MSFT:*_*_*_CC_FLAGS = /wd4201
```

The format is `TOOL:TARGET_TOOLCHAIN_ARCH_ATTRIBUTE = flags`.

### [UserExtensions] Section

Vendor-specific extensions; ignored by the base build system.

---

## A.3 DEC File Format (Package Declaration)

The DEC file declares what a package exports to other packages.

### [Defines] Section

```ini
[Defines]
  DEC_SPECIFICATION = 0x00010017
  PACKAGE_NAME      = MyPlatformPkg
  PACKAGE_GUID      = AABBCCDD-1111-2222-3333-444455556666
  PACKAGE_VERSION   = 1.0
```

### [Includes] Section

Public include directories available to consumers of this package.

```ini
[Includes]
  Include

[Includes.X64]
  Include/X64

[Includes.IA32]
  Include/Ia32
```

### [LibraryClasses] Section

Declares library classes with their header file locations.

```ini
[LibraryClasses]
  MyCustomLib|Include/Library/MyCustomLib.h
  PlatformHookLib|Include/Library/PlatformHookLib.h
```

### [Guids] Section

```ini
[Guids]
  gMyPkgTokenSpaceGuid = { 0x12345678, 0xABCD, 0xEF01, { 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF, 0x01 }}
  gMyCustomEventGuid   = { 0xAABBCCDD, 0x1122, 0x3344, { 0x55, 0x66, 0x77, 0x88, 0x99, 0xAA, 0xBB, 0xCC }}
```

### [Protocols] Section

```ini
[Protocols]
  gMyCustomProtocolGuid = { 0x11111111, 0x2222, 0x3333, { 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xAA, 0xBB }}
```

### [Ppis] Section

```ini
[Ppis]
  gMyPeiServicePpiGuid = { 0xDDDDDDDD, 0xEEEE, 0xFFFF, { 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77 }}
```

### [PcdsFixedAtBuild], [PcdsPatchableInModule], [PcdsDynamic], etc.

```ini
[PcdsFixedAtBuild]
  gMyPkgTokenSpaceGuid.PcdMyBufferSize|0x1000|UINT32|0x00000001

[PcdsFeatureFlag]
  gMyPkgTokenSpaceGuid.PcdEnableMyFeature|TRUE|BOOLEAN|0x00000002
```

The format is: `TokenSpaceGuid.PcdName|DefaultValue|DatumType|TokenNumber`

---

## A.4 DSC File Format (Platform Description)

The DSC is the top-level build configuration for a platform. It ties everything together.

### [Defines] Section

```ini
[Defines]
  PLATFORM_NAME           = MyPlatformPkg
  PLATFORM_GUID           = 99887766-5544-3322-1100-AABBCCDDEEFF
  PLATFORM_VERSION        = 1.0
  DSC_SPECIFICATION       = 0x0001001C
  OUTPUT_DIRECTORY        = Build/MyPlatform
  SUPPORTED_ARCHITECTURES = IA32|X64
  BUILD_TARGETS           = DEBUG|RELEASE|NOOPT
  SKUID_IDENTIFIER        = DEFAULT
```

### [LibraryClasses] Section

Maps abstract library class names to concrete INF implementations.

```ini
[LibraryClasses]
  # Base libraries -- used by all module types
  BaseLib|MdePkg/Library/BaseLib/BaseLib.inf
  BaseMemoryLib|MdePkg/Library/BaseMemoryLibRepStr/BaseMemoryLibRepStr.inf
  PrintLib|MdePkg/Library/BasePrintLib/BasePrintLib.inf
  DebugLib|MdePkg/Library/BaseDebugLibNull/BaseDebugLibNull.inf
  PcdLib|MdePkg/Library/BasePcdLibNull/BasePcdLibNull.inf

[LibraryClasses.common.DXE_DRIVER]
  # DXE-specific library mappings
  UefiDriverEntryPoint|MdePkg/Library/UefiDriverEntryPoint/UefiDriverEntryPoint.inf
  UefiBootServicesTableLib|MdePkg/Library/UefiBootServicesTableLib/UefiBootServicesTableLib.inf
  MemoryAllocationLib|MdePkg/Library/UefiMemoryAllocationLib/UefiMemoryAllocationLib.inf

[LibraryClasses.common.UEFI_APPLICATION]
  UefiApplicationEntryPoint|MdePkg/Library/UefiApplicationEntryPoint/UefiApplicationEntryPoint.inf
  ShellLib|ShellPkg/Library/UefiShellLib/UefiShellLib.inf
```

The format for scoped sections is `[LibraryClasses.ARCH.MODULE_TYPE]`.

### [Components] Section

Lists all modules to build.

```ini
[Components]
  MdePkg/Library/BaseLib/BaseLib.inf
  MyPlatformPkg/Drivers/MyDxeDriver/MyDxeDriver.inf {
    <LibraryClasses>
      # Per-module library override
      DebugLib|MdePkg/Library/UefiDebugLibConOut/UefiDebugLibConOut.inf
    <PcdsFixedAtBuild>
      gMyPkgTokenSpaceGuid.PcdMyBufferSize|0x2000
  }

[Components.X64]
  MyPlatformPkg/Applications/MyApp/MyApp.inf
```

Per-module overrides use `<LibraryClasses>`, `<PcdsFixedAtBuild>`, `<BuildOptions>`, etc. inside curly braces.

### [PcdsFixedAtBuild] Section

```ini
[PcdsFixedAtBuild]
  gEfiMdePkgTokenSpaceGuid.PcdDebugPropertyMask|0x2F
  gEfiMdePkgTokenSpaceGuid.PcdDebugPrintErrorLevel|0x80400040
  gEfiMdePkgTokenSpaceGuid.PcdFixedDebugPrintErrorLevel|0x80400040
```

### [PcdsDynamicDefault] Section

```ini
[PcdsDynamicDefault]
  gEfiMdeModulePkgTokenSpaceGuid.PcdConOutRow|25
  gEfiMdeModulePkgTokenSpaceGuid.PcdConOutColumn|80
```

### [BuildOptions] Section

Platform-wide compiler flags.

```ini
[BuildOptions]
  GCC:*_*_*_CC_FLAGS = -Werror -Wno-address
  GCC:RELEASE_*_*_CC_FLAGS = -DMDEPKG_NDEBUG
  MSFT:*_*_*_CC_FLAGS = /W4 /WX
```

---

## A.5 FDF File Format (Flash Description)

The FDF describes how the firmware image is laid out in flash.

### [FD] Section (Flash Device)

```ini
[FD.MyPlatform]
  BaseAddress   = 0xFF800000   # Flash base address
  Size          = 0x00800000   # 8 MB
  ErasePolarity = 1
  BlockSize     = 0x00010000   # 64 KB block
  NumBlocks     = 0x80         # 128 blocks

  # Region layout within the flash device
  0x00000000|0x00040000       # Offset | Size
  gMyPkgTokenSpaceGuid.PcdFlashNvStorageVariableBase|gMyPkgTokenSpaceGuid.PcdFlashNvStorageVariableSize
  DATA = {
    # NV_VARIABLE_STORE header
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
  }

  0x00040000|0x00010000
  gMyPkgTokenSpaceGuid.PcdFlashNvStorageFtwWorkingBase|gMyPkgTokenSpaceGuid.PcdFlashNvStorageFtwWorkingSize

  0x00050000|0x00010000
  gMyPkgTokenSpaceGuid.PcdFlashNvStorageFtwSpareBase|gMyPkgTokenSpaceGuid.PcdFlashNvStorageFtwSpareSize

  0x00100000|0x00700000
  FV = FVMAIN                 # Firmware volume at this region
```

### [FV] Section (Firmware Volume)

```ini
[FV.FVMAIN]
  FvAlignment        = 16
  ERASE_POLARITY     = 1
  MEMORY_MAPPED      = TRUE
  STICKY_WRITE       = TRUE
  LOCK_CAP           = TRUE
  LOCK_STATUS        = TRUE
  WRITE_DISABLED_CAP = TRUE
  WRITE_ENABLED_CAP  = TRUE
  WRITE_STATUS       = TRUE
  WRITE_LOCK_CAP     = TRUE
  WRITE_LOCK_STATUS  = TRUE
  READ_DISABLED_CAP  = TRUE
  READ_ENABLED_CAP   = TRUE
  READ_STATUS        = TRUE
  READ_LOCK_CAP      = TRUE
  READ_LOCK_STATUS   = TRUE

  #
  # DXE core
  #
  INF MdeModulePkg/Core/Dxe/DxeMain.inf

  #
  # DXE drivers
  #
  INF MdeModulePkg/Universal/PCD/Dxe/Pcd.inf
  INF MdeModulePkg/Universal/Console/ConSplitterDxe/ConSplitterDxe.inf
  INF MdeModulePkg/Universal/Console/GraphicsConsoleDxe/GraphicsConsoleDxe.inf
  INF MyPlatformPkg/Drivers/MyDxeDriver/MyDxeDriver.inf

  #
  # Applications (optional, for shell access)
  #
  INF ShellPkg/Application/Shell/Shell.inf

  #
  # Raw files
  #
  FILE RAW = AABBCCDD-1122-3344-5566-778899AABBCC {
    SECTION RAW = MyPlatformPkg/Binaries/logo.bmp
  }

  #
  # FREEFORM files (e.g., for HII resources)
  #
  FILE FREEFORM = 11223344-5566-7788-99AA-BBCCDDEEFF00 {
    SECTION UI = "MyStrings"
    SECTION RAW = MyPlatformPkg/Strings/strings.bin
  }
```

### File Types in FV

| Keyword | Description |
|---------|-------------|
| `INF` | Build module from INF and include in FV |
| `FILE RAW` | Include a raw binary blob |
| `FILE FREEFORM` | Free-form file with typed sections |
| `FILE DRIVER` | Pre-built driver binary |
| `FILE APPLICATION` | Pre-built application binary |
| `FILE FV_IMAGE` | Nested firmware volume |

### Section Types

| Section | Description |
|---------|-------------|
| `SECTION PE32` | PE32+ executable code |
| `SECTION RAW` | Raw binary data |
| `SECTION UI` | User interface name string |
| `SECTION DXE_DEPEX` | DXE dependency expression |
| `SECTION PEI_DEPEX` | PEI dependency expression |
| `SECTION COMPRESS` | Compressed section container |
| `SECTION GUIDED` | Guided encapsulation (e.g., signed) |

### [Rule] Section

Defines how module types are packaged into files.

```ini
[Rule.Common.DXE_DRIVER]
  FILE DRIVER = $(NAMED_GUID) {
    DXE_DEPEX    DXE_DEPEX    Optional $(INF_OUTPUT)/$(MODULE_NAME).depex
    PE32         PE32         $(INF_OUTPUT)/$(MODULE_NAME).efi
    UI           STRING="$(MODULE_NAME)" Optional
    VERSION      STRING="$(INF_VERSION)" Optional BUILD_NUM=$(BUILD_NUMBER)
  }

[Rule.Common.UEFI_APPLICATION]
  FILE APPLICATION = $(NAMED_GUID) {
    PE32         PE32         $(INF_OUTPUT)/$(MODULE_NAME).efi
    UI           STRING="$(MODULE_NAME)" Optional
  }
```

---

## A.6 Build Command Reference

### Traditional EDK2 Build

```bash
# Set up environment (Linux)
source edksetup.sh

# Build command
build -p MyPlatformPkg/MyPlatformPkg.dsc \
      -a X64 \
      -t GCC5 \
      -b DEBUG \
      -n 8        # Parallel jobs
```

| Flag | Description |
|------|-------------|
| `-p` | Platform DSC file |
| `-a` | Target architecture (IA32, X64, AARCH64, ARM, RISCV64) |
| `-t` | Tool chain tag (GCC5, VS2019, VS2022, CLANGPDB, CLANGDWARF) |
| `-b` | Build target (DEBUG, RELEASE, NOOPT) |
| `-n` | Number of parallel build threads |
| `-m` | Build a single module INF instead of entire platform |
| `-D` | Define macro (e.g., `-D MY_FEATURE=TRUE`) |
| `-y` | Build report file |
| `-Y` | Report types (PCD, LIBRARY, FLASH, DEPEX, BUILD_FLAGS, HASH) |

### Stuart Build (Project Mu)

Stuart wraps the EDK2 build with additional features:

```bash
# One-time setup: clone dependencies
stuart_setup -c Platforms/MyPlatform/PlatformBuild.py

# Update/sync dependencies
stuart_update -c Platforms/MyPlatform/PlatformBuild.py

# Build
stuart_build -c Platforms/MyPlatform/PlatformBuild.py \
  TOOL_CHAIN_TAG=GCC5 \
  TARGET=DEBUG

# CI build (runs build + tests)
stuart_ci_build -c .pytool/CISettings.py -a X64
```

Stuart advantages over raw `build`:
- Automatic dependency management via `ext_dep` YAML files
- Reproducible builds with pinned dependency versions
- Integrated CI/CD with test plugins
- Simplified command-line interface

---

## A.7 Build Output Structure

```
Build/
  MyPlatform/
    DEBUG_GCC5/
      FV/
        FVMAIN.Fv             # Firmware volume
        MYPLATFORM.fd         # Flash device image
      X64/
        MyDriver/
          MyDriver/
            OUTPUT/
              MyDriver.efi    # Built PE32+ binary
              MyDriver.map    # Linker map file
              MyDriver.depex  # Dependency expression
        MdePkg/
          Library/
            BaseLib/
              BaseLib/
                OUTPUT/
                  BaseLib.lib  # Library archive
```

---

## A.8 Build Reports

Generate a detailed build report with:

```bash
build -p MyPlatform.dsc -a X64 -t GCC5 -b DEBUG \
  -y BuildReport.txt \
  -Y PCD -Y LIBRARY -Y FLASH -Y DEPEX -Y BUILD_FLAGS
```

The report includes:
- PCD values and their sources (DSC, DEC, command-line)
- Library class resolution chains
- Flash layout with file offsets and sizes
- Dependency expressions for each module
- Compiler flags per module

This is invaluable for debugging build configuration issues.

---

## A.9 Common Build Errors

| Error | Cause | Fix |
|-------|-------|-----|
| `No library class found for X` | Missing library mapping in DSC | Add `[LibraryClasses]` entry |
| `GUID collision` | Two modules share same FILE_GUID | Generate unique GUID |
| `FV overflow` | Modules exceed firmware volume size | Increase FV size or remove modules |
| `Undefined symbol` | Missing library dependency | Add library to INF `[LibraryClasses]` |
| `Multiple definitions` | Two libraries provide same symbol | Check DSC library resolution order |
| `PCD not found` | Package DEC not listed in INF | Add package to INF `[Packages]` |

---

## Summary

The EDK2 build system revolves around four file types: INF (module), DEC (package), DSC (platform), and FDF (flash layout). Understanding these files and their relationships is essential for working with UEFI firmware. Project Mu's stuart system builds on this foundation with better dependency management and CI integration.
