---
layout: default
title: "Part 2: Project Mu Structure & Tooling"
nav_order: 3
has_children: true
permalink: /part2/
---

# Part 2: Project Mu Structure & Tooling
{: .fs-9 }

Understand how Project Mu organizes firmware code across repositories, builds it with stuart, manages dependencies, and validates changes through continuous integration.
{: .fs-6 .fw-300 }

---

## Overview

Part 1 introduced UEFI concepts and walked you through setting up a development environment. In Part 2, we shift focus to the **engineering infrastructure** that makes Project Mu a scalable, maintainable firmware platform.

Project Mu takes a fundamentally different approach from the traditional EDK2 monorepo model. Instead of a single massive repository, Project Mu distributes firmware code across purpose-specific repositories, each with clearly defined ownership and release cadence. Understanding this architecture is essential before you start writing production firmware.

This part covers five chapters:

### [Chapter 4: Repository Architecture]({% link part2/04-repo-architecture.md %})
How Project Mu splits UEFI firmware across multiple Git repositories, why it does so, and how the repositories relate to each other through dependency layers.

### [Chapter 5: Stuart Build System]({% link part2/05-stuart-build.md %})
A deep dive into `stuart`, the Python-based build orchestration layer that replaces ad-hoc EDK2 build scripts with a repeatable, cross-platform workflow.

### [Chapter 6: Dependency Management]({% link part2/06-dependencies.md %})
How Project Mu resolves external dependencies --- pip packages, NuGet binary tools, git submodules, and third-party libraries like OpenSSL --- and how to keep them up to date safely.

### [Chapter 7: Platform DSC/FDF Organization]({% link part2/07-platform-dsc-fdf.md %})
How platform description (DSC) and flash description (FDF) files are structured in a multi-repo world, including library class resolution, PCD layering, and shared includes.

### [Chapter 8: CI/CD Pipeline]({% link part2/08-ci-cd.md %})
How Project Mu validates every pull request with automated builds, code analysis, and compliance checks --- and how to set up the same pipeline for your own platform.

## What You Will Learn

By the end of Part 2, you will be able to:

- Navigate Project Mu's repository structure and understand each repository's role
- Use `stuart_setup`, `stuart_update`, and `stuart_build` to configure, sync, and build firmware
- Manage binary and source dependencies across repository boundaries
- Read and modify DSC/FDF files in a Project Mu platform
- Set up GitHub Actions CI pipelines for your own firmware project

## Prerequisites

You should have completed [Part 1]({% link part1/index.md %}) or have equivalent experience with:

- A working Project Mu development environment (Python, Git, compiler toolchain)
- Basic familiarity with UEFI concepts (boot phases, drivers, protocols)
- Comfort with command-line Git and Python workflows
