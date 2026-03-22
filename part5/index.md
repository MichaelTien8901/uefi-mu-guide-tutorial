---
layout: default
title: "Part 5: Advanced Topics"
nav_order: 6
has_children: true
permalink: /part5/
---

# Part 5: Advanced Topics
{: .fs-9 }

Explore the internal architecture of UEFI firmware, from early silicon initialization through secure boot and platform configuration.
{: .fs-6 .fw-300 }

---

## Overview

Part 5 moves beyond application-level UEFI development and into the firmware internals that platform engineers work with daily. These chapters cover the boot phases that execute before any UEFI application or OS loader runs, the security infrastructure that establishes trust from power-on through OS handoff, and the platform description tables that tell the operating system how the hardware is wired together.

Understanding these topics is essential for anyone building or customizing a Project Mu platform firmware. The PEI and DXE phases determine how memory is discovered, how drivers are dispatched, and how the protocol database you used in earlier parts gets populated. System Management Mode provides a secure execution environment for runtime firmware services. Secure Boot and Measured Boot establish the chain of trust that modern platforms require. ACPI tables bridge the gap between firmware and the operating system's view of hardware.

Each chapter includes architectural diagrams, C code examples, and pointers to the relevant Project Mu packages and libraries.

## Chapters

### [Chapter 19: PEI Phase]({% link part5/19-pei-phase.md %})
Understand the Pre-EFI Initialization phase: how the PEI Foundation discovers and dispatches PEI Modules (PEIMs), how PEIM-to-PEIM Interfaces (PPIs) provide early services, how Cache-As-RAM enables execution before DRAM training, and how Hand-Off Blocks (HOBs) transfer state to the DXE phase.

### [Chapter 20: DXE Phase]({% link part5/20-dxe-phase.md %})
Explore the Driver Execution Environment: the DXE Foundation, the DXE Dispatcher and its dependency expression engine, the thirteen Architectural Protocols that define platform policy, driver binding for bus enumeration, events and timer services, and the transition to BDS (Boot Device Selection).

### [Chapter 21: System Management Mode]({% link part5/21-smm.md %})
Learn how SMM provides a hardware-isolated execution environment for firmware runtime services, how SMI handlers are registered and dispatched, the differences between Traditional SMM and Standalone MM, SMRAM protection, and security best practices for SMM code.

### [Chapter 22: Security and Secure Boot]({% link part5/22-security.md %})
Master the UEFI Secure Boot chain of trust, the key hierarchy (PK, KEK, db, dbx), binary signing workflows, Measured Boot with TPM integration, Project Mu's Device Firmware Configuration Interface (DFCI), and defenses against bootkits and firmware-level rootkits.

### [Chapter 23: ACPI Integration]({% link part5/23-acpi.md %})
Understand how firmware publishes ACPI tables to describe platform topology, power management, and device configuration. Learn ASL fundamentals, dynamic table generation using the ACPI Table Protocol, debugging techniques with acpidump and iasl, and Project Mu's ACPI management patterns.

### [Chapter 24: Capsule Updates]({% link part5/24-capsule-updates.md %})
Learn how UEFI capsule-based firmware updates work, from capsule generation and signing through delivery mechanisms (in-band and out-of-band), the UpdateCapsule runtime service, and Project Mu's FmpDevicePkg integration for production firmware update workflows.

### [Chapter 25: DFCI]({% link part5/25-dfci.md %})
Explore the Device Firmware Configuration Interface, Microsoft's open-source framework for remote, zero-touch firmware configuration. Understand DFCI's certificate-based trust model, permission system, and how it enables enterprise fleet management of firmware settings.

### [Chapter 26: Rust in Firmware]({% link part5/26-rust-firmware.md %})
Write UEFI firmware components in Rust using the r-efi crate. Set up the Rust toolchain for UEFI targets, build a `no_std` UEFI application, implement custom allocators, and understand how Project Mu integrates Rust modules alongside C code.

### [Chapter 27: Platform Testing]({% link part5/27-platform-testing.md %})
Build a comprehensive testing strategy for firmware: host-based unit tests, UEFI shell-based integration tests, QEMU-based automated testing, stuart's CI test infrastructure, and platform validation best practices.

## Prerequisites

Before starting Part 5, you should be comfortable with:

- Building and running UEFI applications and drivers (Parts 1-3)
- The UEFI protocol and handle database model (Part 3)
- Boot Services, Runtime Services, and memory management (Part 3)
- UEFI variable storage concepts (Chapter 18)
