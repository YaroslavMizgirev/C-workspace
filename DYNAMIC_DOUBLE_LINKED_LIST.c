/*
    Реализован двусвязанный список с возможностью: 
    - добавления данных с конца и с начала;
    - удаления данных с конца и с начала.

    На этой базе можно реализовать список с количеством элементов огранниченным типом unsigned int.
    При изменении (увеличении или уменьшении) типа данных переменной length_list в struct List 
    изменится и кол-во возможных элементов списка.

    СТЭК: init_list, isEmpty, push_back, pop_back
    ОЧЕРЕДЬ: init_list, isEmpty, push_back, pop_front
    ДЭК: init_list, isEmpty, push_back, push_front, pop_back, pop_front
*/
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// узел списка = элемент списка
struct Node {
    int field;              // данные списка
    struct Node *next;      // cледующий элемент списка
    struct Node *previous;  // предыдующий элемент списка
};

// список
struct List {
    unsigned int length_list;  // длина списка
    struct Node *begin;        // начало списка
    struct Node *end;          // конец списка
};

// прототипы функций
void init_list(struct List *p_var, unsigned int id);
void print_list(struct List *list);
_Bool isEmpty(struct List *list);
void push_back(struct List *list, int element);
void push_front(struct List *list, int element);
int pop_front(struct List *list);
int pop_back(struct List *list);

int main(int argc, char const *argv[]) {
    int element;              // переменная списка
    unsigned int length = 0;  // длина списка
    system("clear");
    printf("Начинаем показ операций со списком:\n");
    printf("Объявляем список.\n");
    struct List *list;
    printf("Выделяем память для списка.\n");
    list = (struct List *)malloc(sizeof(struct List));
    if (list == NULL) {
        printf("Ошибка: память для списка не выделилась.\n");
        return EXIT_FAILURE;
    } else {
        printf("Память для списка выделена успешно.\n");
    }
    printf("Инициализируем список.\n");
    init_list(list, length);
    printf("*****************************************************************************************\n");
    printf("Печатаем инициализированный список.\n");
    print_list(list);
    printf("*****************************************************************************************\n");
    // ввод данных с конца списка
    printf("Добавляем рандомно 100 элементов в конец списка значения от -999 по 999.\n");
    srand((unsigned int)time(NULL));
    for (unsigned int i = 0; i < 100; i++) {
        element = rand() % (999 - (-999) + 1) + (-999);
        printf("Элемент №%d = %d\n", i + 1, element);
        push_back(list, element);
        // !test
        printf("*****************************************************************************************\n");
        printf("Печатаем список после добавления нового элемента.\n");
        print_list(list);
        printf("*****************************************************************************************\n");
    }
    // ввод данных с начала списка
    printf("Добавляем рандомно 100 элементов в начало списка значения от -999 по 999.\n");
    srand((unsigned int)time(NULL));
    for (unsigned int i = 0; i < 100; i++) {
        element = rand() % (999 - (-999) + 1) + (-999);
        printf("Элемент №%d = %d\n", i + 1 - i, element);
        push_front(list, element);
        // !test
        printf("*****************************************************************************************\n");
        printf("Печатаем список после добавления нового элемента.\n");
        print_list(list);
        printf("*****************************************************************************************\n");
    }
    // удаление с конца списка
    printf("Удаляем 100 элементов из конца списка.\n");
    unsigned int delete_quantity = list->length_list - 100;
    for (unsigned int i = list->length_list - 1; i >= delete_quantity; i--) {
        if (list->length_list > 0) {
            element = pop_back(list);
            printf("\nУдален элемент№%d = %d\n", i + 1, element);
            // !test
            printf("Печатаем список после удаления очередного элемента.\n");
            print_list(list);
        } else {
            break;
        }
    }
    // удаление с начала списка
    printf("Удаляем 100 элементов из начала списка.\n");
    for (unsigned int i = 0; i < 100; i++) {
        if (list->length_list > 0) {
            element = pop_front(list);
            printf("\nУдален элемент№%d = %d\n", i + 1, element);
            // !test
            printf("Печатаем список после удаления очередного элемента.\n");
            print_list(list);
        } else {
            break;
        }
    }
    printf("Освобождаем память выделенную для списка.\n");
    free(list);
    list = NULL;
    printf("Заканчиваем показ операций со списком. КОНЕЦ.\n");
    return EXIT_SUCCESS;
}

// инициализация списка
void init_list(struct List *p_var, unsigned int id) {
    p_var->length_list = id;
    p_var->begin = NULL;
    p_var->end = NULL;
}

// печать списка
void print_list(struct List *list) {
    struct Node *temp_list;
    if (isEmpty(list)) {
        printf("Список пуст!\n");
    } else {
        printf("Всего %d элементов: [ ", list->length_list);
        for (temp_list = list->begin; temp_list != NULL; temp_list = temp_list->next) {
            printf("%d; ", temp_list->field);
        }
        printf("\b\b ]\n");
    }
}

//проверка на заполненность списка
_Bool isEmpty(struct List *list) {
    if (list->begin == NULL || list->end == NULL || list->length_list == 0) {
        return true;
    }
    return false;
}

//проверка на переполнение списка
_Bool isFull(struct List *list) {
    // при переполнении значения переменной типа unsigned int она обнуляется
    if (list->length_list + 1 == 0) {
        return true;
    }
    return false;
}

// добавление очередного элемента в конец списка
void push_back(struct List *list, int element) {
    if (isFull(list)) {
        printf("Список переполнен!\n");
        return;
    }
    struct Node *p_new_var;
    p_new_var = (struct Node *)malloc(sizeof(struct Node));
    if (isEmpty(list)) {
        // Node
        p_new_var->field = element;  // значение самого элемента
        p_new_var->previous = NULL;  // предыдущий элемент
        p_new_var->next = NULL;      // следующий элемент
        // List
        list->length_list++;      // длина списка
        list->begin = p_new_var;  // начало списка
        list->end = p_new_var;    // конец списка
    } else {
        // Node
        p_new_var->field = element;
        p_new_var->previous = list->end;
        p_new_var->next = NULL;
        list->end->next = p_new_var;
        // List
        list->length_list++;  // длина списка
        list->end = p_new_var;
    }
}

// добавление очередного элемента в начало списка
void push_front(struct List *list, int element) {
    if (isFull(list)) {
        printf("Список переполнен!\n");
        return;
    }
    struct Node *p_new_var;
    p_new_var = (struct Node *)malloc(sizeof(struct Node));
    if (isEmpty(list)) {
        // Node
        p_new_var->field = element;  // значение самого элемента
        p_new_var->previous = NULL;  // предыдущий элемент
        p_new_var->next = NULL;      // следующий элемент
        // List
        list->length_list++;      // длина списка
        list->begin = p_new_var;  // начало списка
        list->end = p_new_var;    // конец списка
    } else {
        // Node
        p_new_var->field = element;         // значение самого элемента
        p_new_var->previous = NULL;         // предыдущий элемент
        p_new_var->next = list->begin;      // следующий элемент
        list->begin->previous = p_new_var;  // предыдущий элемент бывшего первого элемента
        // List
        list->length_list++;      // длина списка
        list->begin = p_new_var;  // начало списка
    }
}

// удаление элемента из начала очереди
int pop_front(struct List *list) {
    struct Node *temp;
    int element;
    if (isEmpty(list)) {
        printf("Очередь пуста!\n");
        return EXIT_SUCCESS;
    }
    element = list->begin->field;
    temp = list->begin;
    if (list->length_list > 1) {
        list->begin = list->begin->next;
        list->begin->previous = NULL;
    }
    list->length_list--;
    free(temp);
    return element;
}

// удаление элемента из конца очереди
int pop_back(struct List *list) {
    struct Node *temp;
    int element;
    if (isEmpty(list)) {
        printf("Очередь пуста!\n");
        return EXIT_SUCCESS;
    }
    element = list->end->field;
    temp = list->end;
    list->end = list->end->previous;
    list->end->next = NULL;
    list->length_list--;
    free(temp);
    return element;
}
