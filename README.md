# Mini Compiler & Three-Address Code Generator

A lightweight compiler implemented in **C++** that demonstrates fundamental compiler construction concepts including lexical analysis, syntax analysis, Abstract Syntax Tree construction, symbol table management, intermediate code generation, and basic optimization.

## Overview

This project implements the core stages of a compiler for arithmetic assignment expressions.

### Example

Input:

```text
a = b + 2 * (c + 3)
```

Generated Three-Address Code:

```text
T1 = c + 3
T2 = 2 * T1
T3 = b + T2
a = T3
```

## Features

* Lexical analysis and tokenization
* Identifier and numeric constant recognition
* Arithmetic operator recognition
* Syntax analysis
* Context-Free Grammar based expression parsing
* Operator precedence handling
* Parentheses support
* Abstract Syntax Tree representation
* Symbol table using C++ STL data structures
* Three-Address Code generation
* Temporary variable generation
* Basic constant-folding optimization
* Error detection for invalid expressions
* Linux/UNIX compatible C++ implementation

## Compiler Pipeline

```text
Source Code
    |
    v
Lexical Analysis
    |
    v
Tokens
    |
    v
Syntax Analysis
    |
    v
Abstract Syntax Tree
    |
    v
Optimization
    |
    v
Three-Address Code
```

## Grammar

```text
Assignment → id = Expression

Expression → Term
           | Expression + Term
           | Expression - Term

Term → Factor
     | Term * Factor
     | Term / Factor

Factor → id
       | number
       | ( Expression )
```

## Technologies

* C++
* C++17
* STL
* Data Structures
* Compiler Design
* Linux/UNIX

## Build

Compile using:

```bash
g++ -std=c++17 main.cpp -o compiler
```

Run:

```bash
./compiler
```

## Sample Input

```text
a = b + 2 * (c + 3)
```

## Sample Output

```text
--- TOKENS ---
a = b + 2 * ( c + 3 )

Syntax Analysis: SUCCESS

--- THREE ADDRESS CODE ---
T1 = c + 3
T2 = 2 * T1
T3 = b + T2
a = T3
```

## Concepts Demonstrated

This project demonstrates practical understanding of:

* Compiler phases
* Lexical analysis
* Tokenization
* Context-Free Grammars
* Recursive-descent parsing
* Operator precedence
* Abstract Syntax Trees
* Symbol tables
* Intermediate Representation
* Three-Address Code
* Compiler optimization
* Data structures
* Error handling
* C++ programming

## Future Improvements

* Implement LL(1) parsing tables
* Add relational and logical operators
* Add type checking
* Add control-flow statements
* Generate assembly code
* Implement register allocation
* Add control-flow graph generation
* Add additional optimization passes

## Author

**Rohit Raj**

B.Tech Computer Science Engineering — AI & ML
IILM University, Greater Noida
