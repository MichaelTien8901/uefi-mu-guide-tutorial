---
layout: default
title: "Appendix E: Glossary"
nav_order: 5
parent: "Appendices"
permalink: /appendices/glossary/
---

# Appendix E: Glossary

This appendix provides definitions for all acronyms, technical terms, error codes, and boot phase terminology used throughout this guide.

---

## E.1 Acronyms (A-Z)

| Acronym | Full Form | Description |
|---------|-----------|-------------|
| ACPI | Advanced Configuration and Power Interface | OS-firmware interface for hardware discovery, power management, and configuration |
| AML | ACPI Machine Language | Bytecode format for ACPI DSDT/SSDT tables |
| ASL | ACPI Source Language | Human-readable source for ACPI tables, compiled to AML |
| BDS | Boot Device Selection | Boot phase where boot targets are identified and launched |
| BIOS | Basic Input/Output System | Legacy firmware interface, predecessor to UEFI |
| BMC | Baseboard Management Controller | Out-of-band hardware management processor |
| BSP | Bootstrap Processor | The first processor to execute firmware code at power-on |
| CAR | Cache-As-RAM | Technique using CPU cache as temporary memory before DRAM init |
| CFR | Configuration File Reader | Project Mu configuration knob definition format |
| CMOS | Complementary Metal-Oxide Semiconductor | Battery-backed non-volatile memory for legacy BIOS settings |
| CRB | Customer Reference Board | Reference hardware platform from a silicon vendor |
| CSM | Compatibility Support Module | Legacy BIOS compatibility layer in UEFI firmware |
| DEC | Package Declaration | EDK2 file format declaring package exports |
| DFCI | Device Firmware Configuration Interface | Project Mu cloud-managed firmware configuration |
| DRAM | Dynamic Random-Access Memory | Main system memory |
| DSC | Platform Description | EDK2 file format describing a complete platform build |
| DSDT | Differentiated System Description Table | Primary ACPI table describing platform hardware |
| DXE | Driver Execution Environment | Boot phase with full memory, protocol-based driver model |
| EBC | EFI Byte Code | Platform-independent bytecode for UEFI drivers |
| EFI | Extensible Firmware Interface | Original name for what became UEFI |
| ESRT | EFI System Resource Table | Table listing firmware components for capsule update |
| FAT | File Allocation Table | Filesystem required on EFI System Partition |
| FDF | Flash Description File | EDK2 file format describing firmware image layout |
| FIT | Firmware Interface Table | Intel-specific table for ACM, microcode, and startup |
| FMP | Firmware Management Protocol | UEFI protocol for firmware component updates |
| FPD | Flash Platform Description | Legacy EDK file format (replaced by FDF) |
| FSP | Firmware Support Package | Intel binary for silicon initialization |
| FTP | Firmware Trusted Platform | Platform security architecture |
| FV | Firmware Volume | Logical container for firmware files within flash |
| FVB | Firmware Volume Block | Protocol for reading/writing firmware volume storage |
| GCD | Global Coherency Domain | Memory and I/O space management in DXE |
| GOP | Graphics Output Protocol | UEFI protocol for framebuffer graphics |
| GPT | GUID Partition Table | UEFI-standard disk partitioning scheme |
| GUID | Globally Unique Identifier | 128-bit identifier used extensively in UEFI |
| HAL | Hardware Abstraction Layer | Software layer isolating OS from hardware specifics |
| HII | Human Interface Infrastructure | UEFI framework for forms, strings, fonts, and images |
| HOB | Hand-Off Block | Data structure passed from PEI to DXE |
| HTTP | Hypertext Transfer Protocol | UEFI network protocol for web-based boot and update |
| IASL | Intel ACPI Source Language Compiler | Tool to compile ASL to AML |
| IFR | Internal Forms Representation | Binary encoding of HII forms |
| INF | Module Information | EDK2 file format describing a single module |
| IPMI | Intelligent Platform Management Interface | BMC communication standard |
| KTI | Intel Ultra Path Interconnect | Intel CPU interconnect (formerly QPI/UPI) |
| MAT | Memory Attributes Table | UEFI table describing memory region attributes |
| MBR | Master Boot Record | Legacy disk partitioning scheme |
| MM | Management Mode | Generic term for SMM (x86) or equivalent on other architectures |
| MMIO | Memory-Mapped I/O | Device registers accessible through memory address space |
| MNP | Managed Network Protocol | UEFI data-link layer network protocol |
| MOR | Memory Overwrite Request | TCG-defined variable to request memory clearing on reset |
| MTRR | Memory Type Range Register | x86 registers controlling memory caching behavior |
| NVRAM | Non-Volatile Random-Access Memory | Persistent storage for UEFI variables |
| OVMF | Open Virtual Machine Firmware | UEFI firmware for QEMU/KVM virtual machines |
| PCD | Platform Configuration Database | EDK2 mechanism for build-time and runtime configuration |
| PCH | Platform Controller Hub | Intel chipset component |
| PCI | Peripheral Component Interconnect | Bus standard for connecting hardware devices |
| PCIe | PCI Express | Serial point-to-point version of PCI |
| PE | Portable Executable | Windows executable format used for UEFI binaries |
| PEI | Pre-EFI Initialization | Early boot phase for memory and silicon init |
| PEIM | PEI Module | Executable module that runs during PEI phase |
| PI | Platform Initialization | UEFI Forum specification for firmware internals |
| PPI | PEI-to-PEI Interface | Service interface mechanism in PEI (analogous to DXE protocols) |
| PXE | Preboot Execution Environment | Network boot standard |
| QEMU | Quick EMUlator | Open-source machine emulator and virtualizer |
| RSDP | Root System Description Pointer | ACPI entry point structure |
| RT | Runtime | UEFI services available after ExitBootServices |
| S3 | Sleep State 3 (Suspend to RAM) | ACPI sleep state preserving memory contents |
| SB | Service Binding | UEFI pattern for creating child protocol instances |
| SEC | Security Phase | First UEFI boot phase, runs from flash/ROM |
| SIO | Super I/O | Legacy peripheral controller (serial, parallel, PS/2) |
| SMBus | System Management Bus | Two-wire communication bus for hardware monitoring |
| SMBIOS | System Management BIOS | Standard for system information tables |
| SMI | System Management Interrupt | Interrupt that enters SMM |
| SMM | System Management Mode | Privileged x86 CPU mode for firmware runtime services |
| SMRAM | System Management RAM | Memory region accessible only in SMM |
| SNP | Simple Network Protocol | UEFI protocol for basic network frame TX/RX |
| SPI | Serial Peripheral Interface | Bus for flash chip communication |
| SSDT | Secondary System Description Table | Supplementary ACPI table |
| TCG | Trusted Computing Group | Organization defining TPM and measured boot standards |
| TLS | Transport Layer Security | Encryption protocol for network communications |
| TPL | Task Priority Level | UEFI preemption priority mechanism |
| TPM | Trusted Platform Module | Security chip for cryptographic operations and measurement |
| TSC | Time Stamp Counter | x86 CPU cycle counter register |
| TSeg | Top Segment | Memory region reserved for SMM |
| UEFI | Unified Extensible Firmware Interface | Industry standard firmware interface specification |
| UNDI | Universal Network Driver Interface | Low-level NIC driver interface |
| USF | Universal Scalable Firmware | Initiative to standardize interfaces between firmware components |
| VLAN | Virtual LAN | Network segmentation supported by UEFI network stack |
| VMM | Virtual Machine Monitor | Hypervisor; firmware may need to interact with VMM services |
| VFR | Visual Forms Representation | Source language for HII forms |
| VPD | Vital Product Data | Read-only manufacturing data region |
| XHCI | eXtensible Host Controller Interface | USB 3.x host controller standard |

---

## E.2 EFI_STATUS Error Codes

### Success and Information Codes

| Code | Name | Value (X64) | Description |
|------|------|-------------|-------------|
| 0 | `EFI_SUCCESS` | 0x0 | Operation completed successfully |
| | `EFI_WARN_UNKNOWN_GLYPH` | 0x1 | String contained unknown glyph |
| | `EFI_WARN_DELETE_FAILURE` | 0x2 | File handle deleted but deletion was incomplete |
| | `EFI_WARN_WRITE_FAILURE` | 0x3 | Data written but some was lost |
| | `EFI_WARN_BUFFER_TOO_SMALL` | 0x4 | Buffer too small for result |
| | `EFI_WARN_STALE_DATA` | 0x5 | Data may be stale |
| | `EFI_WARN_FILE_SYSTEM` | 0x6 | Filesystem issue detected but operation completed |
| | `EFI_WARN_RESET_REQUIRED` | 0x7 | System reset recommended |

### Error Codes (high bit set)

| Code | Name | Value (X64) | Description |
|------|------|-------------|-------------|
| 1 | `EFI_LOAD_ERROR` | 0x8000000000000001 | Image load failed |
| 2 | `EFI_INVALID_PARAMETER` | 0x8000000000000002 | Invalid parameter passed |
| 3 | `EFI_UNSUPPORTED` | 0x8000000000000003 | Operation not supported |
| 4 | `EFI_BAD_BUFFER_SIZE` | 0x8000000000000004 | Buffer size incorrect |
| 5 | `EFI_BUFFER_TOO_SMALL` | 0x8000000000000005 | Buffer too small; required size returned |
| 6 | `EFI_NOT_READY` | 0x8000000000000006 | No data pending |
| 7 | `EFI_DEVICE_ERROR` | 0x8000000000000007 | Physical device error |
| 8 | `EFI_WRITE_PROTECTED` | 0x8000000000000008 | Target is write-protected |
| 9 | `EFI_OUT_OF_RESOURCES` | 0x8000000000000009 | Insufficient resources |
| 10 | `EFI_VOLUME_CORRUPTED` | 0x800000000000000A | Filesystem/volume corrupted |
| 11 | `EFI_VOLUME_FULL` | 0x800000000000000B | No space on volume |
| 12 | `EFI_NO_MEDIA` | 0x800000000000000C | No media in device |
| 13 | `EFI_MEDIA_CHANGED` | 0x800000000000000D | Media changed since last access |
| 14 | `EFI_NOT_FOUND` | 0x800000000000000E | Item not found |
| 15 | `EFI_ACCESS_DENIED` | 0x800000000000000F | Access denied |
| 16 | `EFI_NO_RESPONSE` | 0x8000000000000010 | Server/device not responding |
| 17 | `EFI_NO_MAPPING` | 0x8000000000000011 | No mapping for device |
| 18 | `EFI_TIMEOUT` | 0x8000000000000012 | Operation timed out |
| 19 | `EFI_NOT_STARTED` | 0x8000000000000013 | Protocol not started |
| 20 | `EFI_ALREADY_STARTED` | 0x8000000000000014 | Protocol already started |
| 21 | `EFI_ABORTED` | 0x8000000000000015 | Operation aborted |
| 22 | `EFI_ICMP_ERROR` | 0x8000000000000016 | ICMP error received |
| 23 | `EFI_TFTP_ERROR` | 0x8000000000000017 | TFTP error received |
| 24 | `EFI_PROTOCOL_ERROR` | 0x8000000000000018 | Protocol error |
| 25 | `EFI_INCOMPATIBLE_VERSION` | 0x8000000000000019 | Version incompatibility |
| 26 | `EFI_SECURITY_VIOLATION` | 0x800000000000001A | Security policy violation |
| 27 | `EFI_CRC_ERROR` | 0x800000000000001B | CRC check failed |
| 28 | `EFI_END_OF_MEDIA` | 0x800000000000001C | End of media reached |
| 31 | `EFI_END_OF_FILE` | 0x800000000000001F | End of file reached |
| 32 | `EFI_INVALID_LANGUAGE` | 0x8000000000000020 | Language not supported |
| 33 | `EFI_COMPROMISED_DATA` | 0x8000000000000021 | Data integrity compromised |
| 35 | `EFI_HTTP_ERROR` | 0x8000000000000023 | HTTP error |

The `%r` format specifier in `DEBUG` and `Print` automatically converts `EFI_STATUS` codes to human-readable strings.

---

## E.3 Boot Phase Terms

| Phase | Full Name | Description |
|-------|-----------|-------------|
| SEC | Security Phase | First code executed from reset vector; verifies firmware integrity, initializes temporary RAM (CAR), and transfers to PEI |
| PEI | Pre-EFI Initialization | Initializes minimal hardware (memory controller, chipset basics); runs PEIMs; produces HOBs for DXE |
| DXE | Driver Execution Environment | Full-featured driver model with protocol database; loads and dispatches DXE drivers; establishes boot and runtime services |
| BDS | Boot Device Selection | Enumerates boot devices, processes boot order, launches boot targets |
| TSL | Transient System Load | Period between BDS and OS calling ExitBootServices; OS loader runs here |
| RT | Runtime | Services available to the OS after ExitBootServices (variable access, time, reset) |
| AL | After Life | System state after OS shuts down (reset, power off, or S3/S4 resume) |
| SMM | System Management Mode | Isolated execution environment for runtime firmware services (x86); entered via SMI |
| MM | Management Mode | Architecture-neutral term for SMM-like isolated execution |

---

## E.4 Memory Type Terms

| Type | Description |
|------|-------------|
| `EfiReservedMemoryType` | Firmware-reserved, not usable by OS |
| `EfiLoaderCode` | UEFI application/loader code; usable after ExitBootServices |
| `EfiLoaderData` | UEFI application/loader data; usable after ExitBootServices |
| `EfiBootServicesCode` | Boot services driver code; usable after ExitBootServices |
| `EfiBootServicesData` | Boot services driver data; usable after ExitBootServices |
| `EfiRuntimeServicesCode` | Runtime driver code; must be preserved |
| `EfiRuntimeServicesData` | Runtime driver data; must be preserved |
| `EfiConventionalMemory` | Free, usable memory |
| `EfiUnusableMemory` | Memory with errors; not usable |
| `EfiACPIReclaimMemory` | ACPI tables; reclaimable after OS parses them |
| `EfiACPIMemoryNVS` | ACPI NVS; must be preserved |
| `EfiMemoryMappedIO` | Device MMIO regions |
| `EfiMemoryMappedIOPortSpace` | Device MMIO port space |
| `EfiPalCode` | Itanium PAL code (historical) |
| `EfiPersistentMemory` | Persistent (NVDIMM) memory |

---

## E.5 Project Mu Terms

| Term | Description |
|------|-------------|
| **stuart** | Python-based build orchestration tool for Project Mu (setup, update, build, CI) |
| **ext_dep** | External dependency descriptor (YAML file) for pulling packages via NuGet or Git |
| **mu_basecore** | Core Mu repository containing patched MdePkg, MdeModulePkg, and UefiCpuPkg |
| **mu_plus** | Extended packages providing Mu-specific features |
| **mu_tiano_plus** | Mu-patched versions of additional EDK2 packages (NetworkPkg, FatPkg, etc.) |
| **Policy Service** | Mu framework for managing configuration data through typed policy blobs |
| **DFCI** | Device Firmware Configuration Interface -- cloud-managed firmware settings |
| **MM Supervisor** | Mu feature providing privilege separation within Management Mode |
| **Front Page** | Mu's replacement for the traditional BIOS setup menu |
| **Configuration App** | Mu application for editing firmware settings via HII or configuration files |
| **CFR** | Configuration File Reader -- declarative format for defining firmware knobs |
| **Shared Crypto** | Mu approach to sharing a single crypto binary across all firmware components |
| **FMP** | Firmware Management Protocol -- UEFI standard mechanism for firmware updates |
| **ESRT** | EFI System Resource Table -- lists updatable firmware components |
| **Capsule Update** | UEFI-standard firmware update mechanism delivered as capsule files |
| **mu_devops** | Repository containing CI/CD templates and shared pipeline components |
| **PyTool** | Python tooling packages (`edk2-pytool-extensions`, `edk2-pytool-library`) |
| **PACKAGES_PATH** | Environment variable listing directories to search for EDK2 packages |
| **WORKSPACE** | Root directory for the build system; all paths are relative to this |

---

## E.6 Protocol Terms

| Term | Description |
|------|-------------|
| **Protocol** | Named interface (identified by GUID) installed on a handle; provides a function table |
| **Handle** | Opaque pointer representing a firmware object; protocols are attached to handles |
| **Handle Database** | Global registry of all handles and their installed protocols |
| **Service Binding** | Pattern where a protocol creates/destroys child instances (used by networking, USB) |
| **Driver Binding** | Protocol implementing Start/Stop/Supported for UEFI driver model |
| **Component Name** | Protocol providing human-readable driver and controller names |
| **Device Path** | Protocol describing the hardware path to a device (type/subtype node chain) |
| **Dependency Expression (DEPEX)** | Boolean expression controlling driver dispatch order based on protocol availability |

---

## E.7 Security Terms

| Term | Description |
|------|-------------|
| **Secure Boot** | UEFI feature verifying cryptographic signatures of boot loaders and drivers |
| **PK** | Platform Key -- top-level Secure Boot key owned by platform manufacturer |
| **KEK** | Key Exchange Key -- authorized to update db/dbx |
| **db** | Signature Database -- list of trusted signing certificates/hashes |
| **dbx** | Forbidden Signature Database -- revoked certificates/hashes |
| **dbt** | Timestamp Signature Database -- trusted timestamping certificates |
| **Measured Boot** | Recording firmware/boot component measurements (hashes) into TPM PCRs |
| **PCR** | Platform Configuration Register -- TPM register holding cumulative measurements |
| **Event Log** | Record of what was measured into each PCR and when |
| **TCG Log** | Same as Event Log, formatted per TCG specification |
| **Root of Trust** | Initial trusted component from which a chain of trust extends |
| **ACM** | Authenticated Code Module -- Intel hardware-verified firmware component |
| **SPI Flash Protection** | Hardware write-protection of flash regions containing firmware |
| **Capsule Update** | UEFI-defined mechanism for delivering firmware updates as capsule files |
| **Rollback Protection** | Preventing installation of older, potentially vulnerable firmware versions |
| **SMRAM Lock** | Mechanism to prevent DXE-phase code from accessing SMM memory |
| **Variable Lock** | Protocol to make UEFI variables read-only after lock |
| **Authenticated Variable** | UEFI variable that requires signature verification for writes |

---

## E.8 Build System Terms

| Term | Description |
|------|-------------|
| **WORKSPACE** | Root directory of the EDK2/Mu build environment; all relative paths resolve from here |
| **PACKAGES_PATH** | Semicolon/colon-separated list of directories searched for package references |
| **TARGET** | Build target: DEBUG (full debug output), RELEASE (optimized, minimal debug), NOOPT (no optimization, full debug) |
| **TOOL_CHAIN_TAG** | Identifier for the compiler toolchain: GCC5, VS2019, VS2022, CLANGPDB, CLANGDWARF |
| **AutoGen** | Build system step that generates C source and header files from INF/DEC/DSC metadata |
| **BaseTools** | Collection of Python and C utilities that implement the EDK2 build system |
| **GenFv** | Tool that generates firmware volume images from compiled modules |
| **GenFw** | Tool that converts ELF binaries to PE32+ format for UEFI |
| **GenFds** | Tool that generates the final flash device image from FDF |
| **EDKII_DSC_FEATURE_BUILD_OPTIONS** | DSC define for conditional compilation of platform features |
| **build -m** | Build a single module rather than the entire platform |
| **Build Report** | Detailed output showing PCD values, library resolution, and flash layout |
| **Conf directory** | Contains build_rule.txt, tools_def.txt, and target.txt configuration files |

---

## E.9 Hardware and Bus Terms

| Term | Description |
|------|-------------|
| **BAR** | Base Address Register -- PCI register specifying MMIO or I/O port address range |
| **BDF** | Bus/Device/Function -- PCI device address notation (e.g., 00:1F.0) |
| **DMA** | Direct Memory Access -- hardware mechanism for devices to access memory without CPU |
| **IOMMU** | I/O Memory Management Unit -- hardware that isolates device DMA to assigned regions |
| **VT-d** | Intel Virtualization Technology for Directed I/O -- Intel's IOMMU implementation |
| **MSI** | Message Signaled Interrupt -- PCI interrupt mechanism using memory writes |
| **MSI-X** | Extended MSI -- enhanced version supporting more interrupt vectors |
| **NVMe** | Non-Volatile Memory Express -- protocol for accessing solid-state storage over PCIe |
| **AHCI** | Advanced Host Controller Interface -- SATA controller interface standard |
| **XHCI** | eXtensible Host Controller Interface -- USB 3.x controller standard |
| **EHCI** | Enhanced Host Controller Interface -- USB 2.0 controller standard |
| **SPI** | Serial Peripheral Interface -- bus used for firmware flash chip access |
| **I2C** | Inter-Integrated Circuit -- two-wire serial bus for low-speed peripherals |
| **SMBus** | System Management Bus -- variant of I2C for system management |
| **GPIO** | General Purpose Input/Output -- configurable digital pins |
| **HPET** | High Precision Event Timer -- platform timer for OS scheduling |
| **LAPIC** | Local Advanced Programmable Interrupt Controller -- per-CPU interrupt controller |
| **IOAPIC** | I/O Advanced Programmable Interrupt Controller -- system interrupt router |

---

## E.10 UEFI Table and Data Structure Terms

| Term | Description |
|------|-------------|
| **System Table (ST)** | Top-level UEFI data structure; provides access to Boot Services, Runtime Services, and configuration tables |
| **Boot Services Table (BS)** | Function table for services available before ExitBootServices (memory, protocols, events, images) |
| **Runtime Services Table (RT)** | Function table for services available after ExitBootServices (variables, time, reset, virtual address map) |
| **Configuration Table** | Array of GUID-tagged pointers in the System Table (ACPI, SMBIOS, etc.) |
| **HOB List** | Hand-Off Block list -- data passed from PEI to DXE describing memory, hardware, and resources |
| **GCD Map** | Global Coherency Domain map -- DXE-phase memory and I/O space allocation database |
| **EFI_MEMORY_DESCRIPTOR** | Structure describing a single memory map entry (type, physical address, pages, attributes) |
| **EFI_DEVICE_PATH_PROTOCOL** | Linked list of typed nodes describing the hardware path to a device |
| **EFI_LOAD_OPTION** | Variable-length structure stored in Boot#### variables (attributes, device path, description) |
| **EFI_CAPSULE_HEADER** | Header for firmware update capsules delivered through UpdateCapsule() |
| **EFI_FV_FILETYPE** | Enumeration of file types within a firmware volume (DRIVER, APPLICATION, RAW, FREEFORM, etc.) |
| **EFI_SECTION_TYPE** | Enumeration of section types within FV files (PE32, DEPEX, UI, RAW, COMPRESSED, GUIDED) |

---

## E.11 Network Protocol Terms

| Term | Description |
|------|-------------|
| **SNP** | Simple Network Protocol -- low-level NIC abstraction for frame send/receive |
| **MNP** | Managed Network Protocol -- data-link layer providing multicast and VLAN support |
| **ARP** | Address Resolution Protocol -- resolves IP addresses to MAC addresses |
| **DHCP4/DHCP6** | Dynamic Host Configuration Protocol -- automatic IP address assignment |
| **DNS4/DNS6** | Domain Name System Protocol -- hostname to IP address resolution |
| **HTTP** | Hypertext Transfer Protocol -- application-layer protocol for web communication |
| **TCP4/TCP6** | Transmission Control Protocol -- reliable, ordered byte stream delivery |
| **UDP4/UDP6** | User Datagram Protocol -- connectionless datagram delivery |
| **IP4/IP6** | Internet Protocol -- network-layer addressing and routing |
| **PXE Base Code** | Preboot Execution Environment protocol -- network boot support |
| **iSCSI** | Internet Small Computer Systems Interface -- network-attached storage protocol |
| **TLS** | Transport Layer Security protocol -- encrypted network communication |
| **MTFTP4** | Multicast Trivial File Transfer Protocol -- multicast file distribution |
| **WiFi** | IEEE 802.11 wireless LAN -- supported via EFI_WIRELESS_MAC_CONNECTION protocols |

---

## E.12 ACPI Terms

| Term | Description |
|------|-------------|
| **RSDP** | Root System Description Pointer -- initial structure for locating ACPI tables |
| **XSDT** | Extended System Description Table -- 64-bit table of pointers to other ACPI tables |
| **RSDT** | Root System Description Table -- 32-bit version of XSDT (legacy) |
| **DSDT** | Differentiated System Description Table -- primary table describing platform hardware in AML |
| **SSDT** | Secondary System Description Table -- supplementary AML tables |
| **FADT** | Fixed ACPI Description Table -- describes fixed hardware features |
| **MADT** | Multiple APIC Description Table -- describes interrupt controllers and processors |
| **MCFG** | Memory-Mapped Configuration Space -- describes PCI Express ECAM base address |
| **HPET** | High Precision Event Timer Table -- describes HPET hardware |
| **DMAR** | DMA Remapping Table -- describes IOMMU (VT-d) configuration |
| **BGRT** | Boot Graphics Resource Table -- describes boot splash screen image |
| **SRAT** | System Resource Affinity Table -- describes NUMA topology |
| **SLIT** | System Locality Information Table -- describes NUMA distances |
| **Sx States** | ACPI sleep states: S0 (working), S1-S3 (sleep), S4 (hibernate), S5 (off) |
| **Cx States** | ACPI CPU idle states: C0 (active), C1-Cn (progressively deeper idle) |
| **Px States** | ACPI CPU performance states: P0 (highest), P1-Pn (progressively lower frequency) |

---

## E.13 Common UEFI Shell Commands

| Command | Description |
|---------|-------------|
| `map` | Display or refresh filesystem and device mappings |
| `ls` / `dir` | List directory contents |
| `cd` | Change current directory |
| `cp` / `copy` | Copy files |
| `mv` / `move` | Move or rename files |
| `rm` / `del` | Delete files |
| `edit` | Simple text editor |
| `type` | Display file contents |
| `hexedit` | Hex editor for files |
| `drivers` | List installed UEFI drivers |
| `devices` | List device handles |
| `dh` | Display handle database |
| `devtree` | Display device tree |
| `connect` | Connect drivers to devices |
| `disconnect` | Disconnect drivers from devices |
| `reconnect` | Reconnect drivers to devices |
| `load` | Load a UEFI driver image |
| `unload` | Unload a UEFI driver |
| `memmap` | Display current memory map |
| `dmem` | Display memory at an address |
| `mm` | Read/write memory, I/O, or PCI config space |
| `pci` | Display PCI device information |
| `smbiosview` | Display SMBIOS table contents |
| `acpiview` | Display ACPI table contents |
| `dmpstore` | Dump or modify UEFI variables |
| `bcfg` | Manage boot and driver options |
| `ifconfig` | Configure network interfaces |
| `ping` | Send ICMP echo requests |
| `reset` | Reset the system |
| `exit` | Exit the Shell or a script |
| `set` | Set or display environment variables |
| `echo` | Print text to console |
| `for` | Looping construct in Shell scripts |
| `if` / `endif` | Conditional construct in Shell scripts |
| `goto` | Branch to a label in Shell scripts |
| `stall` | Pause for a specified number of microseconds |

---

## Summary

This glossary covers the essential terminology for UEFI, PI, Project Mu, EDK2, ACPI, hardware buses, networking, security, and related standards. Use it as a quick reference when encountering unfamiliar acronyms or terms throughout this guide and in the broader firmware development ecosystem.
