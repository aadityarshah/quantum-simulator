#include "qubit.h"
#include <math.h>
#include <stdio.h>

const Qubit QUBIT_ZERO = {{{1.0L, 0.0L}, {0.0L, 0.0L}}};
const Qubit QUBIT_ONE = {{{0.0L, 0.0L}, {1.0L, 0.0L}}};

Complex qubit_inner_product(Qubit a, Qubit b) {
    return complex_add(complex_multiply(complex_conjugate(a.amplitudes[0]), b.amplitudes[0]),
                       complex_multiply(complex_conjugate(a.amplitudes[1]), b.amplitudes[1]));
}

long double qubit_norm(Qubit a) {
    long double alpha = complex_magnitude(a.amplitudes[0]);
    long double beta = complex_magnitude(a.amplitudes[1]);
    return sqrtl(alpha * alpha + beta * beta);
}

long double probability_zero(Qubit normalized_a) {
    long double alpha = complex_magnitude(normalized_a.amplitudes[0]);
    return alpha * alpha;
}

long double probability_one(Qubit normalized_a) {
    long double beta = complex_magnitude(normalized_a.amplitudes[1]);
    return beta * beta;
}

void qubit_normalize(Qubit* a) {
    long double norm_val = qubit_norm(*a);
    if (norm_val == 0.0L) {
        fprintf(stderr, "Error: zero qubit cannot be normalized.\n");
        return;
    }
    Complex mul_factor = {1.0L / norm_val, 0.0L};
    a->amplitudes[0] = complex_multiply(a->amplitudes[0], mul_factor);
    a->amplitudes[1] = complex_multiply(a->amplitudes[1], mul_factor);
}

void qubit_print(Qubit a) {
    printf("--- Qubit State ---\n");
    printf("|0> : ");
    complex_print(a.amplitudes[0]);
    printf("|1> : ");
    complex_print(a.amplitudes[1]);
    printf("\n");
}