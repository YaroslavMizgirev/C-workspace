#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct NODE {
    struct NODE *previous;
    struct NODE *next;
    char symbol;
};

struct STACK {
    unsigned int length_stack;
    struct NODE *first;
    struct NODE *last;
};

// прототипы
void init_stack(struct STACK *p_stack, unsigned int length);
_Bool isEmpty(struct STACK *p_stack);
void push_back_node(struct STACK *p_stack, char element);
char pop_back_node(struct STACK *p_stack);
_Bool isParenthesis(char symbol);
_Bool isOpenParenthesis(char symbol);
char what_last_in_stack(struct STACK *p_stack);

int main(int argc, char const *argv[]) {
    char symbol, r_symbol;
    char file_name[150];
    FILE *file_handler;
    struct STACK *p_stack;
    int length = 0;
    struct NODE *p_node;
    unsigned int error_count;
    while (true) {
        printf("Продолжить (Y/N): ");
        fflush(stdout);
        scanf("%c", &symbol);
        while (getchar() != '\n')
            ;
        if (symbol == 'y' || symbol == 'Y') {
            printf("Введите имя проверяемого файла: ");
            fflush(stdout);
            scanf("%s", file_name);
            while (getchar() != '\n')
                ;
            error_count = 0;
            file_handler = NULL;
            file_handler = fopen(file_name, "r");
            if (file_handler != NULL) {
                printf("Файл успешно открыт.\n");
                // инициализируем стек
                p_stack = (struct STACK *)malloc(sizeof(struct STACK));
                if (p_stack == NULL) {
                    printf("Ошибка: память для стека не выделилась.\n");
                    return EXIT_FAILURE;
                }
                init_stack(p_stack, length);
                // читаем файл
                while (true) {
                    r_symbol = fgetc(file_handler);
                    if (r_symbol == EOF) {
                        if (feof(file_handler)) {
                            printf("Чтение файла закончено.\n");
                            break;
                        } else {
                            printf("Ошибка чтения из файла.\n");
                            error_count++;
                            break;
                        }
                    }
                    // обрабатываем только скобки
                    if (isParenthesis(r_symbol)) {
                        // проверяем стек
                        if (isParenthesis(symbol = what_last_in_stack(p_stack))) {
                            switch (symbol) {
                                case '(':
                                    if (r_symbol == '(' || r_symbol == '[' || r_symbol == '{' || r_symbol == '<') {
                                        push_back_node(p_stack, r_symbol);
                                    } else if (r_symbol == ')') {
                                        pop_back_node(p_stack);
                                    } else {
                                        printf("incorrect\n");
                                        error_count++;
                                    }
                                    break;
                                case '[':
                                    if (r_symbol == '(' || r_symbol == '[' || r_symbol == '{' || r_symbol == '<') {
                                        push_back_node(p_stack, r_symbol);
                                    } else if (r_symbol == ']') {
                                        pop_back_node(p_stack);
                                    } else {
                                        printf("incorrect\n");
                                        error_count++;
                                    }
                                    break;
                                case '{':
                                    if (r_symbol == '(' || r_symbol == '[' || r_symbol == '{' || r_symbol == '<') {
                                        push_back_node(p_stack, r_symbol);
                                    } else if (r_symbol == '}') {
                                        pop_back_node(p_stack);
                                    } else {
                                        printf("incorrect\n");
                                        error_count++;
                                    }
                                    break;
                                case '<':
                                    if (r_symbol == '(' || r_symbol == '[' || r_symbol == '{' || r_symbol == '<') {
                                        push_back_node(p_stack, r_symbol);
                                    } else if (r_symbol == '>') {
                                        pop_back_node(p_stack);
                                    } else {
                                        printf("incorrect\n");
                                        error_count++;
                                    }
                                    break;
                            }
                        } else {
                            if (isOpenParenthesis(r_symbol)) {
                                push_back_node(p_stack, r_symbol);
                            } else {
                                printf("incorrect\n");
                                error_count++;
                            }
                        }
                    }
                    if (error_count > 0) {
                        break;
                    }
                }
                // закрываем файл
                if (fclose(file_handler) == EOF) {
                    printf("Ошибка закрытия файла.\n");
                    exit(EXIT_FAILURE);
                } else {
                    printf("Файл успешно закрыт.\n");
                }
                if (error_count == 0) {
                    printf("correct\n");
                }
            } else {
                printf("Ошибка открытия файла.\n");
            }
        } else {
            break;
        }
    }
    return EXIT_SUCCESS;
}

// инициализация стека
void init_stack(struct STACK *p_stack, unsigned int length) {
    p_stack->length_stack = length;
    p_stack->first = NULL;
    p_stack->last = NULL;
}

//проверка на пустоту стека
_Bool isEmpty(struct STACK *p_stack) {
    if (p_stack->first == NULL || p_stack->last == NULL) {
        return true;
    }
    return false;
}

// добавляем в конец
void push_back_node(struct STACK *p_stack, char element) {
    struct NODE *p_new_node;
    p_new_node = (struct NODE *)malloc(sizeof(struct NODE));
    if (isEmpty(p_stack)) {
        // NODE
        p_new_node->symbol = element;  // значение самого элемента
        p_new_node->previous = NULL;   // предыдущий элемент
        p_new_node->next = NULL;       // следующий элемент
        // STACK
        p_stack->length_stack++;      // глубина стека
        p_stack->first = p_new_node;  // начало стека
        p_stack->last = p_new_node;   // конец стека
    } else {
        // NODE
        p_new_node->symbol = element;          // значение самого элемента
        p_new_node->previous = p_stack->last;  // предыдущий элемент
        p_new_node->next = NULL;               // следующий элемент
        // STACK
        p_stack->last->next = p_new_node;  // следующий элемент
        p_stack->length_stack++;           // глубина стека
        p_stack->last = p_new_node;        // конец стека
    }
}

// убираем из конца
char pop_back_node(struct STACK *p_stack) {
    struct NODE *temp;
    char element;
    if (isEmpty(p_stack)) {
        printf("Стек пуст!\n");
        return '\0';
    }
    element = p_stack->last->symbol;
    temp = p_stack->last;
    if (p_stack->length_stack > 1) {
        p_stack->last = p_stack->last->previous;
    }
    if (p_stack->length_stack > 1) {
        p_stack->last->next = NULL;
    }
    p_stack->length_stack--;
    free(temp);
    temp = NULL;
    return element;
}

_Bool isParenthesis(char symbol) {
    if ('(' == symbol || ')' == symbol || '[' == symbol || ']' == symbol || '{' == symbol || '}' == symbol || '<' == symbol || '>' == symbol) {
        return true;
    }
    return false;
}

_Bool isOpenParenthesis(char symbol) {
    if ('(' == symbol || '[' == symbol || '{' == symbol || '<' == symbol) {
        return true;
    }
    return false;
}

char what_last_in_stack(struct STACK *p_stack) {
    if (isEmpty(p_stack)) {
        printf("Стек пуст!\n");
        return '\0';
    }
    return p_stack->last->symbol;
}
