#include <math.h>
#include <stdio.h>

#include "qubit.h"

#define EPSILON 1e-12L

static int approx_equal(long double a, long double b) {
    return fabsl(a - b) < EPSILON;
}

static int complex_approx_equal(Complex a, Complex b) {
    return fabsl(a.x - b.x) < EPSILON && fabsl(a.y - b.y) < EPSILON;
}

static int test_inner_product(void) {
    int failures = 0;

    Complex expected_zero_zero = {1.0L, 0.0L};
    Complex expected_zero_one = {0.0L, 0.0L};
    Complex expected_one_zero = {0.0L, 0.0L};
    Complex expected_one_one = {1.0L, 0.0L};

    Complex zero_zero = qubit_inner_product(QUBIT_ZERO, QUBIT_ZERO);
    Complex zero_one = qubit_inner_product(QUBIT_ZERO, QUBIT_ONE);
    Complex one_zero = qubit_inner_product(QUBIT_ONE, QUBIT_ZERO);
    Complex one_one = qubit_inner_product(QUBIT_ONE, QUBIT_ONE);

    if (!complex_approx_equal(zero_zero, expected_zero_zero)) {
        failures++;
        printf("FAIL %d: qubit_inner_product\n", failures);
        printf("Expected: ");
        complex_print(expected_zero_zero);
        printf("Actual: ");
        complex_print(zero_zero);
    }

    if (!complex_approx_equal(zero_one, expected_zero_one)) {
        failures++;
        printf("FAIL %d: qubit_inner_product\n", failures);
        printf("Expected: ");
        complex_print(expected_zero_one);
        printf("Actual: ");
        complex_print(zero_one);
    }

    if (!complex_approx_equal(one_zero, expected_one_zero)) {
        failures++;
        printf("FAIL %d: qubit_inner_product\n", failures);
        printf("Expected: ");
        complex_print(expected_one_zero);
        printf("Actual: ");
        complex_print(one_zero);
    }

    if (!complex_approx_equal(one_one, expected_one_one)) {
        failures++;
        printf("FAIL %d: qubit_inner_product\n", failures);
        printf("Expected: ");
        complex_print(expected_one_one);
        printf("Actual: ");
        complex_print(one_one);
    }

    if (failures == 0) {
        printf("PASS: qubit_inner_product\n");
    }
    return failures;
}

static int test_norm(void) {
    int failures = 0;

    Qubit a = {{{3.0L, 0.0L}, {4.0L, 0.0L}}};

    long double qubit_norm_a = qubit_norm(a);
    long double qubit_norm_zero = qubit_norm(QUBIT_ZERO);
    long double qubit_norm_one = qubit_norm(QUBIT_ONE);

    if (!approx_equal(qubit_norm_a, 5.0L)) {
        failures++;
        printf("FAIL %d: qubit_norm\n", failures);
        printf("Expected: %Lf\n", 5.0L);
        printf("Actual: %Lf\n", qubit_norm_a);
    }

    if (!approx_equal(qubit_norm_zero, 1.0L)) {
        failures++;
        printf("FAIL %d: qubit_norm\n", failures);
        printf("Expected: %Lf\n", 1.0L);
        printf("Actual: %Lf\n", qubit_norm_zero);
    }

    if (!approx_equal(qubit_norm_one, 1.0L)) {
        failures++;
        printf("FAIL %d: qubit_norm\n", failures);
        printf("Expected: %Lf\n", 1.0L);
        printf("Actual: %Lf\n", qubit_norm_one);
    }

    if (failures == 0) {
        printf("PASS: qubit_norm\n");
    }
    return failures;
}

static int test_normalize(void) {
    int failures = 0;

    Qubit a = {{{3.0L, 0.0L}, {4.0L, 0.0L}}};

    qubit_normalize(&a);

    if (!approx_equal(qubit_norm(a), 1.0L)) {
        failures++;
        printf("FAIL %d: qubit_normalize | qubit_norm\n", failures);
        printf("Expected: %Lf\n", 1.0L);
        printf("Actual: %Lf\n", qubit_norm(a));
    }

    if (!complex_approx_equal(a.amplitudes[0], (Complex){3.0L / 5.0L, 0.0L})) {
        failures++;
        printf("FAIL %d: qubit_normalize\n", failures);
        printf("Expected: ");
        complex_print((Complex){3.0L / 5.0L, 0.0L});
        printf("Actual: ");
        complex_print(a.amplitudes[0]);
    }

    if (!complex_approx_equal(a.amplitudes[1], (Complex){4.0L / 5.0L, 0.0L})) {
        failures++;
        printf("FAIL %d: qubit_normalize\n", failures);
        printf("Expected: ");
        complex_print((Complex){4.0L / 5.0L, 0.0L});
        printf("Actual: ");
        complex_print(a.amplitudes[1]);
    }

    if (failures == 0) {
        printf("PASS: qubit_normalize\n");
    }
    return failures;
}

static int test_probabilities(void) {
    int failures = 0;

    Qubit a = {{{3.0L / 5.0L, 0.0L}, {4.0L / 5.0L, 0.0L}}};

    long double probability_zero_a = probability_zero(a);
    long double probability_one_a = probability_one(a);

    if (!approx_equal(probability_zero_a, 9.0L / 25.0L)) {
        failures++;
        printf("FAIL %d: probability_zero\n", failures);
        printf("Expected: %Lf\n", 9.0L / 25.0L);
        printf("Actual: %Lf\n", probability_zero_a);
    }

    if (!approx_equal(probability_one_a, 16.0L / 25.0L)) {
        failures++;
        printf("FAIL %d: probability_one\n", failures);
        printf("Expected: %Lf\n", 16.0L / 25.0L);
        printf("Actual: %Lf\n", probability_one_a);
    }

    if (!approx_equal(probability_zero_a + probability_one_a, 1.0L)) {
        failures++;
        printf("FAIL %d: probability normalization\n", failures);
        printf("Expected: %Lf\n", 1.0L);
        printf("Actual: %Lf\n", probability_one_a + probability_zero_a);
    }

    if (failures == 0) {
        printf("PASS: probability_zero | probability_one\n");
    }

    return failures;
}

static int test_complex_state(void) {
    int failures = 0;

    long double inverse_sqrt_two = 1.0L / sqrtl(2.0L);

    Qubit a = {{{1.0L, 0.0L}, {0.0L, 1.0L}}};

    qubit_normalize(&a);

    if (!approx_equal(qubit_norm(a), 1.0L)) {
        failures++;
        printf("FAIL %d: complex state normalization\n", failures);
        printf("Expected: %Lf\n", 1.0L);
        printf("Actual: %Lf\n", qubit_norm(a));
    }

    Complex expected_alpha = {inverse_sqrt_two, 0.0L};
    Complex expected_beta = {0.0L, inverse_sqrt_two};

    if (!complex_approx_equal(a.amplitudes[0], expected_alpha)) {
        failures++;
        printf("FAIL %d: complex state alpha\n", failures);
        printf("Expected: ");
        complex_print(expected_alpha);
        printf("Actual: ");
        complex_print(a.amplitudes[0]);
    }

    if (!complex_approx_equal(a.amplitudes[1], expected_beta)) {
        failures++;
        printf("FAIL %d: complex state beta\n", failures);
        printf("Expected: ");
        complex_print(expected_beta);
        printf("Actual: ");
        complex_print(a.amplitudes[1]);
    }

    if (!approx_equal(probability_zero(a), 0.5L)) {
        failures++;
        printf("FAIL %d: complex state probability_zero\n", failures);
        printf("Expected: %Lf\n", 0.5L);
        printf("Actual: %Lf\n", probability_zero(a));
    }

    if (!approx_equal(probability_one(a), 0.5L)) {
        failures++;
        printf("FAIL %d: complex state probability_one\n", failures);
        printf("Expected: %Lf\n", 0.5L);
        printf("Actual: %Lf\n", probability_one(a));
    }

    Complex inner_product = qubit_inner_product(a, a);

    if (!complex_approx_equal(inner_product, (Complex){1.0L, 0.0L})) {
        failures++;
        printf("FAIL %d: complex state inner product\n", failures);
        printf("Expected: ");
        complex_print((Complex){1.0L, 0.0L});
        printf("Actual: ");
        complex_print(inner_product);
    }

    if (failures == 0) {
        printf("PASS: complex qubit state\n");
    }

    return failures;
}

int main(void) {

    printf("----- TESTING QUBITS -----\n\n");

    int failures = 0;

    failures += test_inner_product();
    failures += test_norm();
    failures += test_normalize();
    failures += test_probabilities();
    failures += test_complex_state();

    if (failures == 0) {
        printf("\nAll qubit tests passed.\n");
        return 0;
    }

    printf("\n%d qubit test(s) failed.\n", failures);
    return 1;
}