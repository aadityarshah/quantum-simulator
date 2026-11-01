#ifndef GATE_H
#define GATE_H

#include "operator.h"
#include <stdio.h>

/**
 * @brief Represents a quantum gate carrying additional information about target qubits and number
 * of target qubits along with the operator.
 */
typedef struct {
    Operator op;
    size_t num_qubits; /** Number of qubits involved in the operation, that is, all control and
                          target qubits */
    size_t* qubits;    /** Indices of qubits in the quantum circuit such that first control qubits
                          appear and target qubits at the end*/
} Gate;

/**
 * Apply a quantum gate to a quantum state with any number of qubits greater than or equal to that
 * on gate's operator acts upon
 *
 * @param a A quantum state in the quantum circuit
 * @param gate The gate that acts upon the quantum state
 *
 * @returns The quantum state obtained when `gate` acts upon `a`
 */
QuantumState apply_gate(QuantumState a, Gate gate);

#endif