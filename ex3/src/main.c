#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "occurances.h"

int main(int argc, char* argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Uso: %s <file> <lunghezza_minima>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char* filename = argv[1];
    size_t min_length = atoi(argv[2]);

    find_most_frequent_word(filename, min_length);

    return EXIT_SUCCESS;
}
