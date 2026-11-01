#include "gate.h"
#include <stdio.h>
#include <stdlib.h>

QuantumState apply_gate(QuantumState a, Gate gate) {
    size_t n = a.num_qubits, k = gate.num_qubits;
    size_t num_groups = 1ULL << (n - k);
    size_t num_local_states = 1ULL << k;
    for (size_t i = 0; i < num_groups; i++) {
        // TODO: Map it with non control and non target qubits according to those present in the
        // array of gate by `qubits`
        QuantumState localState;
        localState.num_qubits = (size_t)k;
        localState.size =
            num_local_states; // Since the number of elements in quantum state will also be 2^k
        localState.amplitudes = malloc(sizeof(Complex) * num_local_states);

        if (localState.amplitudes == NULL) {
            fprintf(stderr, "Error: Failed to allocate memory to localstate in apply_gate");
            return localState;
        }

        for (size_t j = 0; j < num_local_states; j++) {
            // TODO: Map with control and target qubits and record the values
        }
        // TODO: Process the stored values in a new local quantum state and have the operator act
        // upon it
        for (size_t j = 0; j < num_local_states; j++) {
            // TODO: Update the quantum state `a` with new values
        }
        free(localState.amplitudes);
    }
    return a;
}