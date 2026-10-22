#include <math.h>
#include <stdio.h>

#include "quantum_state.h"

#define EPSILON 1e-12L

static int approx_equal(long double a, long double b) {
    return fabsl(a - b) < EPSILON;
}

static int complex_approx_equal(Complex a, Complex b) {
    return fabsl(a.x - b.x) < EPSILON && fabsl(a.y - b.y) < EPSILON;
}

static int test_phase_factor_multiplication(void) {
    int failures = 0;

    QuantumState iota_zero_state = quantum_state_multiply_phase(ZERO_STATE, (Complex){0.0L, 1.0L});

    int expected_num_qubits = 1;
    size_t expected_size = 2;

    if (expected_num_qubits != iota_zero_state.num_qubits) {
        failures++;
        printf("FAIL %d: quantum_state_multiply_phase\n", failures);
        printf("Expected: %d\n", expected_num_qubits);
        printf("Actual: %d\n", iota_zero_state.num_qubits);
    }

    if (expected_size != iota_zero_state.size) {
        failures++;
        printf("FAIL %d: quantum_state_multiply_phase\n", failures);
        printf("Expected: %zu\n", expected_size);
        printf("Actual: %zu\n", iota_zero_state.size);
    }

    Complex expected_amplitudes[2] = {{0.0L, 1.0L}, {0.0L, 0.0L}};

    for (size_t i = 0; i < iota_zero_state.size; i++) {
        if (!complex_approx_equal(expected_amplitudes[i], iota_zero_state.amplitudes[i])) {
            failures++;
            printf("FAIL %d: quantum_state_multiply_phase\n", failures);
            printf("Expected: ");
            complex_print(expected_amplitudes[i]);
            printf("Actual: ");
            complex_print(iota_zero_state.amplitudes[i]);
        }
    }

    if (failures == 0) {
        printf("PASS: quantum_state_multiply_phase\n");
    }

    return failures;
}

static int test_norm(void) {
    int failures = 0;

    Complex amplitudes[] = {{3.0, 0.0L}, {4.0L, 0.0L}};
    QuantumState a = {.num_qubits = 1, .size = 2, .amplitudes = amplitudes};

    long double quantum_state_norm_a = quantum_state_norm(a);
    long double quantum_state_norm_zero = quantum_state_norm(ZERO_STATE);
    long double quantum_state_norm_one = quantum_state_norm(ONE_STATE);

    if (!approx_equal(quantum_state_norm_a, 5.0L)) {
        failures++;
        printf("FAIL %d: quantum_state_norm\n", failures);
        printf("Expected: %Lf\n", 5.0L);
        printf("Actual: %Lf\n", quantum_state_norm_a);
    }

    if (!approx_equal(quantum_state_norm_zero, 1.0L)) {
        failures++;
        printf("FAIL %d: quantum_state_norm\n", failures);
        printf("Expected: %Lf\n", 1.0L);
        printf("Actual: %Lf\n", quantum_state_norm_zero);
    }

    if (!approx_equal(quantum_state_norm_one, 1.0L)) {
        failures++;
        printf("FAIL %d: quantum_state_norm\n", failures);
        printf("Expected: %Lf\n", 1.0L);
        printf("Actual: %Lf\n", quantum_state_norm_one);
    }

    if (failures == 0) {
        printf("PASS: quantum_state_norm\n");
    }
    return failures;
}

static int test_inner_product(void) {
    int failures = 0;

    Complex expected_zero_zero = {1.0L, 0.0L};
    Complex expected_zero_one = {0.0L, 0.0L};
    Complex expected_one_zero = {0.0L, 0.0L};
    Complex expected_one_one = {1.0L, 0.0L};

    Complex zero_zero = quantum_states_inner_product(ZERO_STATE, ZERO_STATE);
    Complex zero_one = quantum_states_inner_product(ZERO_STATE, ONE_STATE);
    Complex one_zero = quantum_states_inner_product(ONE_STATE, ZERO_STATE);
    Complex one_one = quantum_states_inner_product(ONE_STATE, ONE_STATE);

    if (!complex_approx_equal(zero_zero, expected_zero_zero)) {
        failures++;
        printf("FAIL %d: quantum_state_inner_product\n", failures);
        printf("Expected: ");
        complex_print(expected_zero_zero);
        printf("Actual: ");
        complex_print(zero_zero);
    }

    if (!complex_approx_equal(zero_one, expected_zero_one)) {
        failures++;
        printf("FAIL %d: quantum_state_inner_product\n", failures);
        printf("Expected: ");
        complex_print(expected_zero_one);
        printf("Actual: ");
        complex_print(zero_one);
    }

    if (!complex_approx_equal(one_zero, expected_one_zero)) {
        failures++;
        printf("FAIL %d: quantum_state_inner_product\n", failures);
        printf("Expected: ");
        complex_print(expected_one_zero);
        printf("Actual: ");
        complex_print(one_zero);
    }

    if (!complex_approx_equal(one_one, expected_one_one)) {
        failures++;
        printf("FAIL %d: quantum_state_inner_product\n", failures);
        printf("Expected: ");
        complex_print(expected_one_one);
        printf("Actual: ");
        complex_print(one_one);
    }

    if (failures == 0) {
        printf("PASS: quantum_state_inner_product\n");
    }
    return failures;
}

static int test_normalize(void) {
    int failures = 0;

    Complex amplitudes[] = {{3.0, 0.0L}, {4.0L, 0.0L}};
    QuantumState a = {.num_qubits = 1, .size = 2, .amplitudes = amplitudes};

    quantum_state_normalize(&a);

    if (!approx_equal(quantum_state_norm(a), 1.0L)) {
        failures++;
        printf("FAIL %d: quantum_state_normalize | quantum_state_norm\n", failures);
        printf("Expected: %Lf\n", 1.0L);
        printf("Actual: %Lf\n", quantum_state_norm(a));
    }

    if (!complex_approx_equal(a.amplitudes[0], (Complex){3.0L / 5.0L, 0.0L})) {
        failures++;
        printf("FAIL %d: quantum_state_nomalize\n", failures);
        printf("Expected: ");
        complex_print((Complex){3.0L / 5.0L, 0.0L});
        printf("Actual: ");
        complex_print(a.amplitudes[0]);
    }

    if (!complex_approx_equal(a.amplitudes[1], (Complex){4.0L / 5.0L, 0.0L})) {
        failures++;
        printf("FAIL %d: quantum_state_normalize\n", failures);
        printf("Expected: ");
        complex_print((Complex){4.0L / 5.0L, 0.0L});
        printf("Actual: ");
        complex_print(a.amplitudes[1]);
    }

    if (failures == 0) {
        printf("PASS: quantum_state_normalize\n");
    }
    return failures;
}

static int test_tensor() {
    int failures = 0;

    QuantumState tensor = quantum_states_tensor(ZERO_STATE, ONE_STATE);
    int expected_tensor_num_qubits = 2;
    size_t expected_tensor_size = 4;

    if (expected_tensor_num_qubits != tensor.num_qubits) {
        failures++;
        printf("FAIL %d: quantum_states_tensor\n", failures);
        printf("Expected: %d\n", expected_tensor_num_qubits);
        printf("Actual: %d\n", tensor.num_qubits);
    }

    if (expected_tensor_size != tensor.size) {
        failures++;
        printf("FAIL %d: quantum_states_tensor\n", failures);
        printf("Expected: %zu\n", expected_tensor_size);
        printf("Actual: %zu\n", tensor.size);
    }

    Complex expected_tensor_amplitudes[4] = {
        {0.0L, 0.0L}, {1.0L, 0.0L}, {0.0L, 0.0L}, {0.0L, 0.0L}};

    for (size_t i = 0; i < tensor.size; i++) {
        if (!complex_approx_equal(expected_tensor_amplitudes[i], tensor.amplitudes[i])) {
            failures++;
            printf("FAIL %d: quantum_states_tensor\n", failures);
            printf("Expected: ");
            complex_print(expected_tensor_amplitudes[i]);
            printf("Actual: ");
            complex_print(tensor.amplitudes[i]);
        }
    }
    if (failures == 0) {
        printf("PASS: quantum_states_tensor\n");
    }

    return failures;
}

int main(void) {

    printf("----- TESTING QUANTUM STATES -----\n\n");

    int failures = 0;

    failures += test_phase_factor_multiplication();
    failures += test_norm();
    failures += test_inner_product();
    failures += test_normalize();
    failures += test_tensor();

    if (failures == 0) {
        printf("\nAll quantum states tests passed.\n");
        return 0;
    }

    printf("\n%d quantum state test(s) failed.\n", failures);
    return 1;
}