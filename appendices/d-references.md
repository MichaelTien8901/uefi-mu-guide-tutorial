---
layout: default
title: "Appendix D: References"
nav_order: 4
parent: "Appendices"
permalink: /appendices/references/
---

# Appendix D: References

This appendix collects the key specifications, repositories, documentation sites, and community resources relevant to UEFI and Project Mu firmware development.

---

## D.1 UEFI and PI Specifications

| Specification | Version | URL |
|--------------|---------|-----|
| UEFI Specification | 2.10 | [https://uefi.org/specifications](https://uefi.org/specifications) |
| PI (Platform Initialization) Specification | 1.8 | [https://uefi.org/specifications](https://uefi.org/specifications) |
| UEFI Shell Specification | 2.2 | [https://uefi.org/specifications](https://uefi.org/specifications) |
| ACPI Specification | 6.5 | [https://uefi.org/specifications](https://uefi.org/specifications) |
| UEFI Platform Initialization Distribution Packaging Spec | 1.1 | [https://uefi.org/specifications](https://uefi.org/specifications) |

All UEFI Forum specifications are available as free PDF downloads from the UEFI Forum website after registration.

---

## D.2 Project Mu Repositories

| Repository | Description | URL |
|-----------|-------------|-----|
| mu_basecore | Core packages (MdePkg, MdeModulePkg, etc.) | [https://github.com/microsoft/mu_basecore](https://github.com/microsoft/mu_basecore) |
| mu_plus | Extended Mu packages | [https://github.com/microsoft/mu_plus](https://github.com/microsoft/mu_plus) |
| mu_tiano_plus | Patched EDK2 packages | [https://github.com/microsoft/mu_tiano_plus](https://github.com/microsoft/mu_tiano_plus) |
| mu_silicon_intel_tiano | Intel silicon support | [https://github.com/microsoft/mu_silicon_intel_tiano](https://github.com/microsoft/mu_silicon_intel_tiano) |
| mu_feature_config | Configuration/policy framework | [https://github.com/microsoft/mu_feature_config](https://github.com/microsoft/mu_feature_config) |
| mu_feature_mm_supv | MM Supervisor feature | [https://github.com/microsoft/mu_feature_mm_supv](https://github.com/microsoft/mu_feature_mm_supv) |
| mu_feature_dfci | Device Firmware Configuration Interface | [https://github.com/microsoft/mu_feature_dfci](https://github.com/microsoft/mu_feature_dfci) |
| mu_devops | CI/CD tooling and templates | [https://github.com/microsoft/mu_devops](https://github.com/microsoft/mu_devops) |
| mu_crypto_release | Crypto binaries for Mu builds | [https://github.com/microsoft/mu_crypto_release](https://github.com/microsoft/mu_crypto_release) |

### Project Mu Documentation

| Resource | URL |
|----------|-----|
| Project Mu main site | [https://microsoft.github.io/mu/](https://microsoft.github.io/mu/) |
| Getting started guide | [https://microsoft.github.io/mu/WhatAndWhy/overview/](https://microsoft.github.io/mu/WhatAndWhy/overview/) |
| Build system documentation | [https://microsoft.github.io/mu/CodeDevelopment/build/](https://microsoft.github.io/mu/CodeDevelopment/build/) |
| Feature documentation | [https://microsoft.github.io/mu/dyn/mu_feature_config/](https://microsoft.github.io/mu/dyn/mu_feature_config/) |

---

## D.3 EDK2 Repositories and Documentation

| Resource | URL |
|----------|-----|
| EDK2 source code | [https://github.com/tianocore/edk2](https://github.com/tianocore/edk2) |
| EDK2 platforms | [https://github.com/tianocore/edk2-platforms](https://github.com/tianocore/edk2-platforms) |
| EDK2 non-OSI binaries | [https://github.com/tianocore/edk2-non-osi](https://github.com/tianocore/edk2-non-osi) |
| TianoCore wiki | [https://github.com/tianocore/tianocore.github.io/wiki](https://github.com/tianocore/tianocore.github.io/wiki) |
| EDK2 build specification | [https://tianocore-docs.github.io/edk2-BuildSpecification/](https://tianocore-docs.github.io/edk2-BuildSpecification/) |
| EDK2 DSC specification | [https://tianocore-docs.github.io/edk2-DscSpecification/](https://tianocore-docs.github.io/edk2-DscSpecification/) |
| EDK2 INF specification | [https://tianocore-docs.github.io/edk2-InfSpecification/](https://tianocore-docs.github.io/edk2-InfSpecification/) |
| EDK2 FDF specification | [https://tianocore-docs.github.io/edk2-FdfSpecification/](https://tianocore-docs.github.io/edk2-FdfSpecification/) |
| EDK2 DEC specification | [https://tianocore-docs.github.io/edk2-DecSpecification/](https://tianocore-docs.github.io/edk2-DecSpecification/) |
| OVMF documentation | [https://github.com/tianocore/tianocore.github.io/wiki/OVMF](https://github.com/tianocore/tianocore.github.io/wiki/OVMF) |

---

## D.4 Stuart / Python Tooling

| Package | Description | URL |
|---------|-------------|-----|
| edk2-pytool-extensions | Stuart build system | [https://github.com/tianocore/edk2-pytool-extensions](https://github.com/tianocore/edk2-pytool-extensions) |
| edk2-pytool-library | Python library for EDK2 operations | [https://github.com/tianocore/edk2-pytool-library](https://github.com/tianocore/edk2-pytool-library) |
| PyPI: edk2-pytool-extensions | pip package | [https://pypi.org/project/edk2-pytool-extensions/](https://pypi.org/project/edk2-pytool-extensions/) |
| PyPI: edk2-pytool-library | pip package | [https://pypi.org/project/edk2-pytool-library/](https://pypi.org/project/edk2-pytool-library/) |

---

## D.5 Industry Standards

| Standard | Organization | Relevance |
|----------|-------------|-----------|
| TCG PC Client Platform TPM Profile (PTP) | Trusted Computing Group | TPM hardware interface |
| TCG EFI Protocol Specification | Trusted Computing Group | TCG/TPM2 UEFI protocols |
| SMBIOS Specification (3.7) | DMTF | System management BIOS data |
| IPMI Specification (2.0) | DMTF | Baseboard management controller |
| PCI Express Base Specification (6.0) | PCI-SIG | PCI/PCIe bus interface |
| USB Specification (4.0) | USB-IF | USB host controller interface |
| NVMe Specification (2.0) | NVM Express | NVMe storage protocol |
| SD/SDIO Specification | SD Association | SD card interface |
| JEDEC DDR5 (JESD79-5) | JEDEC | Memory interface |

### Where to Obtain Standards

| Organization | URL |
|-------------|-----|
| UEFI Forum | [https://uefi.org](https://uefi.org) |
| Trusted Computing Group | [https://trustedcomputinggroup.org](https://trustedcomputinggroup.org) |
| DMTF (SMBIOS) | [https://www.dmtf.org/standards/smbios](https://www.dmtf.org/standards/smbios) |
| PCI-SIG | [https://pcisig.com](https://pcisig.com) |
| NVM Express | [https://nvmexpress.org](https://nvmexpress.org) |

---

## D.6 QEMU and Virtual Platform Resources

| Resource | URL |
|----------|-----|
| QEMU documentation | [https://www.qemu.org/documentation/](https://www.qemu.org/documentation/) |
| QEMU source code | [https://github.com/qemu/qemu](https://github.com/qemu/qemu) |
| OVMF build instructions | [https://github.com/tianocore/tianocore.github.io/wiki/How-to-build-OVMF](https://github.com/tianocore/tianocore.github.io/wiki/How-to-build-OVMF) |
| AAVMF (ARM UEFI for QEMU) | Part of edk2 `ArmVirtPkg` |

---

## D.7 Community Resources

### Mailing Lists

| List | Description | URL |
|------|-------------|-----|
| edk2-devel | EDK2 development discussion | [https://edk2.groups.io/g/devel](https://edk2.groups.io/g/devel) |
| edk2-discuss | General EDK2 questions | [https://edk2.groups.io/g/discuss](https://edk2.groups.io/g/discuss) |

### Issue Trackers

| Project | URL |
|---------|-----|
| EDK2 Bugzilla | [https://bugzilla.tianocore.org](https://bugzilla.tianocore.org) |
| Project Mu (per-repo) | GitHub Issues on each mu_* repository |

### Conferences and Talks

| Event | Description |
|-------|-------------|
| UEFI Plugfest | Semi-annual interoperability testing event |
| OSFC (Open Source Firmware Conference) | Annual conference on open-source firmware |
| Linux Plumbers Conference (firmware track) | Firmware topics in the Linux ecosystem |

### Books

| Title | Author(s) | Notes |
|-------|-----------|-------|
| *Beyond BIOS* (3rd Edition) | Zimmer, Rothman, Marisetty | Comprehensive UEFI/PI reference |
| *Harnessing the UEFI Shell* | Rothman, Zimmer, Lewis | Shell programming guide |
| *Embedded Firmware Solutions* | Zimmer, Rothman | Intel firmware development |

### Online Learning

| Resource | URL |
|----------|-----|
| TianoCore training materials | [https://github.com/tianocore-training](https://github.com/tianocore-training) |
| UEFI learning path (Linaro) | [https://www.linaro.org](https://www.linaro.org) |
| OSDev Wiki UEFI section | [https://wiki.osdev.org/UEFI](https://wiki.osdev.org/UEFI) |

---

## D.8 Tool Downloads

| Tool | URL |
|------|-----|
| GCC cross-compiler (for UEFI) | System package manager or [https://gcc.gnu.org](https://gcc.gnu.org) |
| NASM assembler | [https://nasm.us](https://nasm.us) |
| IASL (ACPI compiler) | [https://www.intel.com/content/www/us/en/developer/topic-technology/open/acpica/download.html](https://www.intel.com/content/www/us/en/developer/topic-technology/open/acpica/download.html) |
| Python 3.9+ | [https://python.org](https://python.org) |
| Visual Studio Build Tools | [https://visualstudio.microsoft.com/downloads/](https://visualstudio.microsoft.com/downloads/) |
| Git | [https://git-scm.com](https://git-scm.com) |
| LLVM/Clang (CLANGPDB/CLANGDWARF) | [https://llvm.org](https://llvm.org) |
| QEMU emulator | [https://www.qemu.org/download/](https://www.qemu.org/download/) |
| UEFITool (firmware image editor) | [https://github.com/LongSoft/UEFITool](https://github.com/LongSoft/UEFITool) |
| CHIPSEC (security analysis) | [https://github.com/chipsec/chipsec](https://github.com/chipsec/chipsec) |
| fwupd (Linux firmware updater) | [https://fwupd.org](https://fwupd.org) |

---

## D.9 Alternative Firmware Projects

| Project | URL |
|---------|-----|
| coreboot | [https://coreboot.org](https://coreboot.org) |
| LinuxBoot | [https://linuxboot.org](https://linuxboot.org) |
| AMD openSIL | [https://github.com/openSIL](https://github.com/openSIL) |
| oreboot | [https://github.com/oreboot/oreboot](https://github.com/oreboot/oreboot) |
| Intel Slim Bootloader | [https://slimbootloader.github.io](https://slimbootloader.github.io) |
| U-Boot (ARM/embedded) | [https://u-boot.readthedocs.io](https://u-boot.readthedocs.io) |
| Arm Trusted Firmware (TF-A) | [https://trustedfirmware.org](https://trustedfirmware.org) |

See [Appendix F](/appendices/alternative-firmware/) for detailed coverage of these projects.

---

## D.10 Firmware Security Resources

| Resource | URL |
|----------|-----|
| NIST SP 800-147: BIOS Protection Guidelines | [https://csrc.nist.gov/publications/detail/sp/800-147/final](https://csrc.nist.gov/publications/detail/sp/800-147/final) |
| NIST SP 800-147B: Server BIOS Protection | [https://csrc.nist.gov/publications/detail/sp/800-147b/final](https://csrc.nist.gov/publications/detail/sp/800-147b/final) |
| NIST SP 800-155: BIOS Integrity Measurement | [https://csrc.nist.gov/publications/detail/sp/800-155/draft](https://csrc.nist.gov/publications/detail/sp/800-155/draft) |
| Microsoft Secured-core PC requirements | [https://learn.microsoft.com/en-us/windows-hardware/design/device-experiences/oem-highly-secure](https://learn.microsoft.com/en-us/windows-hardware/design/device-experiences/oem-highly-secure) |
| CHIPSEC documentation | [https://chipsec.github.io](https://chipsec.github.io) |
| TCG reference implementation | [https://github.com/microsoft/ms-tpm-20-ref](https://github.com/microsoft/ms-tpm-20-ref) |

---

## Summary

This reference collection covers the specifications, source repositories, tooling, standards, security guidelines, and community channels you will need throughout your UEFI and Project Mu development work. Bookmark the UEFI Specification, the Project Mu documentation site, and the EDK2 file format specifications as your primary references.
