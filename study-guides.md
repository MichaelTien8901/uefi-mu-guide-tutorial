---
layout: default
title: Study Guides by Role
nav_order: 2
permalink: /study-guides/
---

# Study Guides by Role
{: .fs-9 }

Not sure where to start? Pick the role closest to yours and follow the recommended learning path.
{: .fs-6 .fw-300 }

---

Every chapter in this guide is self-contained, so you can jump to any topic that interests you. But if you want a focused path, these role-based guides highlight the chapters most relevant to your work.

Chapters are categorized as:
- **Essential** — core material for this role, read these first
- **Recommended** — valuable follow-ups that deepen your skills
- **Optional** — useful reference material when needed

---

## UEFI Application Developer

You write UEFI applications, shell commands, or pre-boot tools. You need to understand UEFI services, protocols, and how to interact with hardware through standardized interfaces.

**Prerequisites:** Basic C programming, comfort with command-line tools.

### Essential Chapters

| Chapter | Topic | Why |
|---------|-------|-----|
| [Ch 1]({% link part1/01-introduction.md %}) | Introduction to UEFI and Project Mu | Understand what UEFI is and how it works |
| [Ch 2]({% link part1/02-environment-setup.md %}) | Environment Setup | Get your build environment running |
| [Ch 3]({% link part1/03-hello-world.md %}) | Hello World | Write and run your first UEFI application |
| [Ch 9]({% link part3/09-driver-model.md %}) | Driver Model | Understand how UEFI loads and manages code |
| [Ch 10]({% link part3/10-protocols-handles.md %}) | Protocols and Handles | The core pattern for all UEFI programming |
| [Ch 11]({% link part3/11-memory-services.md %}) | Memory Services | Allocate and manage memory correctly |
| [Ch 12]({% link part3/12-boot-runtime-services.md %}) | Boot and Runtime Services | The full service API available to your code |
| [Ch 13]({% link part4/13-console-io.md %}) | Console I/O | Text input/output for interactive apps |
| [Ch 14]({% link part4/14-graphics-output.md %}) | Graphics Output (GOP) | Framebuffer access for graphical apps |
| [Ch 15]({% link part4/15-file-system.md %}) | File System Access | Read/write files on FAT volumes |
| [Ch 16]({% link part4/16-block-io.md %}) | Block I/O | Raw disk access and partition detection |
| [Ch 17]({% link part4/17-network.md %}) | Network Stack | TCP/IP, HTTP, DNS for network apps |
| [Ch 18]({% link part4/18-variables.md %}) | UEFI Variables | Persistent storage across boots |

### Recommended Chapters

| Chapter | Topic | Why |
|---------|-------|-----|
| [Ch 28]({% link part6/28-shell-command.md %}) | Custom Shell Command | Build a real shell utility end-to-end |
| [Ch 29]({% link part6/29-boot-menu.md %}) | Graphical Boot Menu | Combine GOP + console + variables |
| [Ch 30]({% link part6/30-network-app.md %}) | Network Application | Build a real network client |
| [Ch 31]({% link part6/31-boot-loader.md %}) | Custom Boot Loader | Understand ExitBootServices and OS handoff |

### Optional Chapters

| Chapter | Topic |
|---------|-------|
| Ch 4-8 | Project Mu structure and tooling (if using Mu for builds) |
| [App A]({% link appendices/a-edk2-build-system.md %}) | EDK2 build system reference (INF/DEC/DSC/FDF) |
| [App C]({% link appendices/c-debugging.md %}) | Debugging techniques |

---

## Platform / Firmware Engineer

You bring up, maintain, or customize platform firmware. You need to understand boot phases, silicon initialization, platform description files, CI/CD, and testing.

**Prerequisites:** C programming, familiarity with hardware initialization concepts, comfort with build systems.

### Essential Chapters

| Chapter | Topic | Why |
|---------|-------|-----|
| [Ch 1]({% link part1/01-introduction.md %}) | Introduction to UEFI and Project Mu | UEFI architecture and Project Mu's role |
| [Ch 2]({% link part1/02-environment-setup.md %}) | Environment Setup | Set up the full Mu toolchain |
| [Ch 3]({% link part1/03-hello-world.md %}) | Hello World | Verify your build environment works |
| [Ch 4]({% link part2/04-repo-architecture.md %}) | Repository Architecture | How Mu splits firmware across repos |
| [Ch 5]({% link part2/05-stuart-build.md %}) | Stuart Build System | The build system you will use daily |
| [Ch 6]({% link part2/06-dependencies.md %}) | Dependency Management | NuGet, pip, submodule dependencies |
| [Ch 7]({% link part2/07-platform-dsc-fdf.md %}) | Platform DSC/FDF | Platform description and flash layout |
| [Ch 8]({% link part2/08-ci-cd.md %}) | CI/CD Pipeline | Automated build and test validation |
| [Ch 19]({% link part5/19-pei-phase.md %}) | PEI Phase | Early init: CAR, memory training, HOBs |
| [Ch 20]({% link part5/20-dxe-phase.md %}) | DXE Phase | Driver dispatch, architectural protocols |
| [Ch 23]({% link part5/23-acpi.md %}) | ACPI Integration | Platform tables for the OS |
| [Ch 27]({% link part5/27-platform-testing.md %}) | Platform Testing | CI test infrastructure and validation |

### Recommended Chapters

| Chapter | Topic | Why |
|---------|-------|-----|
| [Ch 9]({% link part3/09-driver-model.md %}) | Driver Model | Writing platform drivers |
| [Ch 10]({% link part3/10-protocols-handles.md %}) | Protocols and Handles | Protocol installation and consumption |
| [Ch 11]({% link part3/11-memory-services.md %}) | Memory Services | Memory map and allocation patterns |
| [Ch 12]({% link part3/12-boot-runtime-services.md %}) | Boot and Runtime Services | Service lifecycle across phases |
| [Ch 21]({% link part5/21-smm.md %}) | System Management Mode | SMM handlers and SMRAM protection |
| [Ch 22]({% link part5/22-security.md %}) | Security and Secure Boot | Chain of trust, key management |
| [Ch 24]({% link part5/24-capsule-updates.md %}) | Capsule Updates | Firmware update workflows |

### Optional Chapters

| Chapter | Topic |
|---------|-------|
| Ch 13-18 | UEFI services (reference as needed for driver work) |
| [Ch 25]({% link part5/25-dfci.md %}) | DFCI (if managing device fleets) |
| [Ch 26]({% link part5/26-rust-firmware.md %}) | Rust in Firmware (if adopting Rust modules) |
| [App B]({% link appendices/b-migration-guide.md %}) | EDK2 to Mu migration guide |

---

## Security Engineer

You focus on firmware security: Secure Boot, Measured Boot, SMM hardening, DFCI, and firmware update integrity. You need to understand the trust chain from power-on through OS handoff.

**Prerequisites:** C programming, basic understanding of cryptography (PKI, hashing, signing), familiarity with UEFI concepts.

### Essential Chapters

| Chapter | Topic | Why |
|---------|-------|-----|
| [Ch 1]({% link part1/01-introduction.md %}) | Introduction to UEFI and Project Mu | Boot phases and attack surface overview |
| [Ch 2]({% link part1/02-environment-setup.md %}) | Environment Setup | Build environment for security testing |
| [Ch 3]({% link part1/03-hello-world.md %}) | Hello World | Baseline for building test modules |
| [Ch 21]({% link part5/21-smm.md %}) | System Management Mode | SMM isolation, SMRAM protection, attack surface |
| [Ch 22]({% link part5/22-security.md %}) | Security and Secure Boot | PK/KEK/db/dbx, Measured Boot, TPM |
| [Ch 24]({% link part5/24-capsule-updates.md %}) | Capsule Updates | Signed update verification and delivery |
| [Ch 25]({% link part5/25-dfci.md %}) | DFCI | Remote configuration with certificate trust |

### Recommended Chapters

| Chapter | Topic | Why |
|---------|-------|-----|
| [Ch 9]({% link part3/09-driver-model.md %}) | Driver Model | How drivers are authenticated and loaded |
| [Ch 10]({% link part3/10-protocols-handles.md %}) | Protocols and Handles | Protocol security implications |
| [Ch 11]({% link part3/11-memory-services.md %}) | Memory Services | Memory protection and isolation |
| [Ch 12]({% link part3/12-boot-runtime-services.md %}) | Boot and Runtime Services | ExitBootServices security boundary |
| [Ch 18]({% link part4/18-variables.md %}) | UEFI Variables | Authenticated variables, Secure Boot vars |
| [Ch 19]({% link part5/19-pei-phase.md %}) | PEI Phase | Early boot trust establishment |
| [Ch 20]({% link part5/20-dxe-phase.md %}) | DXE Phase | Driver dispatch and security policy |
| [Ch 26]({% link part5/26-rust-firmware.md %}) | Rust in Firmware | Memory-safe firmware for security-critical code |

### Optional Chapters

| Chapter | Topic |
|---------|-------|
| Ch 4-8 | Mu structure and CI (if working on Mu platforms) |
| [Ch 27]({% link part5/27-platform-testing.md %}) | Platform testing (security test automation) |
| [App C]({% link appendices/c-debugging.md %}) | Debugging techniques |

---

## EDK2-to-Project Mu Migrator

You are an experienced EDK2 developer adopting Project Mu. You already know UEFI concepts — you need to understand what Mu does differently: multi-repo architecture, stuart, dependency management, CI/CD, and Mu-specific features.

**Prerequisites:** Working EDK2 experience, familiarity with INF/DEC/DSC/FDF files, existing platform firmware.

### Essential Chapters

| Chapter | Topic | Why |
|---------|-------|-----|
| [Ch 4]({% link part2/04-repo-architecture.md %}) | Repository Architecture | Mu's multi-repo model vs EDK2 monorepo |
| [Ch 5]({% link part2/05-stuart-build.md %}) | Stuart Build System | Replace your build scripts with stuart |
| [Ch 6]({% link part2/06-dependencies.md %}) | Dependency Management | NuGet, ext_dep, pip — new dependency model |
| [Ch 7]({% link part2/07-platform-dsc-fdf.md %}) | Platform DSC/FDF | Multi-repo DSC layering and includes |
| [Ch 8]({% link part2/08-ci-cd.md %}) | CI/CD Pipeline | Mu's CI plugins and GitHub Actions |
| [App B]({% link appendices/b-migration-guide.md %}) | EDK2 to Project Mu Migration | Step-by-step migration guide |

### Recommended Chapters

| Chapter | Topic | Why |
|---------|-------|-----|
| [Ch 1]({% link part1/01-introduction.md %}) | Introduction | Project Mu's philosophy and architecture |
| [Ch 27]({% link part5/27-platform-testing.md %}) | Platform Testing | Mu's test infrastructure |
| [Ch 25]({% link part5/25-dfci.md %}) | DFCI | Mu-specific device management feature |
| [Ch 26]({% link part5/26-rust-firmware.md %}) | Rust in Firmware | Mu's Rust integration |

### Optional Chapters

| Chapter | Topic |
|---------|-------|
| [Ch 24]({% link part5/24-capsule-updates.md %}) | Capsule updates (Mu's FmpDevicePkg approach) |
| [App A]({% link appendices/a-edk2-build-system.md %}) | EDK2 build system reference (for comparison) |

---

## Not Sure Which Role Fits?

If none of these roles match exactly, start with the **UEFI Application Developer** path — it covers the broadest set of fundamental concepts. You can always branch into platform engineering or security topics from there.

For a complete sequential learning experience, simply follow the guide from [Chapter 1]({% link part1/01-introduction.md %}) through [Chapter 31]({% link part6/31-boot-loader.md %}).
