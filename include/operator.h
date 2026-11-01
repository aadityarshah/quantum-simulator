#ifndef OPERATOR_H
#define OPERATOR_H

#include "quantum_state.h"
#include <stdio.h>

/**
 * @brief Stores the matrix elements of the operator
 */
typedef struct {
    size_t num_qubits;
    size_t size;
    Complex* elements;
} Operator;

/**
 * Single qubit zero operator
 */
extern const Operator ZERO_OPERATOR;

/**
 * Single qubit identity operator
 */
extern const Operator IDENTITY_OPERATOR;

/**
 * Pauli's X operator
 */
extern const Operator X_OPERATOR;

/**
 * Pauli's Y operator
 */
extern const Operator Y_OPERATOR;

/**
 * Pauli's Z operator;
 */
extern const Operator Z_OPERATOR;

/**
 * T gate
 */
extern const Operator T_OPERATOR;

/**
 * Phase gate
 */
extern const Operator S_OPERATOR;

/**
 * Hadamard gate
 */
extern const Operator H_OPERATOR;

/**
 * CNOT gate
 */
extern const Operator CX_OPERATOR;

/**
 * Computes the new quantum state obtained when given operator acts on the given quantum state
 *
 * @param A An operator
 * @param a A quantum state
 * @returns A new quantum state obtained when operator `A` acts on the quantum state `a`
 */
QuantumState operate_on_quantum_state(Operator A, QuantumState a);

/**
 * Computes the product of two given operators
 *
 * @param A First operator (acts later)
 * @param B Second operator (acts first)
 * @returns The operator `AB` obtained by the product of the operators `A` and `B`
 */
Operator operators_multiply(Operator A, Operator B);

/**
 * Computes the adjoint operator of the given operator
 *
 * @param A An operator
 * @returns Adjoint operator corresponding to the operator `A`
 */
Operator operator_adjoint(Operator A);

/**
 * Checks if the given operator is Hermitian
 *
 * @param A An operator
 * @returns `0` if the operator `A` is not Hermitian and `1` otherwise
 */
int operator_is_hermitian(Operator A);

/**
 * Compute the tensor product of two given operators
 *
 * @param A First operator
 * @param B Second operator
 * @returns An operator obtained by tensor product $A \otimes B$
 */
Operator operators_tensor(Operator A, Operator B);

/**
 * Check if the given operator is Unitary
 *
 * @param A An operator
 * @returns `0` if the operator `A` is not Unitary and `1` otherwise
 */
int operator_is_unitary(Operator A);

void operator_print(Operator A);

#endif