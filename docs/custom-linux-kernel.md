# Custom Linux Kernel Build

## Overview

This project involved building a customized Linux kernel from source. The workflow covered environment preparation, downloading kernel 6.1.0, changing kernel configuration to enable NTFS support, compiling the kernel, updating the boot configuration, and verifying the resulting installation.

## Workflow

1. Prepare the Ubuntu build environment and required development packages.
2. Obtain and extract the Linux 6.1.0 source tree.
3. Open the kernel configuration interface.
4. Enable the required NTFS filesystem support.
5. Compile the kernel and required modules.
6. Install the resulting kernel components.
7. Update the bootloader configuration.
8. Reboot and verify the selected kernel.

## Key Learning

The project moves beyond using Linux as an end user and demonstrates the relationship between kernel configuration, compilation, modules, and the boot process.

## Portfolio Value

Custom kernel work is a strong systems-oriented project because it demonstrates familiarity with Linux internals, build tooling, configuration, and system startup.

> **Safety note:** Kernel compilation and bootloader changes should be performed in a disposable virtual machine or other controlled environment. Always keep a known-good kernel available for recovery.
