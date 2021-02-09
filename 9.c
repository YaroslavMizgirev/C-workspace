#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct COMPLEX {
    double a;
    double b;
};

// prototypes
void print_struct_complex(struct COMPLEX *p_var);

int main(int argc, char const *argv[]) {
    struct COMPLEX *fi, *si, *ti;
    double entered_value;

    fi = NULL;
    fi = (struct COMPLEX *)malloc(sizeof(struct COMPLEX));
    printf("Первое комплексное число в формате (+-)a(+-)bi.\n");
    while (true) {
        entered_value = 0.0;
        printf("Введите значение первого слагаемого первого комплексного числа. a = ");
        scanf("%lf", &entered_value);
        if (entered_value > 0.0 || entered_value < 0.0) {
            fi->a = entered_value;
            break;
        }
    }
    while (true) {
        entered_value = 0.0;
        printf("Введите значение второго слагаемого первого комплексного числа. b = ");
        scanf("%lf", &entered_value);
        if (entered_value > 0.0 || entered_value < 0.0) {
            fi->b = entered_value;
            break;
        }
    }
    printf("Вы ввели первое комплексное число: ");
    print_struct_complex(fi);
    printf("\n\n");

    si = NULL;
    si = (struct COMPLEX *)malloc(sizeof(struct COMPLEX));
    printf("Второе комплексное число в формате (+-)c(+-)di.\n");
    while (true) {
        entered_value = 0.0;
        printf("Введите значение первого слагаемого второго комплексного числа. c = ");
        scanf("%lf", &entered_value);
        if (entered_value > 0.0 || entered_value < 0.0) {
            si->a = entered_value;
            break;
        }
    }
    while (true) {
        entered_value = 0.0;
        printf("Введите значение второго слагаемого второго комплексного числа. d = ");
        scanf("%lf", &entered_value);
        if (entered_value > 0.0 || entered_value < 0.0) {
            si->b = entered_value;
            break;
        }
    }
    printf("Вы ввели второе комплексное число: ");
    print_struct_complex(si);
    printf("\n\n");

    printf("\n");
    int menu_choice, logout;
    while (true) {
        logout = 0;
        ti = NULL;
        ti = (struct COMPLEX *)malloc(sizeof(struct COMPLEX));
        printf("1. Прибавить второе комплексное число к первому комплексному числу;\n");
        printf("2. Вычесть из первого комплексного числа второе комплексное число;\n");
        printf("3. Умножить первое комплексное число на второе комплексное число;\n");
        printf("4. Разделить первое комплексное число на второе комплексное число;\n");
        printf("5. Выход.\n");
        printf("\nВыберите арифметическое действие с комплексными числами: ");
        scanf("%d", &menu_choice);
        if (menu_choice >= 1 || menu_choice <= 5) {
            switch (menu_choice) {
                case 1:
                    printf("(");
                    print_struct_complex(fi);
                    printf(") + (");
                    print_struct_complex(si);
                    printf(") = (");
                    ti->a = fi->a + si->a;
                    ti->b = fi->b + si->b;
                    print_struct_complex(ti);
                    printf(")\n");
                    break;
                case 2:
                    printf("(");
                    print_struct_complex(fi);
                    printf(") - (");
                    print_struct_complex(si);
                    printf(") = (");
                    ti->a = fi->a - si->a;
                    ti->b = fi->b - si->b;
                    print_struct_complex(ti);
                    printf(")\n");
                    break;
                case 3:
                    printf("(");
                    print_struct_complex(fi);
                    printf(") x (");
                    print_struct_complex(si);
                    printf(") = (");
                    ti->a = (fi->a * si->a) - (fi->b * si->b);
                    ti->b = (fi->a * si->b) + (fi->b * si->a);
                    print_struct_complex(ti);
                    printf(")\n");
                    break;
                case 4:
                    printf("(");
                    print_struct_complex(fi);
                    printf(") / (");
                    print_struct_complex(si);
                    printf(") = (");
                    ti->a = ((fi->a * si->a) + (fi->b * si->b)) / (pow((double)si->a, 2) + pow((double)si->b, 2));
                    ti->b = ((si->a * fi->b) - (fi->a * si->b)) / (pow((double)si->a, 2) + pow((double)si->b, 2));
                    print_struct_complex(ti);
                    printf(")\n");
                    break;
                case 5:
                    logout++;
                    break;
            }
            if (logout > 0) {
                free(ti);
                break;
            }
        }
        free(ti);
        printf("\n\n");
    }
    free(fi);
    fi = NULL;
    free(si);
    si = NULL;
    return EXIT_SUCCESS;
}

void print_struct_complex(struct COMPLEX *p_var) {
    if (p_var != NULL) {
        if (p_var->b > 1.0) {
            if (p_var->a != 0) {
                printf("%0.3lf+%0.3lfi", p_var->a, p_var->b);
            } else {
                printf("%0.3lfi", p_var->b);
            }
        } else if (p_var->b == 1.0) {
            if (p_var->a != 0.0) {
                printf("%0.3lf+i", p_var->a);
            } else {
                printf("i");
            }
        } else if (p_var->b < 1.0 && p_var->b > 0.0) {
            if (p_var->a != 0.0) {
                printf("%0.3lf+%0.3lfi", p_var->a, p_var->b);
            } else {
                printf("%0.3lfi", p_var->b);
            }
        } else if (p_var->b < -1.0) {
            if (p_var->a != 0.0) {
                printf("%0.3lf%0.3lfi", p_var->a, p_var->b);
            } else {
                printf("%0.3lfi", p_var->b);
            }
        } else if (p_var->b == -1.0) {
            if (p_var->a != 0.0) {
                printf("%0.3lf-i", p_var->a);
            } else {
                printf("-i", p_var->a);
            }
        } else if (p_var->b > -1.0 && p_var->b < 0.0) {
            if (p_var->a != 0.0) {
                printf("%0.3lf%0.3lfi", p_var->a, p_var->b);
            } else {
                printf("%0.3lfi", p_var->b);
            }
        } else if (p_var->b == 0.0) {
            if (p_var->a != 0.0) {
                printf("%0.3lf", p_var->a);
            } else {
                printf("0");
            }
        }
    } else {
        printf("Комплексное число не определено!\n");
    }
}
