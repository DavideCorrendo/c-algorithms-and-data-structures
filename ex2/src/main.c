/**
 * @file main.c
 * @brief Main program for word correction using edit distance
 * @details Reads words from a dictionary file and suggests corrections for words
 *          in an input file based on edit distance calculations
 */

#include "distance.h"

/**
 * @brief Main function that implements the word correction program
 * @param argc Number of command line arguments
 * @param argv Array of command line arguments
 * @return 0 on success, 1 on error
 */
int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <dictionary.txt> <correctme.txt>\n", argv[0]);
        return 1;
    }

    const char *dictionary_file = argv[1];
    const char *correctme_file = argv[2];

    // Open and read dictionary file
    FILE *dict_fp = fopen(dictionary_file, "r");
    if (!dict_fp) {
        perror("Error opening dictionary file");
        return 1;
    }

    // Initialize dictionary array
    char **dictionary = NULL;
    int dict_size = 0;
    int max_dict_words = 1000;
    dictionary = (char **)malloc(max_dict_words * sizeof(char *));
    if (!dictionary) {
        fclose(dict_fp);
        return 1;
    }

    // Read dictionary words
    char buffer[1024];
    while (fscanf(dict_fp, "%1023s", buffer) == 1) {
        dictionary[dict_size] = strdup(buffer);
        if (!dictionary[dict_size]) {
            // Handle memory allocation failure
            for (int i = 0; i < dict_size; i++) {
                free(dictionary[i]);
            }
            free(dictionary);
            fclose(dict_fp);
            return 1;
        }
        
        dict_size++;
        if (dict_size >= max_dict_words) {
            max_dict_words *= 2;
            char **temp = (char **)realloc(dictionary, max_dict_words * sizeof(char *));
            if (!temp) {
                // Handle realloc failure
                for (int i = 0; i < dict_size; i++) {
                    free(dictionary[i]);
                }
                free(dictionary);
                fclose(dict_fp);
                return 1;
            }
            dictionary = temp;
        }
    }
    fclose(dict_fp);

    // Find maximum word length in dictionary
    int max_word_len = 10;
    for (int i = 0; i < dict_size; i++) {
        int len = strlen(dictionary[i]);
        if (len > max_word_len) max_word_len = len;
    }

    // Initialize memoization matrix
    int **memo = initialize_memo(max_word_len + 1, max_word_len + 1);
    if (!memo) {
        for (int i = 0; i < dict_size; i++) {
            free(dictionary[i]);
        }
        free(dictionary);
        return 1;
    }

    // Open and process correctme file
    FILE *correctme_fp = fopen(correctme_file, "r");
    if (!correctme_fp) {
        perror("Error opening correctme file");
        free_memo(memo, max_word_len + 1);
        for (int i = 0; i < dict_size; i++) {
            free(dictionary[i]);
        }
        free(dictionary);
        return 1;
    }

    // Process words and find corrections
    clock_t start = clock();
    while (fscanf(correctme_fp, "%1023s", buffer) == 1) {
        find_closest_words((const char **)dictionary, dict_size, buffer, memo);
    }
    clock_t end = clock();
    printf("Total processing time: %.2f seconds\n", 
           (double)(end - start) / CLOCKS_PER_SEC);

    // Cleanup
    fclose(correctme_fp);
    free_memo(memo, max_word_len + 1);
    for (int i = 0; i < dict_size; i++) {
        free(dictionary[i]);
    }
    free(dictionary);

    return 0;
}