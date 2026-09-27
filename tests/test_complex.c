#include <math.h>
#include <stdio.h>

#include "complex.h"

#define EPSILON 1e-12L

static int complex_approx_equal(Complex a, Complex b) {
    return fabsl(a.x - b.x) < EPSILON && fabsl(a.y - b.y) < EPSILON;
}

static int test_add(void) {

    Complex z1 = {3, 4};
    Complex z2 = {5, 8};

    Complex expected = {8, 12};
    Complex actual = complex_add(z1, z2);

    if (complex_approx_equal(actual, expected)) {
        printf("PASS: complex_add\n");
        return 0;
    } else {
        printf("FAIL: complex_add\n");
        printf("Expected: ");
        complex_print(expected);
        printf("Actual:   ");
        complex_print(actual);
        return 1;
    }
}

static int test_subtract(void) {

    Complex z1 = {3, 4};
    Complex z2 = {5, 8};

    Complex expected = {-2, -4};
    Complex actual = complex_subtract(z1, z2);

    if (complex_approx_equal(actual, expected)) {
        printf("PASS: complex_subtract\n");
        return 0;
    } else {
        printf("FAIL: complex_subtract\n");
        printf("Expected: ");
        complex_print(expected);
        printf("Actual:   ");
        complex_print(actual);
        return 1;
    }
}

static int test_multiply(void) {

    Complex z1 = {3, 4};
    Complex z2 = {5, 8};

    Complex expected = {-17, 44};
    Complex actual = complex_multiply(z1, z2);

    if (complex_approx_equal(actual, expected)) {
        printf("PASS: complex_multiply\n");
        return 0;
    } else {
        printf("FAIL: complex_multiply\n");
        printf("Expected: ");
        complex_print(expected);
        printf("Actual:   ");
        complex_print(actual);
        return 1;
    }
}

static int test_conjugate(void) {

    Complex z = {3, 4};

    Complex expected = {3, -4};
    Complex actual = complex_conjugate(z);

    if (complex_approx_equal(actual, expected)) {
        printf("PASS: complex_conjugate\n");
        return 0;
    } else {
        printf("FAIL: complex_conjugate\n");
        printf("Expected: ");
        complex_print(expected);
        printf("Actual:   ");
        complex_print(actual);
        return 1;
    }
}

static int test_magnitude(void) {

    Complex z = {3, 4};

    long double expected = 5.0L;
    long double actual = complex_magnitude(z);

    if (fabsl(actual - expected) < EPSILON) {
        printf("PASS: complex_magnitude\n");
        return 0;
    } else {
        printf("FAIL: complex_magnitude\n");
        printf("Expected: %Lf\n", expected);
        printf("Actual:   %Lf\n", actual);
        return 1;
    }
}

int main(void) {

    printf("----- TESTING COMPLEX NUMBERS -----\n\n");
    int failures = test_add();
    failures += test_subtract();
    failures += test_multiply();
    failures += test_conjugate();
    failures += test_magnitude();

    if (failures == 0) {
        printf("\nAll complex tests passed.\n");
    } else {
        printf("\n%d test(s) failed.\n", failures);
    }

    return failures;
}