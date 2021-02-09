#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    int *array;
    int length_array;
} ARR;

struct SAW {
    struct SAW *next_saw;
    int *array;
    int length_array;
    int start_index;
    int stop_index;
    int count_saw;
};

// prototypes
ARR *get_array(void);
void print_array(ARR *p_var);
void print_saw_array(struct SAW *p_saw);
struct SAW *init_saw(void);
struct SAW *FindedSawSequenceInArray(ARR *p_arr, struct SAW *p_saw);

int main(int argc, char const *argv[]) {
    ARR *p_arr;                // обрабатываемый массив
    struct SAW *p_saw;         // результаты обработки
    struct SAW *begin = NULL;  // первый элемент в списке
    char symbol;               // признак продолжения работы программы
    int max_saw_length = 0, last_index = -1;
    while (true) {
        printf("Продолжить (Y/N): ");
        fflush(stdout);
        scanf("%c", &symbol);
        while (getchar() != '\n')
            ;
        if (symbol == 'y' || symbol == 'Y') {
            p_arr = get_array();
            print_array(p_arr);
            p_saw = init_saw();
            begin = p_saw;
            // ищем наидлиннейшую пилообразную последовательность
            p_saw = FindedSawSequenceInArray(p_arr, p_saw);
            print_saw_array(begin);
            p_saw = begin;
            while (p_saw != NULL) {
                if (max_saw_length <= p_saw->count_saw) {
                    max_saw_length = p_saw->count_saw;
                    if (last_index < p_saw->start_index) {
                        last_index = p_saw->start_index;
                    }
                }
                p_saw = p_saw->next_saw;
            }
            printf("Наидлиннейшая пилообразная последовательность (%d вершин) с максимальным индексом %d.\n", max_saw_length, last_index);
            while (begin != NULL) {
                p_saw = begin;
                // освобождаем память SAW (аналог free)
                begin->array = (int *)realloc(begin->array, 0 * sizeof(int));
                if (begin->array != NULL) {
                    printf("Ошибка освобождения выделенной пямяти p_saw->array.\n");
                    return EXIT_FAILURE;
                }
                begin = begin->next_saw;
                // освобождаем память SAW (аналог free)
                p_saw = (struct SAW *)realloc(p_saw, 0 * sizeof(struct SAW));
                if (p_saw != NULL) {
                    printf("Ошибка освобождения выделенной пямяти p_saw.\n");
                    return EXIT_FAILURE;
                }
            }
            // освобождаем память ARR (аналог free)
            p_arr->array = (int *)realloc(p_arr->array, 0 * sizeof(int));
            if (p_arr->array != NULL) {
                printf("Ошибка освобождения выделенной пямяти p_arr->array.\n");
                return EXIT_FAILURE;
            }
            // освобождаем память ARR (аналог free)
            p_arr = (ARR *)realloc(p_arr, 0 * sizeof(ARR));
            if (p_arr != NULL) {
                printf("Ошибка освобождения выделенной пямяти p_arr.\n");
                return EXIT_FAILURE;
            }
        } else {
            break;
        }
    }
    return EXIT_SUCCESS;
}

// получаем заполненную структуру ARR
ARR *get_array(void) {
    ARR *p_arr;
    while (true) {
        srand((unsigned int)time(NULL));
        p_arr = NULL;
        p_arr = (ARR *)realloc(p_arr, sizeof(ARR));
        if (p_arr != NULL) {
            p_arr->length_array = rand() % (100 - (0) + 1) + (0);
            if (p_arr->length_array > 3) {
                p_arr->array = NULL;
                p_arr->array = (int *)realloc(p_arr->array, p_arr->length_array * sizeof(int));
                if (p_arr->array != NULL) {
                    srand((unsigned int)time(NULL));
                    for (unsigned int i = 0; i < p_arr->length_array; i++) {
                        p_arr->array[i] = rand() % (10 - (-10) + 1) + (-10);
                    }
                    return p_arr;
                } else {
                    free(p_arr);
                    p_arr = NULL;
                }
            }
        }
    }
}

// печать массива из структуры ARR
void print_array(ARR *p_arr) {
    if (p_arr != NULL) {
        if (p_arr->length_array > 0 && p_arr->array != NULL) {
            printf("Массив из %d элементов: [ ", p_arr->length_array);
            for (int i = 0; i < p_arr->length_array; i++) {
                printf("(%d): %d, ", i, p_arr->array[i]);
            }
            printf("\b\b ]\n");
        } else {
            printf("Массив пустой!\n");
        }
    } else {
        printf("Нет данных для печати!\n");
    }
}

//
void print_saw_array(struct SAW *p_saw) {
    if (p_saw != NULL) {
        while (p_saw != NULL) {
            if (p_saw->length_array > 0 && p_saw->array != NULL) {
                printf("Начало - %d, конец - %d, вершин - %d, массив из %d элементов: [ ", p_saw->start_index, p_saw->stop_index, p_saw->count_saw, p_saw->length_array);
                for (unsigned int j = 0; j < p_saw->length_array; j++) {
                    printf("(%d): %d, ", j, p_saw->array[j]);
                }
                printf("\b\b ]\n");
            } else {
                printf("Массив пустой!\n");
            }
            p_saw = p_saw->next_saw;
        }
    } else {
        printf("Нет данных для печати!\n");
    }
}

// инициализируем массив результатов
struct SAW *init_saw(void) {
    struct SAW *p_saw;
    while (true) {
        p_saw = NULL;
        p_saw = (struct SAW *)realloc(p_saw, 1 * sizeof(struct SAW));
        if (p_saw != NULL) {
            p_saw->next_saw = NULL;
            p_saw->length_array = 0;
            p_saw->start_index = -1;
            p_saw->stop_index = -1;
            p_saw->count_saw = 0;
            p_saw->array = NULL;
            p_saw->array = (int *)realloc(p_saw->array, 1 * sizeof(int));
            if (p_saw->array != NULL) {
                return p_saw;
            }
        }
    }
}

// проверяем при заполнении временного массива на условия задачи: A[i] < A[i + 1], A[i + 1] > A[i + 2], A[i + 2] < A[i + 3] и т.д.
struct SAW *FindedSawSequenceInArray(ARR *p_arr, struct SAW *p_saw) {
    unsigned int saw_count = 1;  // кол-во элементов массива SAW
    struct SAW *p_new_saw;       // следующий элемент в списке
    // работаем
    if (p_arr != NULL) {
        if (p_arr->length_array > 3 && p_arr->array != NULL) {
            unsigned int i = 0;  // индекс p_arr
            while (true) {
                if (p_saw->length_array == 0) {
                    p_saw->start_index = i;
                    p_saw->stop_index = i;
                    p_saw->array[p_saw->length_array] = p_arr->array[i++];
                    p_saw->length_array++;
                } else if (p_saw->length_array > 0 && p_saw->length_array % 2 == 0) {
                    if (p_saw->array[p_saw->length_array - 1] > p_arr->array[i]) {
                        p_saw->array = (int *)realloc(p_saw->array, (p_saw->length_array + 1) * sizeof(int));
                        if (p_saw->array == NULL) {
                            printf("Ошибка перераспределения памяти временному массиву.\n");
                            exit(EXIT_FAILURE);
                        }
                        p_saw->stop_index = i;
                        p_saw->count_saw++;
                        p_saw->array[p_saw->length_array] = p_arr->array[i++];
                        p_saw->length_array++;
                    } else {
                        // проверяем наличие пил
                        if (p_saw->count_saw > 0) {
                            // двигаемся дальше по структуре ARR
                            i = (p_saw->start_index + p_saw->count_saw * 2) + 1;
                            // откат SAW
                            while (p_saw->stop_index > (p_saw->start_index + p_saw->count_saw * 2)) {
                                p_saw->array = (int *)realloc(p_saw->array, (p_saw->length_array - 1) * sizeof(int));
                                if (p_saw->array == NULL) {
                                    printf("Ошибка перераспределения памяти временному массиву.\n");
                                    exit(EXIT_FAILURE);
                                }
                                p_saw->length_array--;
                                p_saw->stop_index--;
                            }
                            // двигаемся дальше по структуре SAW
                            p_new_saw = init_saw();
                            p_saw->next_saw = p_new_saw;
                            p_saw = p_new_saw;
                        } else {
                            // двигаемся дальше по структуре ARR
                            i = (p_saw->start_index + p_saw->count_saw * 2) + 1;
                            // откат SAW
                            p_saw->array = (int *)realloc(p_saw->array, 1 * sizeof(int));
                            if (p_saw->array == NULL) {
                                printf("Ошибка перераспределения памяти временному массиву.\n");
                                exit(EXIT_FAILURE);
                            }
                            p_saw->length_array = 0;
                            p_saw->start_index = -1;
                            p_saw->stop_index = -1;
                        }
                    }
                } else if (p_saw->length_array > 0 && p_saw->length_array % 2 != 0) {
                    if (p_saw->array[p_saw->length_array - 1] < p_arr->array[i]) {
                        p_saw->array = (int *)realloc(p_saw->array, (p_saw->length_array + 1) * sizeof(int));
                        if (p_saw->array == NULL) {
                            printf("Ошибка перераспределения памяти временному массиву.\n");
                            exit(EXIT_FAILURE);
                        }
                        p_saw->stop_index = i;
                        p_saw->array[p_saw->length_array] = p_arr->array[i++];
                        p_saw->length_array++;
                    } else {
                        // проверяем наличие пил
                        if (p_saw->count_saw > 0) {
                            // двигаемся дальше по структуре ARR
                            i = (p_saw->start_index + p_saw->count_saw * 2) + 1;
                            // откат SAW
                            while (p_saw->stop_index > (p_saw->start_index + p_saw->count_saw * 2)) {
                                p_saw->array = (int *)realloc(p_saw->array, (p_saw->length_array - 1) * sizeof(int));
                                if (p_saw->array == NULL) {
                                    printf("Ошибка перераспределения памяти временному массиву.\n");
                                    exit(EXIT_FAILURE);
                                }
                                p_saw->length_array--;
                                p_saw->stop_index--;
                            }
                            // двигаемся дальше по структуре SAW
                            p_new_saw = init_saw();
                            p_saw->next_saw = p_new_saw;
                            p_saw = p_new_saw;
                        } else {
                            // двигаемся дальше по структуре ARR
                            i = (p_saw->start_index + p_saw->count_saw * 2) + 1;
                            // откат SAW
                            p_saw->array = (int *)realloc(p_saw->array, 1 * sizeof(int));
                            if (p_saw->array == NULL) {
                                printf("Ошибка перераспределения памяти временному массиву.\n");
                                exit(EXIT_FAILURE);
                            }
                            p_saw->length_array = 0;
                            p_saw->start_index = -1;
                            p_saw->stop_index = -1;
                        }
                    }
                }
                if (i >= p_arr->length_array) {
                    if (p_saw->count_saw > 0) {  // если есть вершина, корректируем последний элемент из списка
                        while (p_saw->stop_index > (p_saw->start_index + p_saw->count_saw * 2)) {
                            p_saw->array = (int *)realloc(p_saw->array, (p_saw->length_array - 1) * sizeof(int));
                            if (p_saw->array == NULL) {
                                printf("Ошибка перераспределения памяти временному массиву.\n");
                                exit(EXIT_FAILURE);
                            }
                            p_saw->length_array--;
                            p_saw->stop_index--;
                        }
                    } else {  // если нет вершины удаляем последний элемент из списка
                        p_saw->array = (int *)realloc(p_saw->array, 0 * sizeof(int));
                        if (p_saw->array != NULL) {
                            printf("Ошибка освобождения выделенной пямяти p_saw->array.\n");
                            exit(EXIT_FAILURE);
                        }
                        p_saw->stop_index = -1;
                        p_saw->start_index = -1;
                        p_saw->length_array = 0;
                    }
                    break;
                }
            }
            return p_saw;
        } else {
            return p_saw;
        }
    } else {
        return p_saw;
    }
}
