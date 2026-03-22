---
layout: default
title: Home
nav_order: 1
permalink: /
mermaid: true
---

# UEFI Project Mu Development Guide
{: .fs-9 }

A comprehensive tutorial and reference for UEFI firmware development using Microsoft's Project Mu framework.
{: .fs-6 .fw-300 }

---

## Welcome

This guide provides a complete learning path for UEFI firmware development through the lens of [Project Mu](https://microsoft.github.io/mu/), Microsoft's open-source UEFI firmware framework. Whether you're new to firmware development or an experienced EDK2 developer looking to adopt Project Mu, this guide covers everything from initial environment setup to advanced firmware topics.

## Who Is This Guide For?

- **Firmware engineers** starting with UEFI development
- **EDK2 developers** migrating to the Project Mu ecosystem
- **Platform engineers** building or maintaining UEFI-based firmware
- **Students and researchers** exploring firmware and low-level systems programming

## Prerequisites

- Basic C programming knowledge
- Familiarity with command-line tools (Git, Python/pip)
- A development machine (Windows 10/11, Ubuntu 20.04+, or macOS)

## Guide Structure

### [Part 1: Getting Started]({% link part1/index.md %})
Introduction to UEFI and Project Mu, environment setup, and your first Hello World application.

### [Part 2: Project Mu Structure & Tooling]({% link part2/index.md %})
Deep dive into Project Mu's multi-repo architecture, the stuart build system, dependency management, and CI/CD pipelines.

### [Part 3: UEFI Core Concepts]({% link part3/index.md %})
Essential UEFI concepts: driver model, protocols and handles, memory services, and boot/runtime services.

### [Part 4: Essential UEFI Services]({% link part4/index.md %})
Hands-on with key UEFI services: console I/O, graphics output, file system, block I/O, networking, and variables.

### [Part 5: Advanced Topics]({% link part5/index.md %})
Professional-level topics: boot phases (PEI/DXE), SMM, security, ACPI, capsule updates, DFCI, Rust in firmware, and platform testing.

### [Part 6: Practical Projects]({% link part6/index.md %})
Complete hands-on projects: custom shell commands, graphical boot menu, network application, and custom boot loader.

### [Appendices]({% link appendices/index.md %})
Reference material: EDK2 build system, migration guide, debugging techniques, specifications, glossary, and alternative firmware.

## How to Use This Guide

- **Sequential learning**: Follow the parts in order for a structured learning experience from beginner to advanced
- **Reference**: Jump directly to any chapter for specific topics — each chapter is self-contained with cross-references where needed
- **Hands-on**: Every chapter includes practical code examples that you can build and run with stuart and QEMU

## UEFI Boot Flow Overview

```mermaid
graph LR
    SEC[SEC<br/>Security] --> PEI[PEI<br/>Pre-EFI Init]
    PEI --> DXE[DXE<br/>Driver Execution]
    DXE --> BDS[BDS<br/>Boot Device Select]
    BDS --> RT[Runtime<br/>OS Running]

    style SEC fill:#e74c3c,stroke:#c0392b,color:#fff
    style PEI fill:#e67e22,stroke:#d35400,color:#fff
    style DXE fill:#2ecc71,stroke:#27ae60,color:#fff
    style BDS fill:#3498db,stroke:#2980b9,color:#fff
    style RT fill:#9b59b6,stroke:#8e44ad,color:#fff
```

## Get Started

Ready to begin? Head to [Chapter 1: Introduction to UEFI and Project Mu]({% link part1/01-introduction.md %}) to start your journey.
