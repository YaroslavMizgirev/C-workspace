/* 
    size_t - целое число без знака тип не менее 16 бит, используется для представления размера объекта.
*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// prototypes
struct RESULT_ARRAY *return_result_array(int *array, size_t length_array);
_Bool hasNumberInArray(int number, struct RESULT_ARRAY *result_array);
void print_integer_array(int *array, size_t length_array);
void print_struct_array(struct RESULT_ARRAY *result_array);

struct RESULT_ARRAY {
    int *array;
    size_t length_array;
};

int main(int argc, char const *argv[]) {
    // определяем длину массива
    size_t length_array = 0;
    srand((unsigned int)time(NULL));
    length_array = (size_t)(rand() % (140 - (10) + 1) + (10));
    // выделяем память и инициализируем массив
    int *array = (int *)malloc(length_array * sizeof(int));
    srand((unsigned int)time(NULL));
    for (size_t i = 0; i < length_array; i++) {
        array[i] = rand() % (10 - (-10) + 1) + (-10);
    }
    printf("БЫЛО \n");
    print_integer_array(array, length_array);
    printf("*********************************************************\n");
    // вычисляем результирующий массив
    struct RESULT_ARRAY *result_array;
    result_array = return_result_array(array, length_array);
    printf("СТАЛО \n");
    print_struct_array(result_array);
    printf("*********************************************************\n");
    //
    free(result_array->array);
    free(array);
    return EXIT_SUCCESS;
}

struct RESULT_ARRAY *return_result_array(int *array, size_t length_array) {
    struct RESULT_ARRAY *new_array;
    new_array = (struct RESULT_ARRAY *)malloc(sizeof(struct RESULT_ARRAY));
    new_array->length_array = 0;
    new_array->array = NULL;
    new_array->array = (int *)malloc(new_array->length_array * sizeof(int));
    size_t i = 0;
    while (i < length_array) {
        if (new_array->length_array == 0) {
            new_array->array[new_array->length_array++] = array[i++];
        } else if (new_array->length_array > 0) {
            if (!hasNumberInArray(array[i], new_array)) {
                new_array->array[new_array->length_array++] = array[i++];
            } else {
                i++;
            }
        }
    }
    return new_array;
}

_Bool hasNumberInArray(int number, struct RESULT_ARRAY *result_array) {
    for (size_t i = 0; i < result_array->length_array; i++) {
        if (result_array->array[i] == number) {
            return true;
        }
    }
    return false;
}

void print_integer_array(int *array, size_t length_array) {
    if (length_array > 0) {
        printf("Массив из %d элементов: [ ", length_array);
        for (size_t i = 0; i < length_array; i++) {
            printf("(%d): %d, ", i, array[i]);
        }
        printf("\b\b ]\n");
    } else {
        printf("Массив пуст!\n");
    }
}

void print_struct_array(struct RESULT_ARRAY *result_array) {
    if (result_array->length_array > 0) {
        printf("Массив из %d элементов: [ ", result_array->length_array);
        for (unsigned int i = 0; i < result_array->length_array; i++) {
            printf("(%d): %d, ", i, result_array->array[i]);
        }
        printf("\b\b ]\n");
    } else {
        printf("Массив пуст!\n");
    }
}
