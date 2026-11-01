#include "operator.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define EPSILON 1e-12
#define INV_SQRT_2 0.70710678118654752440L

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

static Complex T_elements[4] = {{1.0L, 0.0L}, {0.0L, 0.0L}, {0.0L, 0.0L}, {INV_SQRT_2, INV_SQRT_2}};
const Operator T_OPERATOR = {.num_qubits = 1, .size = 2, .elements = T_elements};

static Complex S_elements[4] = {{1.0L, 0.0L}, {0.0L, 0.0L}, {0.0L, 0.0L}, {0.0L, 1.0L}};
const Operator S_OPERATOR = {.num_qubits = 1, .size = 2, .elements = S_elements};

static Complex H_elements[4] = {
    {INV_SQRT_2, 0.0L}, {INV_SQRT_2, 0.0L}, {INV_SQRT_2, 0.0L}, {-INV_SQRT_2, 0.0L}};
const Operator H_OPERATOR = {.num_qubits = 1, .size = 2, .elements = H_elements};

static Complex CX_elements[16] = {{1.0L, 0.0L}, {0.0L, 0.0L}, {0.0L, 0.0L}, {0.0L, 0.0L},
                                  {0.0L, 0.0L}, {1.0L, 0.0L}, {0.0L, 0.0L}, {0.0L, 0.0L},
                                  {0.0L, 0.0L}, {0.0L, 0.0L}, {0.0L, 0.0L}, {1.0L, 0.0L},
                                  {0.0L, 0.0L}, {0.0L, 0.0L}, {1.0L, 0.0L}, {0.0L, 0.0L}};
const Operator CX_OPERATOR = {.num_qubits = 2, .size = 4, .elements = CX_elements};

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
    result.amplitudes = malloc(sizeof(Complex) * result.size);

    if (result.amplitudes == NULL) {
        fprintf(stderr, "Error: failed to allocate memory.\n");
        return result;
    }

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

    if (result.elements == NULL) {
        fprintf(stderr, "Error: failed to allocate memory.\n");
        return result;
    }

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

static int complex_approx_equal(Complex a, Complex b) {
    return fabsl(a.x - b.x) < EPSILON && fabsl(a.y - b.y) < EPSILON;
}

int operator_is_hermitian(Operator A) {
    for (size_t i = 0; i < A.size; i++) {
        for (size_t j = 0; j < A.size; j++) {
            if (!complex_approx_equal(A.elements[A.size * i + j],
                                      complex_conjugate(A.elements[A.size * j + i])))
                return 0;
        }
    }

    return 1;
}

Operator operators_tensor(Operator A, Operator B) {
    Operator tensor_product;
    tensor_product.num_qubits = A.num_qubits + B.num_qubits;
    tensor_product.size = A.size * B.size;
    tensor_product.elements = malloc(sizeof(Complex) * tensor_product.size * tensor_product.size);
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

int operator_is_unitary(Operator A) {
    Operator adjoint = operator_adjoint(A);

    if (adjoint.elements == NULL)
        return 0;

    Operator product = operators_multiply(A, adjoint);
    free(adjoint.elements);

    if (product.elements == NULL)
        return 0;

    int is_unitary = 1;
    for (size_t i = 0; i < product.size; i++) {
        for (size_t j = 0; j < product.size; j++) {
            if (i == j) {
                if (!complex_approx_equal(product.elements[product.size * i + j],
                                          (Complex){1.0L, 0.0L})) {
                    is_unitary = 0;
                    break;
                }
            } else {
                if (!complex_approx_equal(product.elements[product.size * i + j],
                                          (Complex){0.0L, 0.0L})) {
                    is_unitary = 0;
                    break;
                }
            }
        }
        if (!is_unitary)
            break;
    }

    free(product.elements);
    return is_unitary;
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