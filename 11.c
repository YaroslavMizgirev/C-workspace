#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[]) {
    char symbol;
    FILE *file_handler, *out_file_handler;
    char file_name[150];
    char out_file_name[150];
    size_t hasDigit, hasAlpha, hasOther, lineCount;
    if (argc > 1 && strlen(argv[1]) > 3) {
        strcpy(out_file_name, argv[1]);
        printf("Открываем файл: '%s'.\n", out_file_name);
        if ((out_file_handler = fopen(out_file_name, "a+")) != NULL) {
            printf("Введите абсолютный путь файла для расчетов: ");
            fflush(stdout);
            scanf("%[^\n]", file_name);
            if (strlen(file_name) > 0) {
                printf("Открываем файл: '%s'.\n", file_name);
                if ((file_handler = fopen(file_name, "r")) != NULL) {
                    lineCount = 0;  // счетчик строк
                    hasDigit = 0;   // счетчик цифр
                    hasAlpha = 0;   // счетчик букв
                    hasOther = 0;   // счетчик прочих символов
                    while (true) {
                        if ((symbol = fgetc(file_handler)) == EOF) {
                            if (feof(file_handler)) {
                                printf("Конец файла.\n");
                                break;
                            } else {
                                printf("Ошибка чтения файла.\n");
                                break;
                            }
                        }
                        switch (symbol) {
                            case '\n':
                                fprintf(out_file_handler, "В строке №%d: <%d> <%d> <%d>\n", lineCount + 1, hasDigit, hasAlpha, hasOther);
                                hasAlpha = 0;
                                hasDigit = 0;
                                hasOther = 0;
                                lineCount++;
                                break;
                            default:
                                if (isdigit(symbol)) {
                                    hasDigit++;
                                } else if (isalpha(symbol)) {
                                    hasAlpha++;
                                } else {
                                    hasOther++;
                                }
                                break;
                        }
                    }
                    if (fclose(file_handler) == EOF) {
                        printf("Ошибка закрытия файла '%s'.\n", file_name);
                        exit(EXIT_FAILURE);
                    } else {
                        printf("Файл '%s' успешно закрыт.\n", file_name);
                    }
                } else {
                    printf("Ошибка открытия файла '%s'.\n", file_name);
                }
            }
            if (fclose(out_file_handler) == EOF) {
                printf("Ошибка закрытия файла '%s'.\n", out_file_name);
                exit(EXIT_FAILURE);
            } else {
                printf("Файл '%s' успешно закрыт.\n", out_file_name);
            }
        } else {
            printf("Ошибка открытия файла '%s'.\n", out_file_name);
        }
    } else {
        printf("Введите параметром абсолютный путь файла для сохранения результатов вычислений.\n");
    }
    return EXIT_SUCCESS;
}
