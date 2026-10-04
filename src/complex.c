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

long double complex_argument(Complex a) {
    long double angle = atan2l(a.y, a.x);
    if (angle < 0.0L) {
        angle += 2.0L * acosl(-1.0L);
    }
    return angle;
}

void complex_print(Complex a) {
    if (a.y < 0) {
        printf("%Lf - %Lfi\n", a.x, -a.y);
    } else {
        printf("%Lf + %Lfi\n", a.x, a.y);
    }
}
