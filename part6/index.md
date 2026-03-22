---
layout: default
title: "Part 6: Practical Projects"
nav_order: 8
has_children: true
permalink: /part6/
---

# Part 6: Practical Projects

This part brings together everything you have learned throughout the guide into four complete, self-contained projects. Each project is designed to exercise a different cross-section of UEFI and Project Mu concepts, from shell scripting and graphical UI to networking and boot loading.

## What You Will Build

| Chapter | Project | Key Skills |
|---------|---------|------------|
| 28 | Custom Shell Command | ShellPkg, parameter parsing, HII help text |
| 29 | Graphical Boot Menu | GOP framebuffer, console input, boot variables |
| 30 | Network Application | HTTP client, DNS, TCP/IP, TLS basics |
| 31 | Custom Boot Loader | Filesystem access, ExitBootServices, kernel handoff |

## Prerequisites

Before starting these projects you should be comfortable with:

- Writing DXE drivers and UEFI applications (Parts 2 and 3)
- Protocol location, installation, and consumption (Part 3)
- Building with stuart and testing in QEMU (Part 4)
- Hardware interaction patterns covered in Part 5

Each chapter provides complete, compilable source code along with the corresponding INF and DSC fragments needed to build with Project Mu's stuart system. All projects are tested inside QEMU so no physical hardware is required.
