#include <math.h>
#include <stdio.h>

#include "operator.h"

#define EPSILON 1e-12L

static int complex_approx_equal(Complex a, Complex b) {
    return fabsl(a.x - b.x) < EPSILON && fabsl(a.y - b.y) < EPSILON;
}

static int quantum_states_equal(QuantumState a, QuantumState b) {
    if (a.num_qubits != b.num_qubits)
        return 0;
    if (a.size != b.size)
        return 0;
    for (size_t i = 0; i < a.size; i++) {
        if (!complex_approx_equal(a.amplitudes[i], b.amplitudes[i]))
            return 0;
    }
    return 1;
}

static int operators_equal(Operator A, Operator B) {
    if (A.num_qubits != B.num_qubits)
        return 0;
    if (A.size != B.size)
        return 0;
    for (size_t i = 0; i < A.size; i++) {
        for (size_t j = 0; j < A.size; j++) {
            if (!complex_approx_equal(A.elements[A.size * i + j], B.elements[B.size * i + j]))
                return 0;
        }
    }
    return 1;
}

static int test_operator_on_quantum_state(void) {
    int failures = 0;

    if (!quantum_states_equal(ZERO_STATE,
                              operate_on_quantum_state(IDENTITY_OPERATOR, ZERO_STATE))) {
        failures++;
        printf("FAIL %d: operator_on_quantum_state\n", failures);
        printf("Expected: |0>\n");
        printf("Actual: \n");
        quantum_state_print(operate_on_quantum_state(IDENTITY_OPERATOR, ZERO_STATE));
    }

    if (!quantum_states_equal(ONE_STATE, operate_on_quantum_state(X_OPERATOR, ZERO_STATE))) {
        failures++;
        printf("FAIL %d: operator_on_quantum_state\n", failures);
        printf("Expected: |1>\n");
        printf("Actual: \n");
        quantum_state_print(operate_on_quantum_state(X_OPERATOR, ZERO_STATE));
    }

    if (!quantum_states_equal(quantum_state_multiply_phase(ONE_STATE, (Complex){0.0L, 1.0L}),
                              operate_on_quantum_state(Y_OPERATOR, ZERO_STATE))) {
        failures++;
        printf("FAIL %d: operator_on_quantum_state\n", failures);
        printf("Expected: i|1>\n");
        printf("Actual: \n");
        quantum_state_print(operate_on_quantum_state(Y_OPERATOR, ZERO_STATE));
    }

    if (!quantum_states_equal(quantum_state_multiply_phase(ONE_STATE, (Complex){-1.0L, 0.0L}),
                              operate_on_quantum_state(Z_OPERATOR, ONE_STATE))) {
        failures++;
        printf("FAIL %d: operator_on_quantum_state\n", failures);
        printf("Expected: -|1>\n");
        printf("Actual: \n");
        quantum_state_print(operate_on_quantum_state(Y_OPERATOR, ZERO_STATE));
    }

    if (failures == 0) {
        printf("PASS: operate_on_quantum_state\n");
    }
    return failures;
}

static int test_operators_multiply(void) {
    int failures = 0;

    if (!operators_equal(operators_multiply(X_OPERATOR, X_OPERATOR), IDENTITY_OPERATOR)) {
        failures++;
        printf("FAIL %d: operators_multiply | X_OPERATOR times X_OPERATOR\n", failures);
        printf("Expected:\n");
        operator_print(IDENTITY_OPERATOR);
        printf("Actual:\n");
        operator_print(operators_multiply(X_OPERATOR, X_OPERATOR));
    }

    if (!operators_equal(operators_multiply(Y_OPERATOR, Y_OPERATOR), IDENTITY_OPERATOR)) {
        failures++;
        printf("FAIL %d: operators_multiply | Y_OPERATOR times Y_OPERATOR\n", failures);
        printf("Expected:\n");
        operator_print(IDENTITY_OPERATOR);
        printf("Actual:\n");
        operator_print(operators_multiply(Y_OPERATOR, Y_OPERATOR));
    }

    if (!operators_equal(operators_multiply(Z_OPERATOR, Z_OPERATOR), IDENTITY_OPERATOR)) {
        failures++;
        printf("FAIL %d: operators_multiply | Z_OPERATOR times Z_OPERATOR\n", failures);
        printf("Expected:\n");
        operator_print(IDENTITY_OPERATOR);
        printf("Actual:\n");
        operator_print(operators_multiply(Z_OPERATOR, Z_OPERATOR));
    }

    if (failures == 0) {
        printf("PASS: operators_multiply\n");
    }

    return failures;
}

static int test_hermitian_operators(void) {
    int failures = 0;

    if (!operator_is_hermitian(IDENTITY_OPERATOR)) {
        failures++;
        printf("FAIL %d: operator_is_hermitian | IDENTITY_OPERATOR\n", failures);
        printf("Expected: Yes\n");
        printf("Actual: No\n");
    }
    if (!operator_is_hermitian(X_OPERATOR)) {
        failures++;
        printf("FAIL %d: operator_is_hermitian | X_OPERATOR\n", failures);
        printf("Expected: Yes\n");
        printf("Actual: No\n");
    }

    if (!operator_is_hermitian(Y_OPERATOR)) {
        failures++;
        printf("FAIL %d: operator_is_hermitian | Y_OPERATOR\n", failures);
        printf("Expected: Yes\n");
        printf("Actual: No\n");
    }

    if (!operator_is_hermitian(Z_OPERATOR)) {
        failures++;
        printf("FAIL %d: operator_is_hermitian | Z_OPERATOR\n", failures);
        printf("Expected: Yes\n");
        printf("Actual: No\n");
    }

    if (failures == 0) {
        printf("PASS: operator_is_hermitian\n");
    }

    return failures;
}

static int test_operator_adjoint(void) {
    int failures = 0;

    long double inverse_sqrt_two = 1.0L / sqrtl(2.0L);
    Operator operator;
    operator.num_qubits = 1;
    operator.size = 2;
    Complex elements[4] = {{inverse_sqrt_two, 0.0L},
                           {0.0L, inverse_sqrt_two},
                           {0.0L, inverse_sqrt_two},
                           {inverse_sqrt_two, 0.0L}};
    operator.elements = elements;

    Complex expected_elements[4] = {{inverse_sqrt_two, 0.0L},
                                    {0.0L, -inverse_sqrt_two},
                                    {0.0L, -inverse_sqrt_two},
                                    {inverse_sqrt_two, 0.0L}};

    Operator adjoint_operator = operator_adjoint(operator);

    if (operator.num_qubits != adjoint_operator.num_qubits) {
        printf("FAIL %d: operator_adjoint | num_qubits\n", failures);
        printf("Expected: %d\n", operator.num_qubits);
        printf("Actual: %d\n", adjoint_operator.num_qubits);
    }

    if (operator.size != adjoint_operator.size) {
        printf("FAIL %d: operator_adjoint | size\n", failures);
        printf("Expected: %zu\n", operator.size);
        printf("Actual: %zu\n", adjoint_operator.size);
    }

    for (size_t i = 0; i < adjoint_operator.size; i++) {
        for (size_t j = 0; j < adjoint_operator.size; j++) {
            if (!complex_approx_equal(adjoint_operator.elements[adjoint_operator.size * i + j],
                                      expected_elements[operator.size * i + j])) {
                failures++;
                printf("FAIL %d: operator_adjoint | element %zu, %zu\n", failures, i + 1, j + 1);
                printf("Expected: ");
                complex_print(expected_elements[operator.size * i + j]);
                printf("Actual: ");
                complex_print(adjoint_operator.elements[adjoint_operator.size * i + j]);
            }
        }
    }

    if (failures == 0) {
        printf("PASS: operator_adjoint\n");
    }

    return failures;
}

static int test_operator_tensor(void) {
    int failures = 0;

    Operator tensor = operators_tensor(X_OPERATOR, Y_OPERATOR);
    int expected_tensor_num_qubits = 2;
    size_t expected_tensor_size = 4;

    if (expected_tensor_num_qubits != tensor.num_qubits) {
        printf("FAIL %d: operators_tensor | num_qubits\n", failures);
        printf("Expected: %d\n", expected_tensor_num_qubits);
        printf("Actual: %d\n", tensor.num_qubits);
    }

    if (expected_tensor_size != tensor.size) {
        printf("FAIL %d: operators_tensor | size\n", failures);
        printf("Expected: %zu\n", expected_tensor_size);
        printf("Actual: %zu\n", tensor.size);
    }

    Complex expected_tensor_amplitudes[16] = {
        {0.0L, 0.0L}, {0.0L, 0.0L}, {0.0L, 0.0L}, {0.0L, -1.0L}, {0.0L, 0.0L}, {0.0L, 0.0L},
        {0.0L, 1.0L}, {0.0L, 0.0L}, {0.0L, 0.0L}, {0.0L, -1.0L}, {0.0L, 0.0L}, {0.0L, 0.0L},
        {0.0L, 1.0L}, {0.0L, 0.0L}, {0.0L, 0.0L}, {0.0L, 0.0L}};

    for (size_t i = 0; i < tensor.size; i++) {
        for (size_t j = 0; j < tensor.size; j++) {
            if (!complex_approx_equal(tensor.elements[tensor.size * i + j],
                                      expected_tensor_amplitudes[expected_tensor_size * i + j])) {
                failures++;
                printf("FAIL %d: operators_tensor | element %zu, %zu\n", failures, i + 1, j + 1);
                printf("Expected: ");
                complex_print(expected_tensor_amplitudes[expected_tensor_size * i + j]);
                printf("Actual: ");
                complex_print(tensor.elements[tensor.size * i + j]);
            }
        }
    }

    if (failures == 0) {
        printf("PASS: operators_tensor\n");
    }

    return failures;
}

int main(void) {

    printf("----- TESTING OPERATORS -----\n\n");

    int failures = 0;

    failures += test_operator_on_quantum_state();
    failures += test_operators_multiply();
    failures += test_hermitian_operators();
    failures += test_operator_adjoint();
    failures += test_operator_tensor();

    if (failures == 0) {
        printf("\nAll operator tests passed.\n");
        return 0;
    }

    printf("\n%d operator test(s) failed.\n", failures);
    return 1;
}