#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    int *array;
    int length_array;
} ARR;

// prototypes
ARR *get_array();
void print_array(ARR *p_var);

int main(int argc, char const *argv[]) {
    int element, max_length = 0, index_start_max_length = -1, temp_length = 0, index_start_temp_length = -1;
    ARR *p_var;
    char symbol;
    while (true) {
        printf("Продолжить (Y/N): ");
        fflush(stdout);
        scanf("%c", &symbol);
        while (getchar() != '\n')
            ;
        if (symbol == 'y' || symbol == 'Y') {
            max_length = 0;
            index_start_max_length = -1;
            temp_length = 0;
            index_start_temp_length = -1;
            p_var = get_array();
            print_array(p_var);
            // ищем наидлиннейшую последовательность нулей
            for (unsigned int j = 0; j < p_var->length_array; j++) {
                if (p_var->array[j] == 0) {
                    temp_length++;
                    if (index_start_temp_length < 0) {
                        index_start_temp_length = j;
                    }
                } else if (p_var->array[j] != 0) {
                    if (max_length < temp_length) {
                        max_length = temp_length;
                        index_start_max_length = index_start_temp_length;
                    }
                    temp_length = 0;
                    index_start_temp_length = -1;
                }
            }
            printf("Наидлиннейшая последовательность нулей %d знаков с минимальным индексом %d.\n", max_length, index_start_max_length);
            // освобождаем память (аналог free)
            p_var->array = (int *)realloc(p_var->array, 0 * sizeof(int));
            if (p_var->array != NULL) {
                printf("Ошибка освобождения выделенной пямяти.\n");
                return EXIT_FAILURE;
            }
            p_var = (ARR *)realloc(p_var, 0 * sizeof(ARR));
            if (p_var != NULL) {
                printf("Ошибка освобождения выделенной пямяти.\n");
                return EXIT_FAILURE;
            }
        } else {
            break;
        }
    }
    return EXIT_SUCCESS;
}

ARR *get_array() {
    ARR *p_var;
    while (true) {
        srand((unsigned int)time(NULL));
        p_var = NULL;
        p_var = (ARR *)realloc(p_var, sizeof(ARR));
        p_var->length_array = rand() % (100 - (0) + 1) + (0);
        if (p_var->length_array > 0) {
            p_var->array = NULL;
            p_var->array = (int *)realloc(p_var->array, p_var->length_array * sizeof(int));
            if (p_var->array == NULL) {
                printf("Ошибка выделения пямяти.\n");
                return NULL;
            }
            srand((unsigned int)time(NULL));
            for (unsigned int j = 0; j < p_var->length_array; j++) {
                p_var->array[j] = rand() % (1 - (-1) + 1) + (-1);
            }
            return p_var;
        }
    }
}

void print_array(ARR *p_var) {
    printf("[ ");
    for (int i = 0; i < p_var->length_array; i++) {
        printf("%d, ", p_var->array[i]);
    }
    printf("\b\b ]\n");
}
