---
layout: default
title: "Part 4: Essential UEFI Services"
nav_order: 6
has_children: true
permalink: /part4/
---

# Part 4: Essential UEFI Services
{: .fs-9 }

Master the core UEFI protocols that let your firmware interact with hardware, storage, networks, and users.
{: .fs-6 .fw-300 }

---

## Overview

Part 4 dives into the essential UEFI services that every firmware developer must understand. These protocols form the backbone of UEFI's hardware abstraction layer, providing standardized interfaces for console interaction, graphics rendering, file system access, block-level storage, networking, and persistent variable storage.

Each chapter focuses on a specific protocol family, providing both the conceptual framework and practical C code examples that you can build and run in your Project Mu environment. By the end of Part 4, you will be able to build sophisticated UEFI applications that interact with virtually every major subsystem available in the pre-boot environment.

## Chapters

### [Chapter 13: Console I/O]({% link part4/13-console-io.md %})
Work with the Simple Text Input and Output protocols to read keystrokes, display formatted text with color attributes, position the cursor, and build interactive text-based menus.

### [Chapter 14: Graphics Output (GOP)]({% link part4/14-graphics-output.md %})
Use the Graphics Output Protocol to query and set video modes, access the framebuffer directly, draw pixels, lines, and filled rectangles, perform BLT (Block Transfer) operations, and implement double buffering for flicker-free rendering.

### [Chapter 15: File System Access]({% link part4/15-file-system.md %})
Navigate the Simple File System Protocol and EFI_FILE_PROTOCOL to open, read, write, and close files, enumerate directories, query file attributes, and create or delete files on FAT-formatted volumes.

### [Chapter 16: Block I/O]({% link part4/16-block-io.md %})
Access raw storage devices through the Block I/O Protocol, read and write disk sectors, detect GPT and MBR partition schemes, enumerate available storage devices, and understand the relationship between block devices and file systems.

### [Chapter 17: Network Stack]({% link part4/17-network.md %})
Explore the layered UEFI network architecture from the Simple Network Protocol up through IP, TCP, UDP, DNS, and HTTP. Learn to configure network interfaces via DHCP, establish TCP connections, send UDP datagrams, and understand TLS support.

### [Chapter 18: UEFI Variables]({% link part4/18-variables.md %})
Understand the UEFI variable store, work with GetVariable and SetVariable runtime services, explore standard variables like Boot#### and BootOrder, learn about authenticated and Secure Boot variables, and follow best practices for variable management.

## Prerequisites

Before starting Part 4, you should be comfortable with:

- Writing and building UEFI applications (Parts 1-2)
- Using `LocateProtocol` and `LocateHandleBuffer` to find protocol instances (Part 3)
- The handle database and protocol interface model (Part 3)
- UEFI memory management basics (Part 3)
