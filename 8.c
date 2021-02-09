/*
 * 8.c
 *
 *  Created on: 3 февр. 2021 г.
 *      Author: rapMoHuk
 */
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    _Bool isError;
    int result;
} my_atoi_int;

// prototypes
char *init_new_string(size_t length_new_string);
struct MYARRAY *init_myarray(void);
int *init_integer_array(void);
int fill_array_and_write_to_file(char *file_name);
void print_struct_array(struct MYARRAY *myarray);
struct MYARRAY *convert_string_to_struct_array(char *source_string);
my_atoi_int *atoi_int_mod(const char *str);
struct MYARRAY *sort_array(struct MYARRAY *myarray);
int write_array_to_file(char *file_name, struct MYARRAY *myarray);

struct MYARRAY {
    int *array;
    size_t length_array;
};

int main(int argc, char const *argv[]) {
    FILE *in_file_handler;
    char *in_file_name = init_new_string(150);
    // char in_file_name[150] = "/home/rapMoHuk/workspace/c-workspace/teach/in_8.txt";
    char *out_file_name = init_new_string(150);
    // char out_file_name[150] = "/home/rapMoHuk/workspace/c-workspace/teach/out_8.txt";
    char *source_string = init_new_string(150);
    char *target_string = init_new_string(15000);
    int error_count = 0;
    struct MYARRAY *myarray;
    if (argc > 2) {
        strcpy(in_file_name, argv[1]);
        strcpy(out_file_name, argv[2]);
        // формируем массив и записываем его в файл
        if (fill_array_and_write_to_file(in_file_name) != EXIT_SUCCESS) {
            return EXIT_FAILURE;
        }
        printf("Открываем файл для чтения данных: '%s'.\n", in_file_name);
        if ((in_file_handler = fopen(in_file_name, "r")) == NULL) {
            printf("Ошибка открытия файла для чтения данных: '%s'.\n", in_file_name);
            error_count++;
        }
        if (error_count == 0) {
            while (true) {
                if ((fgets(source_string, 150, in_file_handler)) == NULL) {
                    if (feof(in_file_handler)) {
                        printf("Конец файла для чтения данных: '%s'.\n", in_file_name);
                        break;
                    } else {
                        printf("Ошибка в файле для чтения данных: '%s'.\n", in_file_name);
                        break;
                    }
                }
                strcat(target_string, source_string);
            }
            if (fclose(in_file_handler) == EOF) {
                printf("Ошибка закрытия файла для чтения данных: '%s'.\n", in_file_name);
                exit(EXIT_FAILURE);
            } else {
                printf("Файл для чтения данных: '%s' успешно закрыт.\n", in_file_name);
            }
        }

        printf("%s\n", target_string);
        printf("**************************\n");
        printf("Преобразовываем прочитанные данные ...\n");
        if ((myarray = convert_string_to_struct_array(target_string)) == NULL) {
            return EXIT_FAILURE;
        }
        printf("Массив до сортировки: \n");
        print_struct_array(myarray);
        myarray = sort_array(myarray);
        printf("Массив после сортировки: \n");
        print_struct_array(myarray);
        if ((write_array_to_file(out_file_name, myarray)) != EXIT_SUCCESS) {
            free(myarray->array);
            free(myarray);
            return EXIT_FAILURE;
        }
        free(myarray->array);
        free(myarray);
    } else {
        printf("Первый параметр - абсолютный путь файла источник данных для обработки.\n");
        printf("Второй параметр - абсолютный путь файла для сохранения результатов вычислений.\n");
        printf("Больше параметров нет.\n");
    }
    free(in_file_name);
    free(out_file_name);
    free(source_string);
    return EXIT_SUCCESS;
}

// выделяем память и инициализируем новую пустую строку длиной 150 символов
char *init_new_string(size_t length_new_string) {
    char *new_string;
    new_string = (char *)malloc(length_new_string * sizeof(char));
    new_string[0] = '\0';
    return new_string;
}

// выделяем память и инициализируем новую пустую структуру MYARRAY
struct MYARRAY *init_myarray(void) {
    struct MYARRAY *myarray = NULL;
    myarray = (struct MYARRAY *)malloc(sizeof(struct MYARRAY));
    myarray->length_array = 0;
    myarray->array = NULL;
    return myarray;
}

// выделяем память и инициализируем новый пустой целочисленный массив
int *init_integer_array(void) {
    int *array = NULL;
    array = (int *)malloc(sizeof(int));
    return array;
}

// формируем массив и записываем его в файл
int fill_array_and_write_to_file(char *file_name) {
    FILE *file_handler = fopen(file_name, "w");
    if (file_handler == NULL) {
        printf("Ошибка открытия файла для чтения данных: '%s'.\n", file_name);
        return EXIT_FAILURE;
    }
    srand((unsigned int)time(NULL));
    size_t length_array = rand() % (1000 - (10) + 1) + (10);
    int *array = (int *)malloc(length_array * sizeof(int));
    for (size_t i = 0; i < length_array; i++) {
        array[i] = rand() % (999 - (-999) + 1) + (-999);
        fprintf(file_handler, "%d ", array[i]);
    }
    if (fclose(file_handler) == EOF) {
        printf("Ошибка закрытия файла для чтения данных: '%s'.\n", file_name);
        free(array);
        return EXIT_FAILURE;
    }
    free(array);
    printf("Done.\n");
    return EXIT_SUCCESS;
}

// печатаем структуру
void print_struct_array(struct MYARRAY *myarray) {
    if (myarray->length_array > 0) {
        printf("Массив с %zu элементами: [ ", myarray->length_array);
        for (size_t i = 0; i < myarray->length_array; i++) {
            printf("%d, ", myarray->array[i]);
        }
        printf("\b\b ]\n");
    } else {
        printf("Массив пуст!\n");
    }
}

struct MYARRAY *convert_string_to_struct_array(char *source_string) {
    size_t error_count = 0;                            // счетчик ошибок
    char string_with_dividers[] = "[],; ";             // возможные делители
    char *result_divider;                              // строка с результатом деления
    char *save_position;                               // позиция чтения строки с результатом деления
    char *copy_source_string = strdup(source_string);  // дубликат строки source_string
    if (copy_source_string == NULL) {
        printf("Дубликат строки source_string не создан.\n");
        return NULL;
    }
    struct MYARRAY *myarray = init_myarray();  // одна переменная структуры MYARRAY
    myarray->array = init_integer_array();     // один элемент в целочисленном массиве
    my_atoi_int *p_var = NULL;
    int save_number;  // при расширении памяти myarray переменная p_var сбрасывается (более стабильное хранение)
    result_divider = strtok_r(copy_source_string, string_with_dividers, &save_position);
    while (result_divider != NULL) {
        p_var = atoi_int_mod(result_divider);
        if (!p_var->isError) {
            save_number = p_var->result;
            if (myarray->length_array == 0) {
                myarray->array[myarray->length_array++] = save_number;
            } else {
                myarray->array = (int *)realloc(myarray->array, (myarray->length_array + 1) * sizeof(int));
                if (myarray->array == NULL) {
                    printf("Ошибка перераспределения памяти в массиве myarray->array.\n");
                    error_count++;
                    break;
                }
                myarray->array[myarray->length_array++] = save_number;
            }
            // !test
            // print_struct_array(myarray);
        } else {
            error_count++;
            break;
        }
        result_divider = strtok_r(NULL, string_with_dividers, &save_position);
    }
    if (error_count > 0) {
        free(myarray->array);
        free(myarray);
        return NULL;
    } else {
        return myarray;
    }
}

// analog atoi() with error check -> int
my_atoi_int *atoi_int_mod(const char *str) {
    my_atoi_int var, *p_var;
    int error_count = 0;  // счетчик ошибок (по умолчанию 0)
    int result = 0;       // результат (по умолчанию 0)
    int sign = 1;         // знак числа (по умолчанию положительный)
    unsigned int i = 0;   // индекс элемента строки
    if (*str == '\0') {
        printf("\n\n!!!!!!! ERROR: !!!!!!!\n");
        printf("*Пустая строка не может преобразоваться в число*\n");
        printf("!!!!!!! ERROR: !!!!!!!\n\n\n");
        fflush(stdout);
        error_count++;
    } else {
        if (str[i] == '-') {
            sign = -1;
            i++;
        }
        for (; str[i] != '\0'; ++i) {
            if (!isdigit(str[i])) {
                printf("\n\n!!!!!!! ERROR: !!!!!!!\n");
                printf("*Символ №%d: '%c' не является числом*\n", i + 1, str[i]);
                printf("!!!!!!! ERROR: !!!!!!!\n\n\n");
                fflush(stdout);
                error_count++;
            }
            result = result * 10 + str[i] - '0';
        }
    }
    if (error_count > 0) {
        var.isError = true;
        var.result = 0;
    } else {
        var.isError = false;
        var.result = sign * result;
    }
    p_var = &var;
    return p_var;
}

// пузырьковая сортировка по возрастанию
struct MYARRAY *sort_array(struct MYARRAY *myarray) {
    if (myarray->length_array > 0) {
        int temp;
        _Bool isSorted = false;
        while (!isSorted) {
            isSorted = true;
            for (size_t i = 1; i < myarray->length_array; i++) {
                if (myarray->array[i] < myarray->array[i - 1]) {
                    temp = myarray->array[i - 1];
                    myarray->array[i - 1] = myarray->array[i];
                    myarray->array[i] = temp;
                    isSorted = false;
                }
            }
        }
        printf("Массив отсортирован!\n");
        // !test
        // print_struct_array(myarray);
        return myarray;
    } else {
        printf("Массив пуст!\n");
        return NULL;
    }
}

// запись в файл
int write_array_to_file(char *file_name, struct MYARRAY *myarray) {
    FILE *file_handler = NULL;
    int error_count = 0;
    printf("Открываем файл для записи данных: '%s'.\n", file_name);
    if ((file_handler = fopen(file_name, "w")) == NULL) {
        printf("Ошибка открытия файла для записи данных: '%s'.\n", file_name);
        error_count++;
    }
    if (error_count == 0) {
        if (myarray->length_array > 0) {
            fprintf(file_handler, "[ ");
            for (size_t i = 0; i < myarray->length_array; i++) {
                fprintf(file_handler, "%d ", myarray->array[i]);
            }
            fprintf(file_handler, "]\n");
        } else {
            printf("Массив пуст!\n");
        }
        if (fclose(file_handler) == EOF) {
            printf("Ошибка закрытия файла для записи данных: '%s'.\n", file_name);
            return EXIT_FAILURE;
        } else {
            printf("Файл для записи данных: '%s' успешно закрыт.\n", file_name);
        }
        return EXIT_SUCCESS;
    } else {
        return EXIT_FAILURE;
    }
}
