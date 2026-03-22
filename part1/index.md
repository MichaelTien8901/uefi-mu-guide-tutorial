---
layout: default
title: "Part 1: Getting Started"
nav_order: 2
has_children: true
permalink: /part1/
---

# Part 1: Getting Started
{: .fs-9 }

Your first steps into UEFI firmware development with Project Mu.
{: .fs-6 .fw-300 }

---

## Overview

Part 1 takes you from zero to a working UEFI development environment with a running Hello World application. By the end of these three chapters, you will understand what UEFI is, have a fully configured build environment, and have compiled and executed your first UEFI application inside a virtual machine.

## Chapters

### [Chapter 1: Introduction to UEFI and Project Mu]({% link part1/01-introduction.md %})
Learn what UEFI is, why it replaced legacy BIOS, how the UEFI boot phases work, and where Project Mu fits into the picture. This chapter provides the conceptual foundation for everything that follows.

### [Chapter 2: Environment Setup]({% link part1/02-environment-setup.md %})
Install and configure all the tools you need: Python, Git, stuart, compilers, QEMU, and OVMF. Covers both Windows and Linux workflows, including a Docker-based alternative.

### [Chapter 3: Hello World]({% link part1/03-hello-world.md %})
Write, build, and run your first UEFI application. Understand the structure of a UEFI module (`.c` and `.inf` files), the `UefiMain` entry point, and how to use `Print()` for console output.

## What You Will Need

- A development machine running Windows 10/11 or Ubuntu 20.04+
- Basic C programming knowledge
- Familiarity with the command line and Git
- About 20 GB of free disk space (for the full Project Mu source tree and build output)

## Learning Path

After completing Part 1, continue to [Part 2: Project Mu Structure & Tooling]({% link part2/index.md %}) for a deep dive into the multi-repo architecture and the stuart build system.
