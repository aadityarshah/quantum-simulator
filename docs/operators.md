# Operators in Quantum Computing

In quantum computing, our vectors lie in the Hilbert space of dimension $2$ denoted by $\mathcal{H}^2$. The operators act on the basis vectors of the *Hilbert space* $\ket{0}$ and $\ket{1}$ and give a new vector in the Hilbert space itself. All of these operators we work with are ***linear***, which arises directly from the Schrödinger equation. Therefore, when we are dealing with quantum computing, or quantum mechanics in general, all operators we are concerned with are linear operators and thus, whenever we say "operator", will be referring to linear operators only.

By linear operator $\hat{A}$, what we mean is

$$
\hat{A}(\ket{\psi_1} + \ket{\psi_2}) = \hat{A}\ket{\psi_1} + \hat{A}\ket{\psi_2}
$$

I would recommend looking up [Qubit Algebra | The Quantum Notebook](https://aadityarshah.github.io/quantum-notebook/quantum-computing-and-information-notes/04-qubit-algebra#operators) for more info. It consists of the ideas and the foundations from where the implementation is inspired.

## Realizing Operators as Matrices

Once we define the computational basis vectors and use their coordinate representation, the operators acting on them can be realized by using $2 \times 2$ matrices.  These act upon the vector states to give a new vector state in the Hilbert space. 

In case of multiple qubits, this changes accordingly. Thus, for a $n$-qubit system, the operator is denoted by $2^n \times 2^n$ matrices. This is one of the most important things to note for performing further computations.

Thus, to implement them, we can store
- `num_qubits` : Number of qubits in the multi qubit system
- `size_t`: Number of rows/columns given by $2^n$ where $n$ is the number of qubits
- `elements`: A 2D array containing the $ij$-th elements in the operator matrix $\forall \, i, j \in \{1, \dots, n\}$ 

## Properties of Operators

### Multiplication of Operators

Multiplication of two operators is simple to realize since operators can be expressed in terms of matrices and thus, product of two operators is simply given by the product of the corresponding operator matrices. 

### Adjoint of Operator

An adjoint of an operator for our purposes will simply be conjugate tranpose of the operator matrix, that is, take the transpose of the operator matrix, and then perform complex conjugate for all the matrix elements present in the operator. Adjoint of an operator $\hat{A}$ is denoted by $\hat{A}^{\dagger}$. 

### Tensors of Operators

Given any operator with qubits $n_1$, and another operator with qubits $n_2$, the tensor product results in a new operator with $n_1 + n_2$ qubits and thus correspondingly a size of $2^{n_1 + n_2}$. This is computed by going through the matrix elements and multiplying them with matrix elements in the second operator preserving the representation breakdown. To explain it in a better, way consider the following example:

$$
A = \begin{bmatrix} 
0 & 1 \\
0 & 0
\end{bmatrix}
$$

$$
B = \begin{bmatrix}
1 & 0 \\
0 & 1
\end{bmatrix}
$$

Thus,

$$
A \otimes B = \begin{bmatrix}
0 \times \begin{bmatrix} 1 & 0 \\ 0 & 1 \end{bmatrix} & 1 \times \begin{bmatrix} 1 & 0 \\ 0 & 1 \end{bmatrix} \\
0 \times \begin{bmatrix} 1 & 0 \\ 0 & 1 \end{bmatrix} & 0 \times \begin{bmatrix} 1 & 0 \\ 0 & 1 \end{bmatrix} \\
\end{bmatrix}
$$

which gives us

$$
A \otimes B = \begin{bmatrix}
0 & 0 & 1 & 0 \\
0 & 0 & 0 & 1 \\
0 & 0 & 0 & 0 \\
0 & 0 & 0 & 0
\end{bmatrix}
$$

This is a computationally expensive task with the time complexity $\mathcal{O}(n_1^2 n_2^2)$ and the unfortunate part is this is a necessary calculation. Such tasks  are what become computationally very expensive making quantum simulations for larger multi-qubit systems not feasible for classical systems to simulate.

### Eigenvalues and Eigenvectors of Operators

For a $n$-qubit system, we will be having $2^n$ eigenvectors and correspondingly two eigenvalues. What we mean by eigenvectors and eigenvalues can be understood by the following:

Consider a linear operator $\hat{A}$ and a quantum state denoted by $\ket{a_i}$. If they satisfy

$$
A\ket{a_i} = a_i \ket{a_i}
$$

then, $a_i$ is the eigenvalue and $\ket{a_i}$ is the corresponding eigenvector.

Computing eigenvalues and eigenvectors for any $N \times N$ matrix could be best done in $\mathcal{O}(n^3)$. In quantum computing, we try to deal in Pauli operators and could express any operator in terms of the Identity operator and Pauli operators. We keep in mind the eigenvalues and eigenvectors for the pauli operators and thus accordingly, we could determine eigenvectors and eigenvalues of any operator. 

However, how this shall be implemented in code is not something too trivial to me at this point in time, but I will look forward to it in the future. For dealing with basic quantum gates and quantum circuits, the acting of operator on any quantum state is sufficient to work with. 

### Hermitian Operators

For operators to have physical significance, the observed outcomes must be real. Mathematically, this means they shall have real eigenvalues. Thus, in quantum computing, or broadly quantum mechanics, we deal with such operators and call them *Hermitian Operators*. For an operator $\hat{A}$ to be hermitian, it must satisfy 

$$
\hat{A} = \hat{A}^{\dagger}
$$