#include "complex.h"
#include <math.h>
#include <stdio.h>

Complex complex_add(Complex a, Complex b) {
    Complex z;
    z.x = a.x + b.x;
    z.y = a.y + b.y;
    return z;
}

Complex complex_multiply(Complex a, Complex b) {
    Complex z;
    z.x = a.x * b.x - a.y * b.y;
    z.y = a.x * b.y + a.y * b.x;
    return z;
}

Complex complex_subtract(Complex a, Complex b) {
    Complex z;
    z.x = a.x - b.x;
    z.y = a.y - b.y;
    return z;
}

Complex complex_conjugate(Complex a) {
    a.y *= -1;
    return a;
}

long double complex_magnitude(Complex a) {
    return sqrtl(a.x * a.x + a.y * a.y);
}

void complex_print(Complex a) {
    if (a.y < 0) {
        printf("%Lf - %Lfi\n", a.x, -a.y);
    } else {
        printf("%Lf + %Lfi\n", a.x, a.y);
    }
}
