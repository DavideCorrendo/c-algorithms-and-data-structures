/**
 * @file distance.c
 * @brief Implementation of edit distance calculation and word matching functions
 */

#include "distance.h"
#define CORRECT_WORDS 5

int min3(int a, int b, int c) {
    int min = a;
    if (b < min) min = b;
    if (c < min) min = c;
    return min;
}

int **initialize_memo(int rows, int cols) {
    int **memo = (int **)malloc(rows * sizeof(int *));
    if (!memo) return NULL;

    for (int i = 0; i < rows; i++) {
        memo[i] = (int *)malloc(cols * sizeof(int));
        if (!memo[i]) {
            // Clean up previously allocated memory
            for (int j = 0; j < i; j++) {
                free(memo[j]);
            }
            free(memo);
            return NULL;
        }
        for (int j = 0; j < cols; j++) {
            memo[i][j] = -1;
        }
    }
    return memo;
}

void reset_memo(int **memo, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            memo[i][j] = -1;
        }
    }
}

void free_memo(int **memo, int rows) {
    if (!memo) return;
    
    for (int i = 0; i < rows; i++) {
        free(memo[i]);
    }
    free(memo);
}

/**
 * @brief Helper function for edit_distance with memoization
 * @param s1 First string
 * @param s2 Second string
 * @param i Length of first string being considered
 * @param j Length of second string being considered
 * @param memo Memoization matrix
 * @return Edit distance between s1[0..i-1] and s2[0..j-1]
 */
static int edit_distance_memo(const char *s1, const char *s2, int i, int j, int **memo) {
    if (i == 0) return j;
    if (j == 0) return i;

    if (memo[i][j] != -1) {
        return memo[i][j];
    }

    int d_noop = INT_MAX;
    if (s1[i - 1] == s2[j - 1]) {
        d_noop = edit_distance_memo(s1, s2, i - 1, j - 1, memo);
    }
    
    int d_canc = 1 + edit_distance_memo(s1, s2, i, j - 1, memo);
    int d_ins = 1 + edit_distance_memo(s1, s2, i - 1, j, memo);

    memo[i][j] = min3(d_noop, d_canc, d_ins);
    return memo[i][j];
}

int edit_distance(const char *s1, const char *s2) {
    if (strlen(s1) == 0) return strlen(s2);
    if (strlen(s2) == 0) return strlen(s1);
    
    int d_noop = INT_MAX;
    if (s1[0] == s2[0]) {
        d_noop = edit_distance(s1 + 1, s2 + 1);
    }
    int d_canc = 1 + edit_distance(s1, s2 + 1);
    int d_ins = 1 + edit_distance(s1 + 1, s2);
    
    return min3(d_noop, d_canc, d_ins);
}

int edit_distance_dyn(const char *s1, const char *s2) {
    int len1 = strlen(s1);
    int len2 = strlen(s2);
    int **memo = initialize_memo(len1 + 1, len2 + 1);
    
    int result = edit_distance_memo(s1, s2, len1, len2, memo);
    
    free_memo(memo, len1 + 1);
    return result;
}   

void find_closest_words(const char *dictionary[], int dict_size, char *target) {
    clock_t start = clock();

    // Remove punctuation and convert to lowercase
    int j = 0;
    for (int i = 0; i < dict_size; i++) {
        int dict_word_len = strlen(dictionary[i]);
        if (abs(target_len - dict_word_len) > 3) continue;

        distances[count].word = (char *)dictionary[i];
        distances[count].distance = edit_distance(target, dictionary[i], memo);
        count++;
    }
    target[j] = '\0';

    WordDistance *distances = (WordDistance *)malloc(dict_size * sizeof(WordDistance));
    if (!distances) return;

    int target_len = strlen(target);
    int count = 0;

    // Calculate distances for words within acceptable length difference
    for (int i = 0; i < dict_size; i++) {
        int dict_word_len = strlen(dictionary[i]);
        if (abs(target_len - dict_word_len) > 3) continue;

        distances[count].word = (char *)dictionary[i];
        distances[count].distance = edit_distance(target, dictionary[i], memo);
        count++;
    }

    qsort(distances, count, sizeof(WordDistance), compare_distance);

    printf("Word: %s\n", target);
    for (int i = 0; i < CORRECT_WORDS && i < count; i++) {
        printf("  %s (distance: %d)\n", distances[i].word, distances[i].distance);
    }

    free(distances);

    clock_t end = clock();
    printf("Time taken: %.4f seconds\n\n", 
           (double)(end - start) / CLOCKS_PER_SEC);
}

int compare_distance(const void *a, const void *b) {
    return ((WordDistance *)a)->distance - ((WordDistance *)b)->distance;
}