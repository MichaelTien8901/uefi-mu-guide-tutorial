# UEFI Project Mu Development Guide - Code Examples

This directory contains buildable UEFI application and driver examples using
EDK2/Project Mu conventions. Each example demonstrates a specific UEFI concept
and can be compiled and run in QEMU or on real hardware.

## Build Prerequisites

- **Python 3.10+** with pip
- **stuart** (the Project Mu build system):
  ```
  pip install mu_build mu_environment mu_stuart
  ```
- **Compiler toolchain**: GCC 5+ (Linux), Visual Studio 2019+ (Windows), or
  CLANG/LLVM
- **QEMU** (optional, for testing): `apt install qemu-system-x86` or equivalent
- **git** for fetching EDK2/Mu dependencies

## Build Instructions

1. **Set up your Project Mu workspace** (if not already done):
   ```bash
   mkdir mu_workspace && cd mu_workspace
   git clone https://github.com/microsoft/mu_tiano_plus.git
   stuart_setup -c mu_tiano_plus/Platforms/QemuQ35Pkg/PlatformBuild.py
   stuart_update -c mu_tiano_plus/Platforms/QemuQ35Pkg/PlatformBuild.py
   ```

2. **Copy examples into the workspace**:
   ```bash
   cp -r UefiMuGuidePkg/ mu_workspace/
   ```

3. **Build the package**:
   ```bash
   stuart_build -c UefiMuGuidePkg/UefiMuGuidePkg.dsc \
       -a X64 -t RELEASE TOOL_CHAIN_TAG=GCC5
   ```

4. **Build a single module** (optional):
   ```bash
   stuart_build -c UefiMuGuidePkg/UefiMuGuidePkg.dsc \
       -a X64 -t RELEASE -m UefiMuGuidePkg/HelloWorld/HelloWorld.inf
   ```

## Running in QEMU

1. Create a UEFI boot disk image:
   ```bash
   dd if=/dev/zero of=disk.img bs=1M count=64
   mkfs.fat -F 32 disk.img
   mcopy -i disk.img Build/UefiMuGuidePkg/RELEASE_GCC5/X64/HelloWorld.efi ::/
   ```

2. Launch QEMU with OVMF firmware:
   ```bash
   qemu-system-x86_64 \
       -drive if=pflash,format=raw,readonly=on,file=OVMF_CODE.fd \
       -drive if=pflash,format=raw,file=OVMF_VARS.fd \
       -drive format=raw,file=disk.img \
       -net none -serial stdio
   ```

3. At the UEFI Shell prompt, run:
   ```
   Shell> fs0:
   FS0:\> HelloWorld.efi
   ```

## Directory Listing

| Directory           | Type             | Description                                    |
|---------------------|------------------|------------------------------------------------|
| `HelloWorld/`       | UEFI_APPLICATION | Minimal "Hello World" application              |
| `DriverExample/`    | UEFI_DRIVER      | DXE driver with Driver Binding Protocol        |
| `ProtocolExample/`  | UEFI_APPLICATION | Custom protocol definition and usage           |
| `MemoryExample/`    | UEFI_APPLICATION | Memory allocation and memory map               |
| `ServicesExample/`  | UEFI_APPLICATION | Timer events and boot/runtime services         |
| `ConsoleExample/`   | UEFI_APPLICATION | Console I/O, colors, and key input             |
| `GopExample/`       | UEFI_APPLICATION | Graphics Output Protocol and BLT drawing       |
| `FileSystemExample/`| UEFI_APPLICATION | File system read/write/directory listing       |
| `BlockIoExample/`   | UEFI_APPLICATION | Block device enumeration and media info        |
| `NetworkExample/`   | UEFI_APPLICATION | Network interface enumeration and MAC display  |
| `VariableExample/`  | UEFI_APPLICATION | UEFI variable read/write/delete                |
| `NetworkApp/`       | UEFI_APPLICATION | TCP4 network connection example                |
| `ShellCommand/`     | UEFI_APPLICATION | Shell application with argument parsing        |
| `BootMenu/`         | UEFI_APPLICATION | Boot option menu display and selection         |
| `BootLoader/`       | UEFI_APPLICATION | File loading and ExitBootServices pattern      |

## Common Header

All examples include `UefiMuGuide.h` from the package's `Include/` directory,
which provides standard UEFI headers and common macros.

## License

These examples are provided for educational purposes as part of the UEFI
Project Mu Development Guide.
