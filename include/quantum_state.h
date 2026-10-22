#ifndef QUANTUM_STATE_H
#define QUANTUM_STATE_H

#include "complex.h"
#include <stdio.h>

/**
 * @brief Stores the probability amplitudes of a composite quantum state corresponding to
 * computational basis states
 */
typedef struct {
    int num_qubits;
    size_t size;
    Complex* amplitudes;
} QuantumState;

/**
 * The single qubit quantum state in state |0>
 */
extern const QuantumState ZERO_STATE;

/**
 * The single qubit quantum state in state |1>
 */
extern const QuantumState ONE_STATE;

/**
 * Multiplies the given quantum state by a global phase factor
 *
 * @param a A quantum state
 * @param b A global phase factor
 * @returns A quantum state obtained by multiplying the probability amplitudes of computational
 * basis states of quantum state `a` by the global phase factor `b`.
 */
QuantumState quantum_state_multiply_phase(QuantumState a, Complex b);

/**
 * Computes the norm of the quantum state which is the quantum state's inner product with itself.
 *
 * @param a A quantum state
 * @returns The norm of the quantum state <a|a>
 */
long double quantum_state_norm(QuantumState a);

/**
 * Compute the inner product of two given quantum states belonging to same vector space, that is,
 * they have same number of qubits
 *
 * @param a First quantum state with n qubits
 * @param b Second quantum state with n qubits
 * @returns The complex inner product <a|b>
 */
Complex quantum_states_inner_product(QuantumState a, QuantumState b);

/**
 * Normalises the given quantum state in-place
 *
 * @param A quantum state pointer
 */
void quantum_state_normalize(QuantumState* a);

/**
 * Computes the tensor product of two given quantum states
 *
 * @param a First quantum state
 * @param b Second quatum state
 * @returns A quantum state obtained by the tensor product a \otimes b
 */
QuantumState quantum_states_tensor(QuantumState a, QuantumState b);

void quantum_state_print(QuantumState a);

#endif