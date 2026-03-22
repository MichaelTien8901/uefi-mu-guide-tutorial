---
layout: default
title: "Part 3: UEFI Core Concepts"
nav_order: 5
has_children: true
permalink: /part3/
---

# Part 3: UEFI Core Concepts
{: .fs-9 }

Master the foundational architecture that every UEFI developer must understand.
{: .fs-6 .fw-300 }

---

## Overview

Part 3 moves beyond "Hello World" and into the heart of UEFI firmware engineering. These four chapters cover the design patterns, data structures, and service interfaces that underpin every UEFI module you will ever write. Whether you are building a device driver, a boot loader, or a platform initialization module, the concepts here are essential.

You will learn how the UEFI driver model separates policy from mechanism, how the protocol and handle database provides a dynamic object system in C, how memory services give you fine-grained control over allocations across boot phases, and how Boot Services and Runtime Services define the two operational worlds your code can inhabit.

## Chapters

### [Chapter 9: Driver Model]({% link part3/09-driver-model.md %})
Understand the UEFI driver binding protocol, the lifecycle of a driver from loading through starting and stopping, and how to write a complete driver that follows the UEFI 2.10 specification. Build and test a working driver in QEMU.

### [Chapter 10: Protocols and Handles]({% link part3/10-protocols-handles.md %})
Explore the handle database, GUIDs, and the protocol interfaces that form UEFI's component architecture. Learn to install, locate, open, and close protocols, and create your own custom protocol interface.

### [Chapter 11: Memory Services]({% link part3/11-memory-services.md %})
Master pool and page allocation, understand UEFI memory types, interpret the memory map, and avoid the common memory-related bugs that plague firmware code.

### [Chapter 12: Boot and Runtime Services]({% link part3/12-boot-runtime-services.md %})
Survey the full Boot Services and Runtime Services tables, work with events and timers, understand the critical ExitBootServices transition, and learn which services survive into the operating system runtime.

## Prerequisites

Before starting Part 3, you should have completed Parts 1 and 2, or at minimum:

- A working Project Mu build environment with QEMU
- Familiarity with `.inf` and `.dsc` file syntax
- Experience compiling and running a UEFI application
- Comfortable reading and writing C at an intermediate level

## Learning Path

After completing Part 3, continue to [Part 4]({% link part4/index.md %}) where you will apply these core concepts to build real-world firmware components including file system drivers, network stacks, and graphics output.
