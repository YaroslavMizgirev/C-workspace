#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

// prototypes
double mid_geom(char type, int num, ...);

int main(void) {
    mid_geom('i', 2, 11111, 22222);
    mid_geom('d', 6, 555555.501, 1255555.0009, 299999.15, 1000000.3779, 999999.45, 0.855);
    return EXIT_SUCCESS;
}

// вычисляем среднее геометрическое переданных чисел
double mid_geom(char type, int num, ...) {
    int int_sum = 0;
    int a;
    double double_sum = 0.0;
    double b;
    double result = 0.0;
    double x, y;
    va_list factor;
    va_start(factor, num);
    printf("Среднее геометрическое: (");
    switch (type) {
        case 'i':
            for (unsigned int i = 0; i < num; i++) {
                a = va_arg(factor, int);
                printf("%d + ", a);
                int_sum += a;
            }
            x = int_sum * 1.0;
            y = 1.0 / num * 1.0;
            printf("\b\b\b)^%lf = ", y);
            result = pow(x, y);
            printf("%lf.\n", result);
            break;
        case 'd':
            for (unsigned int i = 0; i < num; i++) {
                b = va_arg(factor, double);
                printf("%lf + ", b);
                double_sum += b;
            }
            x = double_sum;
            y = 1.0 / num * 1.0;
            printf("\b\b\b)^%lf = ", y);
            result = pow(x, y);
            printf("%lf.\n", result);
            break;
        default:
            printf("Неопознанный тип данных.\n");
            break;
    }
    va_end(factor);
    return result;
}
