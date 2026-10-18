# Postfix-Code-Generator

A small console program in C++ that takes a **postfix (reverse Polish) expression** and prints the **assembly-like instructions** needed to compute it. It simulates, in a simplified form, the code-generation step of a compiler. The program only generates instructions; it does not evaluate the expression.

![C++](https://img.shields.io/badge/C%2B%2B-OOP-blue)
![Platform](https://img.shields.io/badge/Platform-Windows-informational)
![IDE](https://img.shields.io/badge/IDE-Visual%20Studio%202022-purple)

---

## Overview

A compiler translates high-level source code into simple machine instructions that a CPU can execute. This project was written for a Data Structures course to practice the idea behind that step on a small scale: the user enters a postfix expression such as `AB+C*`, and the program prints the instruction sequence that computes it using a few simple instructions and temporary storage locations.

The whole program is one class, `clsCodeGenerator`, which uses a `std::stack<string>` to keep track of operands. Postfix notation fits a stack naturally: operands are pushed as they are read, and each operator works on the most recent operands.

## Instruction set

| Instruction | Meaning |
|---|---|
| `LD X` | Load operand `X` |
| `AD X` | Add `X` to the loaded value |
| `SB X` | Subtract `X` from the loaded value |
| `ML X` | Multiply the loaded value by `X` |
| `DV X` | Divide the loaded value by `X` |
| `ST TempN` | Store the result in a temporary named `TempN` |

The instructions follow a simple accumulator-style pattern (load, operate, store). They are a teaching model, not the instruction set of a real CPU.

## How it works

The program reads the expression character by character:

1. **Operand** (uppercase letter `A`–`Z`): push it onto the `_Operands` stack.
2. **Operator** (`+`, `-`, `*`, `/`): if the stack holds at least two items, take the top item as the right operand and the one below it as the left operand, then print:
   - `LD <left>`
   - the instruction for the operator (`AD`, `SB`, `ML` or `DV`) with `<right>`
   - `ST TempN`, where `N` is a counter that increases with each operation

   Both operands are then removed from the stack and `TempN` is pushed in their place. It acts as an operand for any later operator.
3. **Anything else**, or an operator when fewer than two operands are on the stack: the program prints `Invalid Postfix Operation!` and continues with the next character.

## Examples

**Input:** `AB+C*` (that is, `(A + B) * C`)

```
LD A
AD B
ST Temp1
LD Temp1
ML C
ST Temp2
```

**Input:** `ABC*+` (that is, `A + (B * C)`)

```
LD B
ML C
ST Temp1
LD A
AD Temp1
ST Temp2
```

**Input:** `AB-CD/*` (that is, `(A - B) * (C / D)`)

```
LD A
SB B
ST Temp1
LD C
DV D
ST Temp2
LD Temp1
ML Temp2
ST Temp3
```

## Limitations

- Operands must be **single uppercase letters** (`A`–`Z`). Numbers, lowercase letters and multi-character names are not supported.
- The input must already be in **postfix form**. There is no infix-to-postfix conversion.
- The expression must be entered **without spaces**, because it is read with `cin >>`.
- Validation is basic. Invalid characters and operators with too few operands are reported, but the program does not stop at the first error. It also does not check for leftover operands at the end, so an incomplete expression such as `AB` prints nothing.
- There is no register allocation or optimization. Every operation stores its result in a new temporary.

## Build and run

### Visual Studio 2022/2026 Community

1. Install Visual Studio Community with the **Desktop development with C++** workload.
2. Clone the repo: `git clone https://github.com/MuhammedEsmer67/Postfix-Code-Generator.git`
3. Create an empty **Console App** project and add `Postfix_Computer_Architecture.cpp` to it.
4. Press **Ctrl + F5** (Start Without Debugging). A console window shows the output.

### PowerShell (g++)

```
cd Postfix-Code-Generator
g++ -std=c++17 Postfix_Computer_Architecture.cpp -o PostfixGenerator
.\PostfixGenerator
```
