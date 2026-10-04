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
    if (norm_val == 1.0L)
        return;
    Complex mul_factor = {1.0L / norm_val, 0.0L};
    a->amplitudes[0] = complex_multiply(a->amplitudes[0], mul_factor);
    a->amplitudes[1] = complex_multiply(a->amplitudes[1], mul_factor);
}

long double polar_angle_of_qubit(Qubit a) {
    return 2 * acosl(complex_magnitude(a.amplitudes[0]));
}

long double azimuthal_angle_of_qubit(Qubit a) {
    if ((a.amplitudes[1].x == 0 && a.amplitudes[1].y == 0) ||
        (a.amplitudes[0].x == 0 && a.amplitudes[0].y == 0))
        return NAN;

    long double angle = complex_argument(a.amplitudes[1]) - complex_argument(a.amplitudes[0]);

    if (angle < 0)
        angle += 2 * acosl(-1.0L);

    return angle;
}

void ignore_phase_factor_in_qubit(Qubit* a) {
    long double diff = complex_argument(a->amplitudes[1]) - complex_argument(a->amplitudes[0]);
    a->amplitudes[0].x = complex_magnitude(a->amplitudes[0]);
    a->amplitudes[0].y = 0;
    long double b_magnitude = complex_magnitude(a->amplitudes[1]);
    a->amplitudes[1].x = b_magnitude * cosl(diff);
    a->amplitudes[1].y = b_magnitude * sinl(diff);
}

void qubit_print(Qubit a) {
    printf("--- Qubit State ---\n");
    printf("|0> : ");
    complex_print(a.amplitudes[0]);
    printf("|1> : ");
    complex_print(a.amplitudes[1]);
    printf("\n");
}