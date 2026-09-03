# Project 1 — Basic Embedded System Simulator

**Author:** Menna Muhammed Ibrahim  
**Email:** menamohamed12122004@gmail.com  

---

## Overview

This project is a fundamental C application demonstrating core embedded programming concepts, fixed-width integer types (`stdint.h`), structured data handling, and input validation without standard library memory allocation overhead.

---

## Features & Implementation Highlights

- **Standard Fixed-Width Data Types:** Uses explicitly sized types (`uint8_t`, `uint16_t`, `uint32_t`) ensuring portable memory consumption across different target microcontrollers.
- **Robust Input Buffer Clearing:** Implements interactive input protection against invalid inputs or characters to prevent infinite execution loops and application crashes.
- **Static Memory Allocation:** Zero dynamic allocations (`malloc`/`free`) to align with safety-critical embedded coding standards (MISRA C principles).
- **Clean Structured Architecture:** Modular code design with isolated functions handling system operations, state processing, and formatted console output.

---

## How to Build and Run

### Prerequisites
- GCC Compiler (C99 standard compatible)

### Compilation
Open your terminal and run:

```bash
gcc -Wall -Wextra -std=c99 main.c -o project1