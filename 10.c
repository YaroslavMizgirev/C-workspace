#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// prototypes
int return_main_menu_point(void);
size_t return_length_of_array(void);
struct MYARRAY *fill_integer_array(struct MYARRAY *myarray);
void print_struct_array(struct MYARRAY *myarray);
struct MYARRAY *change_minmax_in_array(struct MYARRAY *myarray);
void enter_continue(void);

struct MYARRAY {
    int *array;
    size_t length_array;
};

int main(int argc, char const *argv[]) {
    if (return_main_menu_point() == EXIT_SUCCESS) {
        return EXIT_SUCCESS;
    } else {
        return EXIT_FAILURE;
    }
}

// главное меню
int return_main_menu_point(void) {
    size_t last_choice = 0;
    size_t main_menu_point = 0;
    size_t check_logout = 0;
    struct MYARRAY *myarray;
    myarray = (struct MYARRAY *)malloc(sizeof(struct MYARRAY));
    while (true) {
        // system("clear");
        if (last_choice == 0) {
            printf("1. Определяем длину целочисленного массива (от 10 до 50 включительно).\n");
        }
        if (last_choice == 1) {
            printf("2. Заполняем определенный целочисленный массив значениями (от -100 до +100 не включительно).\n");
        }
        if (last_choice == 2) {
            printf("3. Поменять местами наибольший и наименьший элементы определенного и заполненного целочисленного массива.\n");
        }
        if (last_choice == 3) {
            printf("4. Выход.\n");
        }
        printf("\n\nВыберите один из пунктов меню для продолжения: ");
        scanf("%d", &main_menu_point);
        while (getchar() != '\n')
            ;
        switch (main_menu_point) {
            case 1:
                if (last_choice == 0) {
                    last_choice++;
                    myarray->length_array = return_length_of_array();
                    printf("Длина массива составляет: %d.\n", myarray->length_array);
                    enter_continue();
                } else {
                    printf("Пункты меню можно выбирать только по порядку./n");
                    enter_continue();
                }
                break;
            case 2:
                if (last_choice == 1) {
                    last_choice++;
                    myarray = fill_integer_array(myarray);
                    print_struct_array(myarray);
                    enter_continue();
                } else {
                    printf("Пункты меню можно выбирать только по порядку./n");
                    enter_continue();
                }
                break;
            case 3:
                if (last_choice == 2) {
                    last_choice++;
                    myarray = change_minmax_in_array(myarray);
                    print_struct_array(myarray);
                    enter_continue();
                } else {
                    printf("Пункты меню можно выбирать только по порядку./n");
                    enter_continue();
                }
                break;
            case 4:
                if (last_choice == 3) {
                    check_logout++;
                } else {
                    printf("Пункты меню можно выбирать только по порядку./n");
                    enter_continue();
                }
                break;
            default:
                break;
        }
        if (check_logout > 0) {
            break;
        }
    }
    free(myarray->array);
    free(myarray);
    return EXIT_SUCCESS;
}

// заполнение длины массива
size_t return_length_of_array(void) {
    size_t length_array = 0;
    srand((unsigned int)time(NULL));
    length_array = rand() % (50 - (10) + 1) + (10);
    return length_array;
}

struct MYARRAY *fill_integer_array(struct MYARRAY *myarray) {
    if (myarray->length_array > 0) {
        myarray->array = (int *)malloc(myarray->length_array * sizeof(int));
        srand((unsigned int)time(NULL));
        for (size_t i = 0; i < myarray->length_array; i++) {
            myarray->array[i] = rand() % (99 - (-99) + 1) + (-99);
        }
    } else {
        printf("Структура MYARRAY не инициализирована.\n");
    }
    return myarray;
}

void print_struct_array(struct MYARRAY *myarray) {
    if (myarray->length_array > 0) {
        printf("Массив с %d элементами: [ ", myarray->length_array);
        for (size_t i = 0; i < myarray->length_array; i++) {
            printf("%d, ", myarray->array[i]);
        }
        printf("\b\b ]\n");
    } else {
        printf("Массив пуст!\n");
    }
}

struct MYARRAY *change_minmax_in_array(struct MYARRAY *myarray) {
    if (myarray->length_array > 0) {
        size_t min_index = -1, max_index = -1;
        int min_value, max_value;
        for (size_t i = 0; i < myarray->length_array; i++) {
            if (i == 0) {
                min_index = i;
                min_value = myarray->array[i];
                max_index = i;
                max_value = myarray->array[i];
            } else {
                if (min_value > myarray->array[i]) {
                    min_index = i;
                    min_value = myarray->array[i];
                }
                if (max_value < myarray->array[i]) {
                    max_index = i;
                    max_value = myarray->array[i];
                }
            }
        }
        if (min_index == max_index) {
            printf("Минимальное и максимальное значения в массиве совпадают!\n");
        } else {
            myarray->array[min_index] = max_value;
            myarray->array[max_index] = min_value;
            printf("Минимальное: %d на %d позиции и максимальное: %d на %d позиции значения в массиве поменены местами!\n", min_value, min_index, max_value, max_index);
        }
    } else {
        printf("Массив пуст!\n");
    }
    return myarray;
}

void enter_continue(void) {
    char enter_continue = '\0';
    while (enter_continue != '\n') {
        printf("\nНажмите клавишу 'Enter' для продолжения... ");
        enter_continue = getchar();
    }
}
