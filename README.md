# CSach

## Sachkeerat Singh Brar's Custom Programming Language

Welcome to the repository of my custom programming language! This project is a personal endeavor to learn and explore the C programming language (hence the name is C + Sach) by developing an interpreter to create a new programming language. Inspired by [Ianertson's](https://www.youtube.com/@helloworldcode) YouTube tutorials, this project serves a way for me to learn C in a creative way.

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

- **Variable Declaration and Printing**: You can create variables and print their values.
- **Function Declaration and Calling**: You can create your own functions with custom arguments and call them in their scope.
- **Variable types**: Long integers, strings, and characters. Explicit annotation coming soon.
- **Math**: You can use integers. Basic math features are implemented. Other than parentheses, the order of operations is respected.

## Getting Started

### Prerequisites

Before you begin, ensure you have met the following requirements:

- You have a C compiler installed (`gcc` or `clang`).
- You have `make` installed.
- You have `sudo` installed for Unix-like systems.

### Usage

**Unix-like Systems (Linux, macOS)**

1.  Clone the repository
    ```sh
    git clone https://github.com/sachkeeratb/CSach.git
    ```
2.  Navigate to the project directory
    ```sh
    cd CSach
    ```
3.  Compile the project\
    a) Locally

    ```sh
    make
    ```

    or

    b) System-wide

    ```sh
    sudo make install
    ```

4.  Run the interpreter\
    a) With local use

    ```sh
    ./csach.out <filePath>
    ```

    or

    b) With system-wide use

    ```sh
    csach <filePath>
    ```

5.  The optional step to uninstall\
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
**Windows**\
TODO

## Examples

Here's an example of how to use the current features

```
let greeting = "Hello, " + "world!";

let a = 2 + 2 * 3 + 2 / 2 + 4^2;

func main() {
  println(greeting);
  let statement = "Nice to meet you!";
  println(statement);
  println();
  print("The value of a is", a, "and that's cool!");
};
main();
```

Output:

```
Hello, world!
Nice to meet you!

The value of a is 25 and that's cool!
```

## Acknowledgements

Special thanks to [Ianertson](https://github.com/sebbekarlsson) for the amazing tutorial series on [YouTube](https://www.youtube.com/@helloworldcode) and his [GitHub Repository](https://github.com/sebbekarlsson/hello) that inspired this project.
