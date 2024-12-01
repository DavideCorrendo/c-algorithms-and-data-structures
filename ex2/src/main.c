#include "distance.h"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Uso: %s <dictionary.txt> <correctme.txt>\n", argv[0]);
        return 1;
    }

    const char *dictionary_file = argv[1];
    const char *correctme_file = argv[2];

    // Leggi il dizionario
    FILE *dict_fp = fopen(dictionary_file, "r");
    if (!dict_fp) {
        perror("Errore nell'apertura del file dictionary.txt");
        return 1;
    }

    char **dictionary = NULL;
    int dict_size = 0;
    int max_dict_words = 1000;
    dictionary = (char **)malloc(max_dict_words * sizeof(char *));
    char buffer[1024];

    while (fscanf(dict_fp, "%1023s", buffer) == 1) {
        dictionary[dict_size] = strdup(buffer);
        dict_size++;
        if (dict_size >= max_dict_words) {
            max_dict_words *= 2;
            dictionary = (char **)realloc(dictionary, max_dict_words * sizeof(char *));
        }
    }
    fclose(dict_fp);

    // Determina la lunghezza massima di una parola
    int max_word_len = 10;
    for (int i = 0; i < dict_size; i++) {
        int len = strlen(dictionary[i]);
        if (len > max_word_len) max_word_len = len;
    }

    // Inizializza la matrice di memoizzazione
    int **memo = initialize_memo(max_word_len + 1, max_word_len + 1);

    // Leggi il file correctme.txt
    FILE *correctme_fp = fopen(correctme_file, "r");
    if (!correctme_fp) {
        perror("Errore nell'apertura del file correctme.txt");
        free_memo(memo, max_word_len + 1);
        for (int i = 0; i < dict_size; i++){free(dictionary[i]);}
        free(dictionary);
        return 1;
    }

    while (fscanf(correctme_fp, "%1023s", buffer) == 1) {
        find_closest_words((const char **)dictionary, dict_size, buffer, memo);
    }
    fclose(correctme_fp);

    // Libera la memoria
    free_memo(memo, max_word_len + 1);
    for (int i = 0; i < dict_size; i++){free(dictionary[i]);}
    free(dictionary);

    return 0;
}
