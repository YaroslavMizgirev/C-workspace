#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct list {
    int field;          // данные списка
    struct list *next;  // cледующий элемент списка
};

struct queue {
    unsigned int queue_count;  // счетчик элементов очереди
    struct list *first;        // первый элемент в очереди
    struct list *last;         // последний элемент в очереди
};

void init_queue(struct queue *p_var, unsigned int id);
struct list *init_list(int element);
void print(struct queue *q);
_Bool isEmpty(struct queue *q);
void push_back(struct queue *q, int element, unsigned int id);
struct list *addelem(struct list *lst, int element);
int pop_front(struct queue *q);

int main(int argc, char const *argv[]) {
    struct queue *q;
    int element;
    unsigned int id = 0;
    system("clear");
    printf("Начинаем показ операций с очередью:\n");
    //
    printf("Выделяем память для очереди.\n");
    q = (struct queue *)malloc(sizeof(struct queue));  // выделяем памяти
    if (q == NULL) {
        printf("Ошибка: память для очереди - не выделилась.\n");
        return EXIT_FAILURE;
    } else {
        printf("Память для очереди - выделена успешно.\n");
    }
    //
    printf("Инициализируем очередь.\n");
    init_queue(q, id);  // инициализация новой очереди
    //
    // !test
    printf("Печатаем инициализированную очередь.\n");
    print(q);  // печать очереди
    //
    // ввод данных
    printf("Вводим рандомно элементы в список и формируем очередь.\n");
    srand((unsigned int)time(NULL));
    for (unsigned int i = 0; i < 100; i++) {
        element = rand() % (999 - (-999) + 1) + (-999);
        printf("Элемент №%d = %d\n", i + 1, element);
        push_back(q, element, i + 1);
        // !test
        printf("Печатаем очередь после добавления нового элемента.\n");
        print(q);  // печать очереди
    }
    printf("\n");
    //
    // !test
    printf("Печатаем полученную очередь, после ввода данных.\n");
    print(q);  // печать очереди
    //
    printf("Удаляем элементы из очереди.\n");
    while (q->first != NULL) {
        element = pop_front(q);
        printf("\nУдален элемент %d\n", element);
        // !test
        printf("Печатаем очередь после удаления очередного элемента.\n");
        print(q);  // печать очереди
    }
    //
    // !test
    printf("Печатаем полученную очередь, после удаления данных.\n");
    print(q);  // печать очереди
    //
    printf("Освобождаем память выделенную для очереди.\n");
    free(q);
    q = NULL;
    //
    printf("Заканчиваем показ операций с очередью. КОНЕЦ.\n");
    return EXIT_SUCCESS;
}

// инициализация queue
void init_queue(struct queue *p_var, unsigned int id) {
    p_var->queue_count = id;
    p_var->first = NULL;
    p_var->last = NULL;
}
// инициализация list
struct list *init_list(int element) {
    struct list *lst;
    // выделение памяти под корень списка
    lst = (struct list *)malloc(sizeof(struct list));
    lst->field = element;
    lst->next = NULL;  // это последний узел списка
    return lst;
}

// печать очереди
void print(struct queue *q) {
    struct list *h;
    if (isEmpty(q)) {
        printf("Очередь пуста!\n");
    } else {
        printf("В очереди %d элементов: ", q->queue_count);
        printf("[\t");
        for (h = q->first; h != NULL; h = h->next) {
            printf("%d\t", h->field);
        }
        printf("]\n");
    }
}

// проверка на пустую очередь
_Bool isEmpty(struct queue *q) {
    if (q->first == NULL) {
        return true;
    } else {
        return false;
    }
}

// добавление очередного элемента в очередь
void push_back(struct queue *q, int element, unsigned int id) {
    if ((q->last == NULL) && (q->first == NULL)) {
        q->queue_count = id;
        q->last = init_list(element);
        q->first = q->last;
    } else {
        q->queue_count = id;
        q->last = addelem(q->last, element);
    }
}
// добавление очередного элемента в список
struct list *addelem(struct list *lst, int element) {
    struct list *temp, *p;
    temp = (struct list *)malloc(sizeof(struct list));
    p = lst->next;          // сохранение указателя на следующий узел
    lst->next = temp;       // предыдущий узел указывает на создаваемый
    temp->field = element;  // сохранение поля данных добавляемого узла
    temp->next = p;         // созданный узел указывает на следующий элемент
    return temp;
}

// удаление очередного элемента из очереди
int pop_front(struct queue *q) {
    struct list *temp;
    int element;
    if (isEmpty(q)) {
        printf("Очередь пуста!\n");
        return EXIT_SUCCESS;
    }
    element = q->first->field;
    temp = q->first;
    q->first = q->first->next;
    q->queue_count--;
    free(temp);
    return element;
}