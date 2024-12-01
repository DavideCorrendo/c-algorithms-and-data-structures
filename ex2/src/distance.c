#include "distance.h"
#define CORRECT_WORDS 3

//function to find the minimum of 3 int numbers
int min3(int a, int b, int c) {
    int min = a;
    if (b < min) min = b;
    if (c < min) min = c;
    return min;
}

//initialilize the matrix forthe memoization
int **initialize_memo(int rows, int cols) {
    int **memo = (int **)malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; i++) {
        memo[i] = (int *)malloc(cols * sizeof(int));
        for (int j = 0; j < cols; j++) {
            memo[i][j] = -1; // Indica che il valore non è stato calcolato
        }
    }
    return memo;
}

//reset the matrix for the memoization
void reset_memo(int **memo, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            memo[i][j] = -1; // Resetta a -1
        }
    }
}

//free the matrix for the memoization
void free_memo(int **memo, int rows) {
    for (int i = 0; i < rows; i++) {
        free(memo[i]);
    }
    free(memo);
}

//wrapped function of edit_distance
int edit_distance_memo(const char *s1, const char *s2, int i, int j, int **memo) {
    //base case
    if (i == 0) return j; //if first string is empty
    if (j == 0) return i; //if second string is empty

    //avoid to make redondant calculations
    if (memo[i][j] != -1) {
        return memo[i][j];
    }


    int d_noop = (s1[i - 1] == s2[j - 1]) ? edit_distance_memo(s1, s2, i - 1, j - 1, memo) : 1 + edit_distance_memo(s1, s2, i - 1, j - 1, memo);


    int d_canc = 1 + edit_distance_memo(s1, s2, i, j - 1, memo); // Cancella in s2
    int d_ins = 1 + edit_distance_memo(s1, s2, i - 1, j, memo);  // Inserisce in s1


    memo[i][j] = min3(d_noop, d_canc, d_ins);
    return memo[i][j];
}

//recorsive function with memoization to find edit distance
int edit_distance(const char *s1, const char *s2, int **memo) {
    int len1 = strlen(s1);
    int len2 = strlen(s2);

    //reset the matrix for a new word
    reset_memo(memo, len1 + 1, len2 + 1);

    //call the wrapped function
    return edit_distance_memo(s1, s2, len1, len2, memo);
}

//find the closests words to a target word
void find_closest_words(const char *dictionary[], int dict_size, char *target, int **memo) {

    int j = 0;
    //ignore every sign of punctuation
    for (int i = 0; target[i] != '\0'; i++) {
        if (!ispunct(target[i])) {
            target[j++] = tolower(target[i]);
        }
    }
    target[j] = '\0';

    WordDistance *distances = (WordDistance *)malloc(dict_size * sizeof(WordDistance));
    int target_len = strlen(target);

    int count = 0;
    for (int i = 0; i < dict_size; i++) {
        int dict_word_len = strlen(dictionary[i]);

        //ignore dictionary word with lenght > 5
        if (abs(target_len - dict_word_len) > 3) continue;

        distances[count].word = (char *)dictionary[i];
        distances[count].distance = edit_distance(target, dictionary[i], memo);
        count++;
    }

    //sorting the word with less distances
    qsort(distances, count, sizeof(WordDistance), compare_distance);

    // print the <CORRECT_WORDS> closest words 
    printf("Parola: %s\n", target);
    for (int i = 0; i < CORRECT_WORDS; i++) {
        printf("  %s (distanza: %d)\n", distances[i].word, distances[i].distance);
    }
    printf("\n");

    free(distances);
}

//function to compare word distances(used in qsort)
int compare_distance(const void *a, const void *b) {
    return ((WordDistance *)a)->distance - ((WordDistance *)b)->distance;
}