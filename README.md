# UEFI Project Mu Development Guide

A comprehensive tutorial and reference for UEFI firmware development using Microsoft's [Project Mu](https://microsoft.github.io/mu/) framework.

**Live Site:** [https://michaeltien8901.github.io/uefi-mu-guide-tutorial/](https://michaeltien8901.github.io/uefi-mu-guide-tutorial/)

## What's Inside

| Part | Chapters | Topics |
|------|----------|--------|
| **Part 1: Getting Started** | Ch 1-3 | Introduction, environment setup, Hello World |
| **Part 2: Structure & Tooling** | Ch 4-8 | Multi-repo architecture, Stuart build, dependencies, CI/CD |
| **Part 3: Core Concepts** | Ch 9-12 | Driver model, protocols/handles, memory, boot/runtime services |
| **Part 4: Essential Services** | Ch 13-18 | Console I/O, graphics (GOP), file system, block I/O, networking, variables |
| **Part 5: Advanced Topics** | Ch 19-27 | PEI/DXE, SMM, security, ACPI, capsule updates, DFCI, Rust, testing |
| **Part 6: Projects** | Ch 28-31 | Shell command, boot menu, network app, boot loader |
| **Appendices** | A-F | EDK2 build system, migration guide, debugging, references, glossary |

## Study Guides by Role

- **UEFI Application Developer** - Ch 1-3, 9-18, 28-31
- **Platform / Firmware Engineer** - Ch 1-8, 19-20, 23, 27
- **Security Engineer** - Ch 1-3, 21-22, 24-25
- **EDK2-to-Mu Migrator** - Ch 4-8, Appendix B

## Example Code

The [`examples/UefiMuGuidePkg/`](examples/UefiMuGuidePkg/) directory contains 15 buildable UEFI examples covering every hands-on chapter.

## Building the Site Locally

```bash
bundle install
bundle exec jekyll serve
```

## Source Repository

Development repo: [uefi-mu-guide-tutorial-openspec](https://github.com/MichaelTien8901/uefi-mu-guide-tutorial-openspec)

This deploy repo is generated via `git subtree split --prefix=docs` from the development repo.
