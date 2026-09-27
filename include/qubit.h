#ifndef QUBIT_H
#define QUBIT_H

#include "complex.h"

/**
 * @brief Stores the probability ampltiudes of a qubit state corresponding to computational basis
 * states
 */
typedef struct {
    Complex amplitudes[2];
} Qubit;

/**
 * Computational basis state |0>.
 */
extern const Qubit QUBIT_ZERO;

/**
 * Computational basis state |1>.
 */
extern const Qubit QUBIT_ONE;

/**
 * Computes the inner product <a|b> of two qubit states.
 *
 * @param a First qubit state (bra).
 * @param b Second qubit state (ket).
 * @return The complex inner product <a|b>.
 */
Complex qubit_inner_product(Qubit a, Qubit b);

/**
 * Computes the norm of the qubit state which is qubit state's inner product with itself.
 *
 * @param a A qubit state
 * @return The norm of the qubit state
 */
long double qubit_norm(Qubit a);

/**
 * Computes the square of the probability amplitude corresponding to the zero state for the given
 * normalized qubit state.
 *
 * @param norm_a A nomralized qubit state
 * @return The square of probability amplitude corresponding to the zero state.
 */
long double probability_zero(Qubit norm_a);

/**
 * Computes the square of the probability amplitude corresponding to the one state for the given
 * normalized qubit state.
 *
 * @param norm_a A normalized qubit state
 * @return The square of probability amplitude corresponding to the one state.
 */
long double probability_one(Qubit norm_a);

/**
 * Normalizes the given qubit state in-place.
 *
 * @param a A qubit state
 */
void qubit_normalize(Qubit* a);

/**
 * Print a qubit state to the standard output.
 *
 * @param a A qubit state
 */
void qubit_print(Qubit a);
#endif