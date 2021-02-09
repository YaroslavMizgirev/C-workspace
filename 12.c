#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

// prototype
void polinom_in_point(int variable, int num, ...);

int main(int argc, char const *argv[]) {
    polinom_in_point(1, 12, -6, 7, -5, 4, 137, 3, -1, 2, 1, 1, -10, 0);
    polinom_in_point(1, 6, 555555, 5, -299999, 4, -999999, 0);
    polinom_in_point(1, 6, 55, 2, -29, 1, 0, 0);
    return EXIT_SUCCESS;
}

// вычисляем значение полинома в точке
void polinom_in_point(int variable, int num, ...) {
    double monom = 0.0;
    int a, b;
    va_list factor;
    va_start(factor, num);
    printf("Значение полинома: ");
    for (unsigned int i = 0; i < num; i++) {
        if (i % 2 == 0) {
            a = va_arg(factor, int);

        } else {
            b = va_arg(factor, int);
            switch (b) {
                case 0:
                    if (a < -1) {
                        printf("%d", a);
                    } else if (a == -1) {
                        printf("%d", a);
                    } else if (a > 1) {
                        printf("+%d", a);
                    } else if (a == 1) {
                        printf("+%d", a);
                    } else if (a == 0) {
                        printf("");
                    }
                    variable = 1;
                    monom += (double)a * (double)variable;
                    break;
                case 1:
                    if (a < -1) {
                        printf("%dx", a);
                    } else if (a == -1) {
                        printf("-x");
                    } else if (a > 1) {
                        printf("+%dx", a);
                    } else if (a == 1) {
                        printf("+x");
                    } else if (a == 0) {
                        printf("");
                    }
                    monom += (double)a * (double)variable;
                    break;
                default:
                    if (a < 0) {
                        printf("%dx^%d", a, b);
                    } else if (a == -1) {
                        printf("-x^%d", b);
                    } else if (a > 1) {
                        printf("+%dx^%d", a, b);
                    } else if (a == 1) {
                        printf("+x^%d", b);
                    } else if (a == 0) {
                        printf("");
                    }
                    variable = pow((double)variable, (double)b);
                    monom += (double)a * (double)variable;
                    break;
            }
        }
    }
    printf(" в точке: %0.3lf ", (double)variable);
    printf(" равно ");
    printf("%0.3lf\n", monom);
    va_end(factor);
}
