# CSach
## Sachkeerat Singh Brar's Custom Programming Language

Welcome to the repository of my custom programming language! This project is a personal endeavor to learn and explore the C programming language (hence the name is C + Sach) by developing a new programming language from scratch. Inspired by [Ianertson's YouTube tutorials](https://www.youtube.com/@helloworldcode), this project serves a way for me to learn C in a creative way.

## Table of Contents

- [Introduction](#introduction)
- [Features](#features)
- [Getting Started](#getting-started)
  - [Prerequisites](#prerequisites)
  - [Usage](#usage)
- [Examples](#examples)
- [Acknowledgements](#acknowledgements)

## Introduction

This project is designed to help me (and potentially others) learn the fundamentals of the C programming language by building a new programming language. It provides a hands-on approach to understanding compiler design, syntax parsing, and other core concepts of programming languages.

## Features

- **Variable Declaration and Printing**: Currently, you can create variables and print their values.

## Getting Started

### Prerequisites

Before you begin, ensure you have met the following requirements:

- You have a C compiler installed (e.g., `gcc`, `clang`).
- You have `sudo` and `make` installed for Unix-like systems.

### Usage
**Unix-like Systems (Linux, macOS)**
1. Clone the repository
    ```sh
    git clone https://github.com/sachkeeratb/CSach.git
    ```
2. Navigate to the project directory
    ```sh
    cd CSach
    ```
3. Compile the project\
    a) Locally
    ```sh
    make
    ```

    or

    b) System-wide
    ```sh
    sudo make install
    ```
 
4. Run the interpreter\
    a) With local use
    ```sh
    ./csach.out <filePath>
    ```
    or

    b) With system-wide use
    ```sh
    csach <filePath>

5. The optional step to uninstall\
    a) Locally
    ```sh
    cd ..
    rm -rf CSach
    ```
    or

    b) System-wide
    ```sh
    sudo make uninstall
    ```
    
    or
    
    c) System-wide without the CSach Makefile
    ```sh
    sudo rm /usr/local/bin/csach
    ```
\
**Windows**
1. Clone the repository
    ```cmd
    git clone https://github.com/sachkeeratb/CSach.git
    ```
2. Navigate to the project directory:
    ```cmd
    cd CSach
    ```
3. \
    a) Compile the project using `gcc`
    ```cmd
   gcc -o csach.exe main.c
   ```

    or

    b) Compile the project using `clang`
    ```cmd
    clang -o csach.exe main.c
    ```

4. Run the interpreter
    ```cmd
    csach.exe <filePath>
    ```

5. The optional step to uninstall
    ```cmd
    cd ..
    rmdir /s CSach
    ```
    

## Examples

Here's an example of how to use the current features

```
let name = "Sachkeerat Singh Brar";
let otherName = "Other Name";
print(name, otherName);
```
Output:
```
Sachkeerat Singh Brar
Other Name
```

## Acknowledgements
Special thanks to [Ianertson](https://www.youtube.com/@helloworldcode) for the amazing tutorial series that inspired this project.