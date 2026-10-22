#include "operator.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static Complex zero_elements[4] = {{0.0L, 0.0L}, {0.0L, 0.0L}, {0.0L, 0.0L}, {0.0L, 0.0L}};
const Operator ZERO_OPERATOR = {.num_qubits = 1, .size = 2, .elements = zero_elements};

static Complex identity_elements[4] = {{1.0L, 0.0L}, {0.0L, 0.0L}, {0.0L, 0.0L}, {1.0L, 0.0L}};
const Operator IDENTITY_OPERATOR = {.num_qubits = 1, .size = 2, .elements = identity_elements};

static Complex x_elements[4] = {{0.0L, 0.0L}, {1.0L, 0.0L}, {1.0L, 0.0L}, {0.0L, 0.0L}};
const Operator X_OPERATOR = {.num_qubits = 1, .size = 2, .elements = x_elements};

static Complex y_elements[4] = {{0.0L, 0.0L}, {0.0L, -1.0L}, {0.0L, 1.0L}, {0.0L, 0.0L}};
const Operator Y_OPERATOR = {.num_qubits = 1, .size = 2, .elements = y_elements};

static Complex z_elements[4] = {{1.0L, 0.0L}, {0.0L, 0.0L}, {0.0L, 0.0L}, {-1.0L, 0.0L}};
const Operator Z_OPERATOR = {.num_qubits = 1, .size = 2, .elements = z_elements};

QuantumState operate_on_quantum_state(Operator A, QuantumState a) {
    if (A.num_qubits != a.num_qubits || A.size != a.size) {
        fprintf(stderr,
                "Error: The operator must be defined on the same vector space as that of the "
                "quantum state.\n");
        return ZERO_STATE;
    }

    QuantumState result;
    result.num_qubits = a.num_qubits;
    result.size = a.size;
    result.amplitudes = malloc(sizeof(Complex) * result.size * result.size);

    for (size_t i = 0; i < A.size; i++) {
        Complex element = {0.0L, 0.0L};
        for (size_t j = 0; j < A.size; j++)
            element =
                complex_add(element, complex_multiply(A.elements[A.size * i + j], a.amplitudes[j]));
        result.amplitudes[i] = element;
    }

    return result;
}

// Uses a standard naive algorithm and it could be optimized further using advanced algorithms like
// Strassen's algorithm but that will increase code complexity unnecessarily and also introduce very
// high hidden constants
Operator operators_multiply(Operator A, Operator B) {
    if (A.num_qubits != B.num_qubits || A.size != B.size) {
        fprintf(stderr, "Error: Both the operators must be defined on the same vector space for "
                        "their multiplication.");
        return A;
    }

    Operator result;
    result.num_qubits = A.num_qubits;
    result.size = A.size;
    result.elements = malloc(sizeof(Complex) * result.size * result.size);

    for (size_t i = 0; i < result.size; i++) {
        for (size_t j = 0; j < result.size; j++) {
            Complex element = {0.0L, 0.0L};
            for (size_t k = 0; k < result.size; k++) {
                element = complex_add(element, complex_multiply(A.elements[A.size * i + k],
                                                                B.elements[B.size * k + j]));
            }
            result.elements[A.size * i + j] = element;
        }
    }

    return result;
}

Operator operator_adjoint(Operator A) {
    Operator adjoint_A;
    adjoint_A.num_qubits = A.num_qubits;
    adjoint_A.size = A.size;
    adjoint_A.elements = malloc(sizeof(Complex) * adjoint_A.size * adjoint_A.size);

    if (adjoint_A.elements == NULL) {
        fprintf(stderr, "Error: failed to allocate memory");
        return A;
    }

    for (size_t i = 0; i < A.size; i++) {
        for (size_t j = 0; j < A.size; j++) {
            adjoint_A.elements[A.size * i + j] = complex_conjugate(A.elements[A.size * j + i]);
        }
    }

    return adjoint_A;
}

static int complex_equal(Complex a, Complex b) {
    return (a.x == b.x) && (a.y == b.y);
}

int operator_is_hermitian(Operator A) {
    int is_hermitian = 1;
    for (size_t i = 0; i < A.size; i++) {
        for (size_t j = 0; j < A.size; j++) {
            if (!complex_equal(A.elements[A.size * i + j],
                               complex_conjugate(A.elements[A.size * j + i])))
                is_hermitian = 0;
        }
    }

    return is_hermitian;
}

Operator operators_tensor(Operator A, Operator B) {
    Operator tensor_product;
    tensor_product.num_qubits = A.num_qubits + B.num_qubits;
    tensor_product.size = A.size * B.size;
    tensor_product.elements = malloc(sizeof(Complex) * tensor_product.size);
    if (tensor_product.elements == NULL) {
        fprintf(stderr, "Error: failed to allocate memory.\n");
        return tensor_product;
    }
    for (size_t i = 0; i < A.size; i++) {
        for (size_t j = 0; j < A.size; j++) {
            for (size_t k = 0; k < B.size; k++) {
                for (size_t l = 0; l < B.size; l++) {
                    tensor_product.elements[A.size * B.size * (B.size * i + k) + B.size * j + l] =
                        complex_multiply(A.elements[A.size * i + j], B.elements[B.size * k + l]);
                }
            }
        }
    }

    return tensor_product;
}

static void complex_print_inline(Complex a) {
    if (a.y < 0) {
        printf("%#.6Lg - %#.6Lgi ", a.x, -a.y);
    } else {
        printf("%#.6Lg + %#.6Lgi ", a.x, a.y);
    }
}

void operator_print(Operator A) {
    printf("--- Operator ---\n");
    for (size_t i = 0; i < A.size; i++) {
        printf("[ ");
        for (size_t j = 0; j < A.size; j++) {
            complex_print_inline(A.elements[A.size * i + j]);
        }
        printf("]\n");
    }
}