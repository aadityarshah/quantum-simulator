# Quantum Gates

Quantum Gates are special unitary operators that act on a qubit to obtain specific states of it. We use single and multi qubit gates for the same. 

An operator $\hat{U}$ is unitary, for our purposes, if its inverse equals to its adjoint. Therefore,

$$
\hat{U}^{\dagger} \hat{U} = \hat{U} \hat{U}^{\dagger} = I
$$

The operators are required to be unitary by the laws of quantum mechanics in order to conserve probability.

A set of gates is called universal if any arbitrary unitary operation can be approximated to high precision by combining them.

Commonly used single qubit gates are the following:
- Pauli X (NOT) gate
- Pauli Y gate
- Pauli Z gate
- T gate
- S (Phase) gate
- H (Hadamard) gate

Commonly used multi-qubit gates are the following:
- CNOT gate
- SWAP gate
- Toffolo (CCNOT) gate

Refer to [Quantum Gates | The Quantum Notebook](https://aadityarshah.github.io/quantum-notebook/quantum-computing-and-information-notes/05-quantum-gates) for more details.

## Implementing Gates

To integrate quantum gates, generalised operators can be used, ensuring only that they are unitary. But we also need additional information especially in case of arbitrary multi qubit gates which contain which qubits are the control qubits and which the target qubits. Thus, along with the operator, we introduce the parameter `qubits` which stores the indices of the qubits that the operator acts upon in the given quantum state, in an order manner such that last one is the target qubit whereas all the other qubits are control qubits.

Once we store the gate, the difficult task is to implement them on any arbitrary state. The reason is that the provided quantum state could control of $n$ qubits whereas the gate would be acting only on a few of them and intended to leave others unaffected. 

To implement this, there were two approaches that came into my mind:

(1) Naive approach

Use identity matrices and tensor them with gate's operator in between for all the qubits that shall remain unchanged. This shall be easy to implement for single qubit gates but would be troublesome to implemnent for controlled gates and highly computationally expensive as it will require whole matrix reconstruction.

(2) Optimized approach

Focus on the computational basis states especially the ones in which the qubits involved only change with others being constant and apply the operator focused on those particular states. This won't require whole matrix reconstruction and is way less expensive, both memory and time-wise than the naive approach.

Another thing which could be thought about is adding specialised functions for particular standard gate operations like X, Y, Z, CNOT, etc. which use the standard properties of these gates to perform the computation even more quickly but this is just a top of the head idea and ould be looked into in the future for further optimizations in the future.

### Algorithm for the Optimized Approach

The aim is to implement an arbitrary $k$ qubits quantum gate on the provided $n$ qubits quantum state. For this, an algorithm is presented in an informal manner.

Consider a $n$ qubit system provided as a quantum state represented by $S$, with $n_1$ control qubits with their indices representing the decimal equivalent of the binary representation of the computational basis states for the system which are stored in the first $q$ indices of `qubits` array and a target qubit's index at the end of the `qubits` array.

Let's the denote the array `qubits` by $Q$. Focus on the control qubits and target qubits. Our aim is to find combinations in which all the qubits in $S - Q$ have the same values and those in $Q$ differ progressively according to control qubits order. Then form a quantum state from these for the operator to act upon and then perform the action.

In computational basis representation, the rightmost bit is the least significant bit, thus the highest index has least weightage. An $i$-th bit has a weightage of $2^{n-i-1}$. So, with the control qubits known, those mentioned first are given the highest weightage. Now, let us first set all qubits to zero. Now, we start in the order of increasing bits in the target and then control qubits from right to left in the array in order to obtain the current coefficients of relevant states and then apply operator on these obtained bits. After this, we look into $S - Q$ and increase each qubit in similar order or randomly (this order won't matter if all arrangements are covered because ordering matters in quantum state, however if all changes occur, then order is irrelevant and this also allows for *parallelism*, i.e. performing operator on multiple arrangements simultaneously in multiple threads.)
