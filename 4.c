#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// prototypes
unsigned int return_next_index_position(char *p_str, unsigned int i);

int main(int argc, char const *argv[]) {
    char source_string[150];
    char new_string[2];
    int unique_symbols, length_source_string;
    char symbol;
    unsigned int i;
    while (true) {
        printf("Продолжить (Y/N): ");
        fflush(stdout);
        scanf("%c", &symbol);
        while (getchar() != '\n')
            ;
        if (symbol == 'y' || symbol == 'Y') {
            printf("Введите строку: ");
            fflush(stdout);
            scanf("%s", source_string);
            while (getchar() != '\n')
                ;
            length_source_string = strlen(source_string);
            unique_symbols = 0;
            i = 0;
            while (i < length_source_string) {
                unique_symbols++;
                i = return_next_index_position(source_string, i);
            }
            printf("%d уникальных символов в строке.\n", unique_symbols);
            char *target_string = NULL;
            target_string = (char *)realloc(target_string, unique_symbols * sizeof(char));
            i = 0;
            while (i < length_source_string) {
                new_string[0] = source_string[i];
                new_string[1] = '\0';
                strcat(target_string, new_string);
                i = return_next_index_position(source_string, i);
            }
            printf("Результат: %s.\n", target_string);
        } else {
            break;
        }
    }
    return EXIT_SUCCESS;
}

unsigned int return_next_index_position(char *p_str, unsigned int i) {
    unsigned int tempI = i;
    char symbol = *(p_str + i);
    while (symbol == *(p_str + tempI)) {
        tempI++;
    }
    return tempI;
}
