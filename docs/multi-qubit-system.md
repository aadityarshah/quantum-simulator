# Multi Qubit Systems

While dealing with practical quantum circuits, we almost always encounter more than a single qubit system. Therefore, one of the most important things in a quantum simulator is how several qubits are stored.  

A state $\ket{\psi}$ of a multi qubit system of $n$ qubits where each qubit's state is denoted by $\ket{\psi_i}$, $i = 1, \cdots, n$ can be represented by the tensor products

$$
\ket{\psi} = \ket{\psi_1} \otimes \ket{\psi_2} \otimes \cdots \otimes \ket{\psi_n}
$$

Since a qubit state can be simply represented by a $2 \times 1$ matrix, the tensor product can be expressed as a $2^n \times 1$ matrix for a $n$-qubit system. 

## Implementing Multi Qubit System State

To implement the representation of a multi qubit system's state along with operations on it, a simple structure needs to be found. 

### Array Implementation

A naive way will be to create a array consisting of $2^n$ elements as we will be knowing the number of qubits $n$ in the provided multi qubit system.

In highly entangled systems, this representation seems inefficient but at the same time, it is robust for small qubit systems. 

#### Trade-off while using array to store multi qubit systems

The data type `long double` in C takes upto $16$ bytes. Each `Complex` number consists of two `long double` entries thus sizing about $32$ bytes. Hence, each qubit state would require about $64$ bytes ($2^6$ bytes). 1 GB is about $2^30$ bytes and thus, 24 qubit system will take up 1 GB space. Moving ahead, 34 qubit system will take up 1 TB space. Thus, it is practically not feasible to simulate large multi qubit systems atleast in this manner. 

#### Parameters

For scope of this simulator, we will anyways to continue with the usage of an array for storing a multi-qubit system as it is the most robust known method. Thus, the parameters required will be as follows:
- `num_qubits` : Number of qubits in the multi qubit system
- `size_t` : Size of the array which will be given by $2^n$, but might be heplful to store.
- `states[size_t]` : Use `size_t` to initialise an array with $2^n$ Complex numbers.

It is helpful to note that the state of multi qubit system is often known as *composite quantum state* or *joint state*. Thus, we will call this state to be *QuantumState* in our code. 

#### Any other useful data strucutres?

While working with multi qubit systems, state change is very frequent so accession time must be quick. We don't need to insert or delete elements from the array once the system has been initialised thus making arrays a suitable data structure to use.

## Properties of Multi Qubit System State

### Global Phase Factors

Any quantum state can be multiplied by a global phase factor which would be a complex number that could be represented by $e^{i\theta}$. This could be ignored in particular cases since it does not have any physical significance in itself but it becomes important many times in multi-qubit systems when the state of one qubit is dependent on the others and their global phase factor, especially when the quantum state is a superposition of computational basis states instead of being purely in a computational basis state.

### Normalization

In a multi qubit system, the normalization is taken care of at the level of all qubits, not individual qubits i.e. the sum of square of probability amplitudes of the $2^n$ computational basis states must sum to exactly $1$. 

### Inner Product

For an inner product, we need two vectors from the same vector space. Since a qubit belongs to $\mathcal{H}^2$, a quantum state with $n$ qubits belongs to the Hilbert space $\mathcal{H}^{2^n}$. In such a case, the inner product could be computed by multiplying the probability amplitudes corresponding to each of the states (it must be noted that all the computational basis states even in a quantum state are orthonormal to each other).

### Tensor Product

Given any quantum state with qubits $n_1$, and another quantum state with qubits $n_2$, the tensor product results in a new quantum state with $n_1 + n_2$ qubits and thus correspondingly a size of $2^{n_1 + n_2}$. This is computed by going through probability amplitudes of computational basis states in the first quantum state and multiplying them with probability amplitudes of computational basis state in the second quantum state.