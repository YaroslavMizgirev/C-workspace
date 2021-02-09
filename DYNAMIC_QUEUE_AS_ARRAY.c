#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Тип данных очереди
typedef struct {
    int *digit;            // массив хранения значений очереди
    unsigned int p_End;    // Указатель на хвост (по нему включают)
    unsigned int p_Begin;  // Указатель на голову (по нему исключают)
    unsigned int length;   // Количество элементов в очереди
} QueueArray;

// prototypes
void init_queue_as_array(QueueArray *p_var);
void push_queue_as_array(QueueArray *p_var, int dig_var);
void pop_queue_as_array(QueueArray *p_var);
_Bool isFull_Queue(QueueArray *p_var);
_Bool isEmpty_Queue(QueueArray *p_var);
void print_queue(QueueArray *p_var);

int main(int argc, char *args[]) {
    int element;
    printf("Очередь на массиве.\n");
    printf("Объявляем очередь на массиве.\n");
    QueueArray *p_var;
    printf("Выделяем память для очереди на массиве.\n");
    p_var = malloc(sizeof(QueueArray));
    if (p_var == NULL) {
        printf("Ошибка выделения памяти для очереди на массиве.\n");
        return EXIT_FAILURE;
    } else {
        printf("Память для очереди на массиве выделена успешно.\n");
    }
    printf("Инициализируем очередь на массиве.\n");
    init_queue_as_array(p_var);
    printf("Печатаем очередь на массиве после инициализации.\n");
    print_queue(p_var);
    //
    printf("Добавляем 100 рандомных элементов в конец массива данных очереди на массиве (от -999 по 999).\n");
    srand((unsigned int)time(NULL));
    for (unsigned int i = 0; i < 100; i++) {
        element = rand() % (999 - (-999) + 1) + (-999);
        push_queue_as_array(p_var, element);
        // !test
        printf("Печатаем после добавления %d элемента = %d.\n", i + 1, element);
        print_queue(p_var);
    }
    //
    printf("Удаляем 100 элементов из начала массива данных очереди на массиве.\n");
    unsigned int pop_count = 0;
    while (pop_count < 100) {
        pop_queue_as_array(p_var);
        // !test
        printf("Печатаем после удаления %d элемента.\n", pop_count + 1);
        print_queue(p_var);
        pop_count++;
    }
    printf("Освобождаем выделенную память для очереди на массиве.\n");
    free(p_var);
    p_var = NULL;
    printf("Конец.\n");
    return EXIT_SUCCESS;
}

// инициализируем очередь
void init_queue_as_array(QueueArray *p_var) {
    p_var->digit = NULL;  // массив значений хранящихся в списке
    p_var->p_Begin = 0;   // первый элемент очереди
    p_var->p_End = 0;     // последний элемент очереди
    p_var->length = 0;    // длина очереди
}

// добавляем в очередь
void push_queue_as_array(QueueArray *p_var, int dig_var) {
    if (isFull_Queue(p_var)) {
        printf("Очередь переполнена!\n");
        return;
    }
    p_var->digit = (int *)realloc(p_var->digit, (p_var->length + 1) * sizeof(int));
    if (p_var->digit != NULL) {
        p_var->length++;  // Увеличение количества элементов очереди
    } else {
        printf("Ошибка: не выделяется память для новых элементов очереди в массиве!\n");
        return;
    }
    if (p_var->length > 1) {
        p_var->p_End++;  // Сдвиг указателя
    }
    *(p_var->digit + p_var->p_End) = dig_var;  // Включение элемента
}

// Исключение из очереди
void pop_queue_as_array(QueueArray *p_var) {
    int *temp;
    if (isEmpty_Queue(p_var)) {
        printf("Очередь пуста!\n");
        return;
    }
    printf("Удаляем %d элемент массива = %d\n", p_var->p_Begin + 1, p_var->digit[p_var->p_Begin]);
    if (p_var->length > 1) {
        for (unsigned int i = 1; i < p_var->length; i++) {
            *(p_var->digit + i - 1) = *(p_var->digit + i);
        }
        p_var->p_End--;
        p_var->length--;
        if (p_var->length > 2) {
            p_var->digit = (int *)realloc(p_var->digit, (p_var->length - 1) * sizeof(int));
            if (p_var->digit != NULL) {
                printf("Память для очереди на массиве перераспределена успешно.\n");
            } else {
                printf("Ошибка перераспределения выделенной памяти для очереди на массиве.\n");
            }
        }
    } else if (p_var->length == 1) {
        free(p_var->digit);
        p_var->digit = NULL;
        p_var->length--;
    }
}

// Проверка полна ли очередь
_Bool isFull_Queue(QueueArray *p_var) {
    // при переполнении значения переменной типа unsigned int она обнуляется
    if (p_var->length + 1 == 0) {
        return true;
    }
    return false;
}

// Проверка пуста ли очередь
_Bool isEmpty_Queue(QueueArray *p_var) {
    if (p_var->length == 0) {
        return true;
    }
    return false;
}

// Печать очереди на массиве
void print_queue(QueueArray *p_var) {
    if (isEmpty_Queue(p_var)) {
        printf("Очередь пуста!\n");
    } else {
        printf("В очереди %d элементов: [ ", p_var->length);
        for (int i = 0; i < p_var->length; i++) {
            printf("%d; ", p_var->digit[i]);
        }
        printf("\b\b ]\n");
    }
}
