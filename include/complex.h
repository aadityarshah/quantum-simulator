#ifndef COMPLEX_H
#define COMPLEX_H

/**
 * @brief Stores the real and imaginary part of a complex number
 */
typedef struct {
    long double x;
    long double y;
} Complex;

/**
 * Adds two complex numbers.
 *
 * @param a First complex number.
 * @param b Second complex number.
 * @return The sum of a and b.
 */
Complex complex_add(Complex a, Complex b);

/**
 * Multiplies two complex numbers.
 *
 * @param a First complex number.
 * @param b Second complex number.
 * @return The product of a and b.
 */
Complex complex_multiply(Complex a, Complex b);

/**
 * Subtracts two complex numbers.
 *
 * @param a First complex number.
 * @param b Second complex number.
 * @return The difference of a and b.
 */
Complex complex_subtract(Complex a, Complex b);

/**
 * Conjugates a complex number.
 *
 * @param a A complex number.
 * @return Complex conjugate of a.
 */
Complex complex_conjugate(Complex a);

/**
 * Computes the magnitude of a complex number.
 *
 * @param a A complex number.
 * @return The magnitude of a.
 */
long double complex_magnitude(Complex a);

/**
 * Computes the argument of a complex number in [0, 2PI)
 *
 * @param a A complex number.
 * @return The argument of a
 */
long double complex_argument(Complex a);

/**
 * Print a complex number to standard output.
 *
 * @param a A complex number.
 */
void complex_print(Complex a);

#endif