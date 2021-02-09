#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void add_elements_in_array(void);
void print_array(int *array, unsigned int length_array);
void init_array(unsigned int start_position);
void min_elements_in_array(void);

struct ARRAY_TYPE {
    int *array;
    unsigned int length_array;
} ARRAY;

int main(int argc, char const *argv[]) {
    // another variable for struct ARRAY_TYPE
    struct ARRAY_TYPE *AARRAY;
    AARRAY->array = NULL;
    AARRAY->length_array = 0;
    // variable ARRAY
    ARRAY.length_array = 1;
    ARRAY.array = malloc(1);
    ARRAY.array[0] = 999;
    add_elements_in_array();
    print_array(ARRAY.array, ARRAY.length_array);
    min_elements_in_array();
    print_array(ARRAY.array, ARRAY.length_array);
    free(ARRAY.array);
    ARRAY.array = NULL;
    ARRAY.length_array = 0;
    return EXIT_SUCCESS;
}

void add_elements_in_array(void) {
    int start_position = ARRAY.length_array;
    int length_array = 150;
    ARRAY.array = (int *)realloc(ARRAY.array, length_array * sizeof(int));
    if (ARRAY.array != NULL) {
        ARRAY.length_array = length_array;
        init_array(start_position);
    }
}

void print_array(int *array, unsigned int length_array) {
    for (int i = 0; i < length_array; i++) {
        if (i == 0) {
            printf("[\t");
        }
        printf("%d\t", array[i]);
        if (i == length_array - 1) {
            printf("]\n");
        }
    }
}

void init_array(unsigned int start_position) {
    for (int i = start_position; i < ARRAY.length_array; i++) {
        ARRAY.array[i] = -1;
    }
}

void min_elements_in_array(void) {
    int start_position = ARRAY.length_array;
    int length_array = 1;
    ARRAY.array = (int *)realloc(ARRAY.array, length_array * sizeof(int));
    if (ARRAY.array != NULL) {
        ARRAY.length_array = length_array;
    }
}