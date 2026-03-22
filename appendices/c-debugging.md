---
layout: default
title: "Appendix C: Debugging Techniques"
nav_order: 3
parent: "Appendices"
permalink: /appendices/debugging/
---

# Appendix C: Debugging Techniques

This appendix covers the essential debugging tools and techniques for UEFI and Project Mu firmware development. From simple debug prints to full source-level debugging with GDB, these methods will help you diagnose issues across all boot phases.

---

## C.1 The DEBUG Macro

The `DEBUG` macro is the most fundamental debugging tool in UEFI. It is defined in `DebugLib.h` and controlled by PCDs.

### Basic Usage

```c
#include <Library/DebugLib.h>

DEBUG ((DEBUG_INFO, "MyDriver: entry point called\n"));
DEBUG ((DEBUG_WARN, "MyDriver: buffer size %d exceeds limit\n", Size));
DEBUG ((DEBUG_ERROR, "MyDriver: LocateProtocol failed - %r\n", Status));
```

### Error Levels

| Level | Value | Purpose |
|-------|-------|---------|
| `DEBUG_INIT` | 0x00000001 | Initialization messages |
| `DEBUG_WARN` | 0x00000002 | Warnings |
| `DEBUG_LOAD` | 0x00000004 | Module load/unload |
| `DEBUG_FS` | 0x00000008 | Filesystem operations |
| `DEBUG_POOL` | 0x00000010 | Memory pool allocation |
| `DEBUG_PAGE` | 0x00000020 | Page allocation |
| `DEBUG_INFO` | 0x00000040 | General information |
| `DEBUG_DISPATCH` | 0x00000080 | Driver dispatch |
| `DEBUG_VARIABLE` | 0x00000100 | Variable operations |
| `DEBUG_BM` | 0x00000400 | Boot manager |
| `DEBUG_BLKIO` | 0x00001000 | Block I/O operations |
| `DEBUG_NET` | 0x00004000 | Network stack |
| `DEBUG_UNDI` | 0x00010000 | UNDI driver |
| `DEBUG_LOADFILE` | 0x00020000 | Load file operations |
| `DEBUG_EVENT` | 0x00080000 | Event/timer |
| `DEBUG_GCD` | 0x00100000 | GCD operations |
| `DEBUG_CACHE` | 0x00200000 | Cache operations |
| `DEBUG_VERBOSE` | 0x00400000 | Verbose output |
| `DEBUG_ERROR` | 0x80000000 | Error messages (always shown) |

### PCD Configuration

Control what gets printed with these PCDs in your DSC:

```ini
[PcdsFixedAtBuild]
  # Which debug levels are enabled (bitmask)
  gEfiMdePkgTokenSpaceGuid.PcdDebugPrintErrorLevel|0x80400040
  #  0x80000000 = DEBUG_ERROR
  #  0x00400000 = DEBUG_VERBOSE
  #  0x00000040 = DEBUG_INFO

  # Debug property mask (features enabled)
  gEfiMdePkgTokenSpaceGuid.PcdDebugPropertyMask|0x2F
  #  Bit 0: DEBUG_PROPERTY_DEBUG_ASSERT_ENABLED
  #  Bit 1: DEBUG_PROPERTY_DEBUG_PRINT_ENABLED
  #  Bit 2: DEBUG_PROPERTY_DEBUG_CODE_ENABLED
  #  Bit 3: DEBUG_PROPERTY_CLEAR_MEMORY_ENABLED
  #  Bit 5: DEBUG_PROPERTY_ASSERT_DEADLOOP_ENABLED
```

### DebugLib Implementations

| Library INF | Output Target | Best For |
|------------|---------------|----------|
| `BaseDebugLibNull` | Nowhere (disabled) | Release builds |
| `BaseDebugLibSerialPort` | Serial port (COM1) | Hardware, QEMU |
| `UefiDebugLibConOut` | Console (screen) | Interactive debugging |
| `UefiDebugLibDebugPortProtocol` | Debug port protocol | Debugger integration |
| `PeiDxeDebugLibReportStatusCode` | Status code output | Production firmware |

---

## C.2 Serial Output Configuration

Serial output is the most reliable debug channel, working from SEC through Runtime.

### QEMU Serial Setup

```bash
# Output serial to terminal
qemu-system-x86_64 \
  -bios OVMF.fd \
  -serial stdio \
  -nographic

# Output serial to file
qemu-system-x86_64 \
  -bios OVMF.fd \
  -serial file:debug.log \
  -display gtk

# Output serial to TCP socket
qemu-system-x86_64 \
  -bios OVMF.fd \
  -serial tcp:localhost:1234,server,nowait
```

### DSC Configuration for Serial Debug

```ini
[LibraryClasses]
  DebugLib|MdePkg/Library/BaseDebugLibSerialPort/BaseDebugLibSerialPort.inf
  SerialPortLib|PcAtChipsetPkg/Library/SerialIoLib/SerialIoLib.inf

[PcdsFixedAtBuild]
  # Serial port base address (0x3F8 = COM1)
  gEfiMdeModulePkgTokenSpaceGuid.PcdSerialRegisterBase|0x3F8
  # Baud rate
  gEfiMdeModulePkgTokenSpaceGuid.PcdSerialBaudRate|115200
```

---

## C.3 ASSERT Macro

`ASSERT` halts execution when a condition is false (in DEBUG builds):

```c
#include <Library/DebugLib.h>

ASSERT (Buffer != NULL);
ASSERT (Size > 0 && Size <= MAX_BUFFER_SIZE);
ASSERT_EFI_ERROR (Status);  // Asserts if Status is an error

// Return value assertion
ASSERT_RETURN_ERROR (ReturnValue);  // For RETURN_STATUS
```

When an assert fires, the debug output shows:

```
ASSERT [MyDriver] /path/to/MyDriver.c(123): Buffer != NULL
```

If `DEBUG_PROPERTY_ASSERT_DEADLOOP_ENABLED` is set, the CPU enters a dead loop, which is ideal for attaching a debugger.

---

## C.4 GDB with QEMU

QEMU's built-in GDB stub enables source-level debugging of UEFI firmware.

### Step 1: Launch QEMU with GDB Server

```bash
qemu-system-x86_64 \
  -bios OVMF_CODE.fd \
  -serial stdio \
  -s \          # Enable GDB server on port 1234
  -S \          # Freeze CPU at startup (wait for GDB)
  -nographic
```

### Step 2: Connect GDB

```bash
gdb
(gdb) target remote localhost:1234
(gdb) continue
```

### Step 3: Load Debug Symbols

UEFI modules are loaded at runtime-determined addresses. You need to find the load address and load symbols accordingly:

```bash
# From the UEFI debug log, find the image base:
# Loading driver at 0x00007E8F000 EntryPoint=0x00007E90ABC MyDriver.efi

# In GDB:
(gdb) add-symbol-file Build/MyPlatform/DEBUG_GCC5/X64/MyDriver/MyDriver/DEBUG/MyDriver.debug 0x00007E8F000
```

### Automated Symbol Loading

The OVMF debug log prints module load addresses. A helper script can parse these:

```bash
#!/bin/bash
# load_symbols.sh - Parse OVMF debug log and generate GDB commands

LOG_FILE="debug.log"
BUILD_DIR="Build/MyPlatform/DEBUG_GCC5/X64"

grep "Loading driver" "$LOG_FILE" | while read -r line; do
  ADDR=$(echo "$line" | grep -oP '0x[0-9A-Fa-f]+' | head -1)
  MODULE=$(echo "$line" | grep -oP '\S+\.efi' | sed 's/.efi//')

  DEBUG_FILE=$(find "$BUILD_DIR" -name "${MODULE}.debug" 2>/dev/null | head -1)
  if [ -n "$DEBUG_FILE" ]; then
    echo "add-symbol-file $DEBUG_FILE $ADDR"
  fi
done
```

### Common GDB Commands for UEFI

```
(gdb) break MyDriverEntryPoint          # Set breakpoint by function name
(gdb) break *0x7E90ABC                  # Set breakpoint by address
(gdb) info registers                    # View CPU registers
(gdb) x/32xw 0x7E8F000                 # Examine memory (32 words)
(gdb) x/16xg $rsp                      # Examine stack (16 quad-words)
(gdb) print gST->FirmwareVendor        # Print UEFI variable (with symbols)
(gdb) set *(UINT32 *)0x7E91000 = 0x42  # Modify memory
(gdb) stepi                             # Step one instruction
(gdb) nexti                             # Step over call
(gdb) continue                          # Resume execution
(gdb) bt                                # Backtrace
```

---

## C.5 QEMU Monitor Commands

The QEMU monitor provides low-level system inspection. Access it with `Ctrl-A C` in `-nographic` mode, or via the monitor tab in GUI mode.

| Command | Description |
|---------|-------------|
| `info registers` | Dump all CPU registers |
| `info mem` | Show page table mappings |
| `info tlb` | Show TLB entries |
| `info mtree` | Show memory region tree |
| `info pci` | Show PCI device tree |
| `x/Nx addr` | Examine N words at address |
| `xp /Nx paddr` | Examine physical address |
| `gdbserver` | Start GDB server on the fly |
| `stop` | Pause guest CPU |
| `cont` | Resume guest CPU |
| `log unimp` | Log unimplemented feature accesses |
| `savevm name` | Save VM snapshot |
| `loadvm name` | Restore VM snapshot |

Example: inspecting the UEFI System Table:

```
(qemu) xp /4xg 0x7F9E018   # Examine System Table header
(qemu) info pci              # Check PCI enumeration
```

---

## C.6 Phase-Specific Debugging

### SEC Phase Debugging

SEC runs from flash with no memory. Debugging options are limited:

- **Port 80h POST codes**: Write to I/O port 0x80 for progress tracking
- **Serial output**: If serial is initialized in SEC
- **LED/GPIO toggles**: On physical hardware

```c
// Post code output
IoWrite8 (0x80, 0x01);  // SEC entry
IoWrite8 (0x80, 0x02);  // CAR initialized
IoWrite8 (0x80, 0x03);  // Entering PEI
```

### PEI Phase Debugging

PEI runs with limited memory (initially just Cache-as-RAM). Use:

```c
// PEI debug print (with PeiServicesLib)
DEBUG ((DEBUG_INFO, "PEI: memory discovered, %d MB\n",
        MemorySize / (1024 * 1024)));

// Report status code for progress
REPORT_STATUS_CODE (
  EFI_PROGRESS_CODE,
  (EFI_SOFTWARE_PEI_MODULE | EFI_SW_PEI_CORE_PC_HANDOFF_TO_NEXT)
  );
```

### DXE Phase Debugging

DXE has full memory and serial support. This is the easiest phase to debug:

```c
// Rich debug output
DEBUG ((DEBUG_INFO, "DXE Driver loaded at 0x%p\n", ImageHandle));
DEBUG ((DEBUG_INFO, "  Protocol count: %d\n", ProtocolCount));

// Use ASSERT for development
ASSERT_EFI_ERROR (Status);

// Conditional debug code
DEBUG_CODE_BEGIN ();
  DumpProtocolDatabase ();
DEBUG_CODE_END ();
```

### SMM Debugging

SMM debugging is the most challenging due to the isolated execution environment:

- SMM runs in its own address space (SMRAM)
- Standard serial output may not work from SMM
- Use `SmmDebugLib` for serial output from SMM
- QEMU can be configured to allow GDB debugging of SMM

```ini
# DSC: SMM-specific debug library
[LibraryClasses.common.DXE_SMM_DRIVER]
  DebugLib|MdePkg/Library/BaseDebugLibSerialPort/BaseDebugLibSerialPort.inf
```

---

## C.7 Visual Studio Debugging (Windows)

For developers using Visual Studio on Windows:

### Build with MSFT Toolchain

```bash
stuart_build -c PlatformBuild.py TOOL_CHAIN_TAG=VS2022
```

### Attach to QEMU

1. Start QEMU with `-s -S` flags.
2. In Visual Studio: **Debug > Attach to Process > Connection Type: Remote (no authentication)**.
3. Enter `localhost:1234` as the qualifier.
4. Load symbols from the build output directory.

### WinDbg with OVMF

For kernel-style debugging, WinDbg can connect to QEMU:

```bash
qemu-system-x86_64 \
  -bios OVMF.fd \
  -serial pipe:com_1 \
  -m 256
```

Then in WinDbg: `File > Kernel Debug > COM > Pipe > \\.\pipe\com_1`

---

## C.8 Shell-Based Debugging

The UEFI Shell provides several built-in debugging commands:

| Command | Description |
|---------|-------------|
| `drivers` | List all loaded drivers with handles |
| `dh` | Display handle database |
| `dh -p <protocol>` | Find handles with a specific protocol |
| `devtree` | Display device tree hierarchy |
| `memmap` | Display memory map |
| `dmpstore` | Dump UEFI variable store |
| `smbiosview` | Display SMBIOS tables |
| `acpiview` | Display ACPI tables |
| `pci` | List PCI devices |
| `mm` | Read/write memory or I/O ports |
| `dmem` | Display memory contents |

Examples:

```
# List all drivers
Shell> drivers

# Show handles with PCI I/O protocol
Shell> dh -p PciIo

# Dump memory at address
Shell> dmem 0x7F9E000 0x100

# Read PCI config space
Shell> pci 00 1F 00

# Dump all UEFI variables
Shell> dmpstore -all

# Write to I/O port
Shell> mm 0x3F8 0x41 -IO -w 1
```

---

## C.9 Common Debugging Patterns

### Pattern 1: Status Code Tracing

```c
// Track progress through a complex initialization
DEBUG ((DEBUG_INFO, "[MyDriver] Phase 1: Locate protocols\n"));
Status = LocateRequiredProtocols ();
DEBUG ((DEBUG_INFO, "[MyDriver] Phase 1: %r\n", Status));

DEBUG ((DEBUG_INFO, "[MyDriver] Phase 2: Initialize hardware\n"));
Status = InitializeHardware ();
DEBUG ((DEBUG_INFO, "[MyDriver] Phase 2: %r\n", Status));
```

### Pattern 2: Memory Dump Helper

```c
VOID
DumpHex (
  IN CONST VOID  *Data,
  IN UINTN       Length
  )
{
  CONST UINT8  *Bytes = (CONST UINT8 *)Data;
  UINTN        Index;

  for (Index = 0; Index < Length; Index++) {
    if (Index % 16 == 0) {
      DEBUG ((DEBUG_INFO, "\n  %04X: ", Index));
    }
    DEBUG ((DEBUG_INFO, "%02X ", Bytes[Index]));
  }
  DEBUG ((DEBUG_INFO, "\n"));
}
```

### Pattern 3: Protocol Availability Check

```c
VOID
DebugCheckProtocol (
  IN EFI_GUID  *ProtocolGuid,
  IN CHAR8     *Name
  )
{
  EFI_STATUS  Status;
  VOID        *Interface;

  Status = gBS->LocateProtocol (ProtocolGuid, NULL, &Interface);
  DEBUG ((DEBUG_INFO, "  %-30a: %r (0x%p)\n",
          Name, Status, Interface));
}

// Usage:
DebugCheckProtocol (&gEfiPciIoProtocolGuid, "PciIo");
DebugCheckProtocol (&gEfiGraphicsOutputProtocolGuid, "GOP");
```

### Pattern 4: Timing Measurement

```c
UINT64
GetTimestamp (
  VOID
  )
{
  return AsmReadTsc ();  // x86 timestamp counter
}

// Usage:
UINT64 Start = GetTimestamp ();
DoExpensiveOperation ();
UINT64 End = GetTimestamp ();
DEBUG ((DEBUG_INFO, "Operation took %ld cycles\n", End - Start));
```

### Pattern 5: Deadloop for Debugger Attach

```c
// Place at a point where you want to attach a debugger
volatile BOOLEAN Wait = TRUE;
DEBUG ((DEBUG_INFO, "Waiting for debugger at 0x%p...\n", &Wait));
while (Wait) {
  CpuPause ();
}
// In GDB: set *(BOOLEAN *)0xADDRESS = 0
```

---

## C.10 Build Report Analysis

Generate a build report to understand PCD resolution, library mapping, and more:

```bash
build -p MyPlatform.dsc -a X64 -t GCC5 -b DEBUG \
  -y report.txt \
  -Y PCD -Y LIBRARY -Y DEPEX -Y BUILD_FLAGS
```

The report shows:
- Which library INF was selected for each library class
- Final PCD values and where they were set (DSC, DEC, command-line)
- Dependency expressions for dispatch ordering
- Exact compiler flags applied to each module

This is often the fastest way to diagnose "wrong library linked" or "wrong PCD value" issues.

---

## Summary

UEFI debugging ranges from simple `DEBUG` prints to full source-level debugging with GDB. The key tools are: `DEBUG` macro with serial output for print-style debugging, GDB with QEMU for source-level debugging, QEMU monitor for system-level inspection, UEFI Shell commands for runtime state examination, and build reports for configuration analysis. Master these tools and you can diagnose issues at any boot phase.
