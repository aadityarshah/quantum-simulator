# Quantum Simulator

A state-vector quantum circuit simulator implemented from first principles in C.

## Project Status

🚧 Under development.

## Overview

This project aims to implement a basic quantum circuit simulator from scratch in C, with an emphasis on understanding the mathematical foundations and computational implementation of quantum gates and circuits. 

Currently, the project implements the following:
- Complex-number arithmetic
- Qubit representation 
- Bloch sphere representation of a qubit
- Quantum-state representation
- Multi-qubit operators

I will soon be implementing the following:
- Quantum gates (enforcing unitarity and adapting generalised operators for use in quantum circuits)
- Measurement
- Quantum circuits

Once quantum circuit simulation is verified and ready, the aim is to try implementing basic quantum algorithms and also perform performance analysis compared to existing Quantum Programming frameworks like Qiskit and Cirq.

## Goals

- Understand how quantum states and gates are represented computationally.
- Implement the mathematical operations underlying quantum circuits.
- Explore efficient state-vector simulation.
- Analyze the computational and memory scaling of quantum simulation.

## How to use?

Clone the repository by

```bash
git clone https://github.com/aadityarshah/quantum-simulator
```

Run the existing tests (present in the [`tests`](./tests/) directory) by

```bash
make test
```

The repository is structured as follows:
- [`docs`](./docs/)  directory contains the documentation for explanation and some implementation based choices for implementing quantum states and operators.
- [`include`](./include/) directory contains the header files which declare the constant variables and functions to be implemented and the docstrings for the functions.
- [`src`](./src/) directory contains the source code implementing the functions declared in the `include` directory.
- [`tests`](./tests/) directory contains the tests for testing the implementations of all implemented functions.

## AI Disclosure

The aim of this repository is to understand mathematical foundations and implementing everything from scratch according to my knowledge and understand of fundamentals of quantum computing. Thus, all the documentation and code in `docs`, `include`, `src` directories is completely written by me. However, `Makefile`, githooks, github workflows, PR template, `clang` checks for formatting and only the tests for the complex numbers in `tests/test_complex.c`c were implemented using OpenAI's ChatGPT. All the descriptions in pull requests have been written by me and I have complete understanding of the implementation.

## Language

- C (C17)