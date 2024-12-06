#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "hashtable.h"

void debug_print_word_counts(HashTable* table);

// Funzione di hashing per stringhe
unsigned long hash_string(const void* key) {
    const char* str = (const char*)key;
    unsigned long hash = 5381;
    int c;
    while ((c = *str++))
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    return hash;
}

// Funzione di confronto per stringhe (case-insensitive)
int compare_strings(const void* a, const void* b) {
    return strcasecmp((const char*)a, (const char*)b);
}

void clean_word(char* str) {
    int len = strlen(str);
    int cont = 0;
    char c;
    
    for (int i = 0; i < len; i++) {
        c = tolower(str[i]);
        if (c >= 'a' && c <= 'z') {
            str[cont] = c;
            cont++;
        }
    }
    str[cont] = '\0';
}

void find_most_frequent_word(const char* filename, size_t min_length) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Errore nell'apertura del file");
        return;
    }

    HashTable* table = hash_table_create(compare_strings, hash_string);
    char word[256];
    while (fscanf(file, "%255s", word) == 1) {
        // Pulisce la parola prima di inserirla
        clean_word(word);

        // Controlla la lunghezza dopo la pulizia
        if (strlen(word) >= min_length) {
            int* count = (int*)hash_table_get(table, word);
            if (count) {
                (*count)++;
            } else {
                int* new_count = malloc(sizeof(int));
                *new_count = 1;
                hash_table_put(table, strdup(word), new_count);
            }
        }
    }
    fclose(file);

    // Debug print of word counts
    debug_print_word_counts(table);

    // Find most frequent word
    char* most_frequent_word = NULL;
    int max_frequency = 0;

    for (int i = 0; i < table->bucket_count; i++) {
        HashNode* node = table->buckets[i];
        while (node) {
            int current_count = *(int*)node->value;
            if (current_count > max_frequency) {
                max_frequency = current_count;
                most_frequent_word = (char*)node->key;
            }
            node = node->next;
        }
    }

    if (most_frequent_word) {
        printf("La parola più frequente con almeno %zu caratteri è '%s' con %d occorrenze.\n",
               min_length, most_frequent_word, max_frequency);
    } else {
        printf("Nessuna parola trovata con lunghezza minima di %zu caratteri.\n", min_length);
    }

    hash_table_free(table);
}

void debug_print_word_counts(HashTable* table) {
    FILE* debug_file = fopen("debug.txt", "w");
    if (debug_file == NULL) {
        perror("Errore nell'apertura del file debug.txt");
        return;
    }

    fprintf(debug_file, "Debug - Conteggio delle parole:\n");
    for (int i = 0; i < table->bucket_count; i++) {
        HashNode* node = table->buckets[i];
        while (node) {
            fprintf(debug_file, "%s: %d\n", (char*)node->key, *(int*)node->value);
            node = node->next;
        }
    }

    fclose(debug_file);
    printf("Dettagli del debug salvati in debug.txt\n");
}

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
