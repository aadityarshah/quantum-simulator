#include <math.h>
#include <stdio.h>

#include "qubit.h"

#define EPSILON 1e-12L
#define PI 3.14159265358979323846

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

    Qubit zero = {{{0.0L, 0.0L}, {0.0L, 0.0L}}};

    qubit_normalize(&zero);

    if (!complex_approx_equal(zero.amplitudes[0], (Complex){0.0L, 0.0L}) ||
        !complex_approx_equal(zero.amplitudes[1], (Complex){0.0L, 0.0L})) {
        failures++;
        printf("FAIL %d: qubit_normalize | zero qubit\n", failures);
        printf("Expected: zero qubit unchanged\n");
        printf("Actual: ");
        qubit_print(zero);
    }

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

static int test_angular_parameters_of_qubit(void) {

    int failures = 0;

    long double inverse_sqrt_two = 1.0L / sqrtl(2.0L);

    Qubit plus = {{{inverse_sqrt_two, 0.0L}, {inverse_sqrt_two, 0.0L}}};
    Qubit plus_i = {{{inverse_sqrt_two, 0.0L}, {0.0L, inverse_sqrt_two}}};
    Qubit minus = {{{inverse_sqrt_two, 0.0L}, {-inverse_sqrt_two, 0.0L}}};
    Qubit minus_i = {{{inverse_sqrt_two, 0.0L}, {0.0L, -inverse_sqrt_two}}};
    Qubit arbitrary = {
        {{sqrtl(3.0L) / 2.0L, 0.0L}, {1.0L / (2.0L * sqrtl(2.0L)), 1.0L / (2.0L * sqrtl(2.0L))}}};

    long double expected_polar_angle_zero = 0.0L;
    long double expected_polar_angle_one = PI;
    long double expected_polar_angle_equator = PI / 2.0L;

    long double expected_azimuthal_angle_plus = 0.0L;
    long double expected_azimuthal_angle_plus_i = PI / 2.0L;
    long double expected_azimuthal_angle_minus = PI;
    long double expected_azimuthal_angle_minus_i = 3.0L * PI / 2.0L;

    long double actual_polar_angle_zero = polar_angle_of_qubit(QUBIT_ZERO);
    long double actual_polar_angle_one = polar_angle_of_qubit(QUBIT_ONE);
    long double actual_polar_angle_plus = polar_angle_of_qubit(plus);
    long double actual_polar_angle_plus_i = polar_angle_of_qubit(plus_i);

    long double actual_azimuthal_angle_zero = azimuthal_angle_of_qubit(QUBIT_ZERO);
    long double actual_azimuthal_angle_one = azimuthal_angle_of_qubit(QUBIT_ONE);
    long double actual_azimuthal_angle_plus = azimuthal_angle_of_qubit(plus);
    long double actual_azimuthal_angle_plus_i = azimuthal_angle_of_qubit(plus_i);
    long double actual_azimuthal_angle_minus = azimuthal_angle_of_qubit(minus);
    long double actual_azimuthal_angle_minus_i = azimuthal_angle_of_qubit(minus_i);

    long double actual_polar_angle_arbitrary = polar_angle_of_qubit(arbitrary);
    long double actual_azimuthal_angle_arbitrary = azimuthal_angle_of_qubit(arbitrary);

    if (!approx_equal(actual_polar_angle_zero, expected_polar_angle_zero)) {
        failures++;
        printf("FAIL %d: polar_angle_of_qubit | QUBIT_ZERO\n", failures);
        printf("Expected: %Lf\n", expected_polar_angle_zero);
        printf("Actual: %Lf\n", actual_polar_angle_zero);
    }

    if (!approx_equal(actual_polar_angle_one, expected_polar_angle_one)) {
        failures++;
        printf("FAIL %d: polar_angle_of_qubit | QUBIT_ONE\n", failures);
        printf("Expected: %Lf\n", expected_polar_angle_one);
        printf("Actual: %Lf\n", actual_polar_angle_one);
    }

    if (!approx_equal(actual_polar_angle_plus, expected_polar_angle_equator)) {
        failures++;
        printf("FAIL %d: polar_angle_of_qubit | |+>\n", failures);
        printf("Expected: %Lf\n", expected_polar_angle_equator);
        printf("Actual: %Lf\n", actual_polar_angle_plus);
    }

    if (!approx_equal(actual_polar_angle_plus_i, expected_polar_angle_equator)) {
        failures++;
        printf("FAIL %d: polar_angle_of_qubit | |+i>\n", failures);
        printf("Expected: %Lf\n", expected_polar_angle_equator);
        printf("Actual: %Lf\n", actual_polar_angle_plus_i);
    }

    if (!isnan(actual_azimuthal_angle_zero)) {
        failures++;
        printf("FAIL %d: azimuthal_angle_of_qubit | QUBIT_ZERO\n", failures);
        printf("Expected: NAN\n");
        printf("Actual: %Lf\n", actual_azimuthal_angle_zero);
    }

    if (!isnan(actual_azimuthal_angle_one)) {
        failures++;
        printf("FAIL %d: azimuthal_angle_of_qubit | QUBIT_ONE\n", failures);
        printf("Expected: NAN\n");
        printf("Actual: %Lf\n", actual_azimuthal_angle_one);
    }

    if (!approx_equal(actual_azimuthal_angle_plus, expected_azimuthal_angle_plus)) {
        failures++;
        printf("FAIL %d: azimuthal_angle_of_qubit | |+>\n", failures);
        printf("Expected: %Lf\n", expected_azimuthal_angle_plus);
        printf("Actual: %Lf\n", actual_azimuthal_angle_plus);
    }

    if (!approx_equal(actual_azimuthal_angle_plus_i, expected_azimuthal_angle_plus_i)) {
        failures++;
        printf("FAIL %d: azimuthal_angle_of_qubit | |+i>\n", failures);
        printf("Expected: %Lf\n", expected_azimuthal_angle_plus_i);
        printf("Actual: %Lf\n", actual_azimuthal_angle_plus_i);
    }

    if (!approx_equal(actual_azimuthal_angle_minus, expected_azimuthal_angle_minus)) {
        failures++;
        printf("FAIL %d: azimuthal_angle_of_qubit | |->\n", failures);
        printf("Expected: %Lf\n", expected_azimuthal_angle_minus);
        printf("Actual: %Lf\n", actual_azimuthal_angle_minus);
    }

    if (!approx_equal(actual_azimuthal_angle_minus_i, expected_azimuthal_angle_minus_i)) {
        failures++;
        printf("FAIL %d: azimuthal_angle_of_qubit | |-i>\n", failures);
        printf("Expected: %Lf\n", expected_azimuthal_angle_minus_i);
        printf("Actual: %Lf\n", actual_azimuthal_angle_minus_i);
    }

    if (!approx_equal(actual_polar_angle_arbitrary, PI / 3.0L)) {
        failures++;
        printf("FAIL %d: polar_angle_of_qubit | arbitrary state\n", failures);
        printf("Expected: %Lf\n", PI / 3.0L);
        printf("Actual: %Lf\n", actual_polar_angle_arbitrary);
    }

    if (!approx_equal(actual_azimuthal_angle_arbitrary, PI / 4.0L)) {
        failures++;
        printf("FAIL %d: azimuthal_angle_of_qubit | arbitrary state\n", failures);
        printf("Expected: %Lf\n", PI / 4.0L);
        printf("Actual: %Lf\n", actual_azimuthal_angle_arbitrary);
    }

    if (failures == 0) {
        printf("PASS: polar_angle_of_qubit | azimuthal_angle_of_qubit\n");
    }

    return failures;
}

static int test_ignore_phase_factor(void) {

    int failures = 0;

    long double inverse_sqrt_two = 1.0L / sqrtl(2.0L);

    Qubit a = {{{0.0L, inverse_sqrt_two}, {inverse_sqrt_two, 0.0L}}};

    ignore_phase_factor_in_qubit(&a);

    Complex expected_alpha = {inverse_sqrt_two, 0.0L};
    Complex expected_beta = {0.0L, -inverse_sqrt_two};

    if (!complex_approx_equal(a.amplitudes[0], expected_alpha)) {
        failures++;
        printf("FAIL %d: ignore_phase_factor_in_qubit | alpha\n", failures);
        printf("Expected: ");
        complex_print(expected_alpha);
        printf("Actual: ");
        complex_print(a.amplitudes[0]);
    }

    if (!complex_approx_equal(a.amplitudes[1], expected_beta)) {
        failures++;
        printf("FAIL %d: ignore_phase_factor_in_qubit | beta\n", failures);
        printf("Expected: ");
        complex_print(expected_beta);
        printf("Actual: ");
        complex_print(a.amplitudes[1]);
    }

    if (failures == 0) {
        printf("PASS: ignore_phase_factor_in_qubit\n");
    }

    return failures;
}

static int test_complex_state(void) {
    int failures = 0;

    long double inverse_sqrt_two = 1.0L / sqrtl(2.0L);

    Qubit a = {{{1.0L, 0.0L}, {0.0L, 1.0L}}};

    qubit_normalize(&a);
    ignore_phase_factor_in_qubit(&a);

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

    long double expected_polar_angle = PI / 2.0L;
    long double expected_azimuthal_angle = PI / 2.0L;

    long double actual_polar_angle = polar_angle_of_qubit(a);
    long double actual_azimuthal_angle = azimuthal_angle_of_qubit(a);

    if (!approx_equal(actual_polar_angle, expected_polar_angle)) {
        failures++;
        printf("FAIL %d: complex state polar angle\n", failures);
        printf("Expected: %Lf\n", expected_polar_angle);
        printf("Actual: %Lf\n", actual_polar_angle);
    }

    if (!approx_equal(actual_azimuthal_angle, expected_azimuthal_angle)) {
        failures++;
        printf("FAIL %d: complex state azimuthal angle\n", failures);
        printf("Expected: %Lf\n", expected_azimuthal_angle);
        printf("Actual: %Lf\n", actual_azimuthal_angle);
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
    failures += test_angular_parameters_of_qubit();
    failures += test_ignore_phase_factor();
    failures += test_complex_state();

    if (failures == 0) {
        printf("\nAll qubit tests passed.\n");
        return 0;
    }

    printf("\n%d qubit test(s) failed.\n", failures);
    return 1;
}