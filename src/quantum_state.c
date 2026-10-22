#include "quantum_state.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static const Complex zero_amplitudes[2] = {{1.0L, 0.0L}, {0.0L, 0.0L}};
static const Complex one_amplitudes[2] = {{0.0L, 0.0L}, {1.0L, 0.0L}};

const QuantumState ZERO_STATE = {1, 2, (Complex*)zero_amplitudes};
const QuantumState ONE_STATE = {1, 2, (Complex*)one_amplitudes};

QuantumState quantum_state_multiply_phase(QuantumState a, Complex b) {
    QuantumState result;
    result.num_qubits = a.num_qubits;
    result.size = a.size;
    result.amplitudes = malloc(sizeof(Complex) * result.size);
    if (result.amplitudes == NULL) {
        fprintf(stderr, "Error: failed to allocate memory");
        return a;
    }
    for (size_t i = 0; i < a.size; i++) {
        result.amplitudes[i] = complex_multiply(a.amplitudes[i], b);
    }

    return result;
}

long double quantum_state_norm(QuantumState a) {
    long double norm = 0.0L;
    for (size_t i = 0; i < a.size; i++) {
        long double magn = complex_magnitude(a.amplitudes[i]);
        norm += magn * magn;
    }
    return sqrtl(norm);
}

Complex quantum_states_inner_product(QuantumState a, QuantumState b) {
    if (a.num_qubits != b.num_qubits) {
        fprintf(stderr, "Error: cannot compute inner product between two quantum states with "
                        "different number of qubits.\n");
        return (Complex){0.0L, 0.0L};
    }

    Complex inner_product = {0.0L, 0.0L};
    for (size_t i = 0; i < a.size; i++) {
        inner_product =
            complex_add(inner_product, complex_multiply(a.amplitudes[i], b.amplitudes[i]));
    }
    return inner_product;
}

void quantum_state_normalize(QuantumState* a) {
    long double norm_val = quantum_state_norm(*a);
    if (norm_val == 0.0L) {
        fprintf(stderr, "Error: zero qubit cannot be normalized.\n");
        return;
    }

    Complex mul_factor = {1.0L / norm_val, 0.0L};

    for (size_t i = 0; i < a->size; i++) {
        a->amplitudes[i] = complex_multiply(a->amplitudes[i], mul_factor);
    }
}

QuantumState quantum_states_tensor(QuantumState a, QuantumState b) {
    QuantumState tensor_product;
    tensor_product.num_qubits = a.num_qubits + b.num_qubits;
    tensor_product.size = a.size * b.size;
    tensor_product.amplitudes = malloc(sizeof(Complex) * tensor_product.size);
    if (tensor_product.amplitudes == NULL) {
        fprintf(stderr, "Error: failed to allocate memory.\n");
        return ZERO_STATE;
    }
    for (size_t i = 0; i < a.size; i++) {
        for (size_t j = 0; j < b.size; j++) {
            tensor_product.amplitudes[b.size * i + j] =
                complex_multiply(a.amplitudes[i], b.amplitudes[j]);
        }
    }
    return tensor_product;
}

void quantum_state_print(QuantumState a) {
    printf("--- Quantum State ---\n");
    for (size_t i = 0; i < a.size; i++) {
        printf("|");
        for (int bit = a.num_qubits - 1; bit >= 0; bit--) {
            size_t k = (i >> bit) & 1;
            printf("%zu", k);
        }
        printf("> : ");
        complex_print(a.amplitudes[i]);
    }
}