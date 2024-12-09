#include "occurances.h"

// strings hashing function
unsigned long hash_string(const void* key) {
    const char* str = (const char*)key;
    unsigned long hash = 5381;
    int c;
    while ((c = *str++))
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    return hash;
}

// compare function for strings (case-insensitive)
int compare_strings(const void* a, const void* b) {
    return strcasecmp((const char*)a, (const char*)b);
}

void clean_word(char* str) {
    int len = strlen(str);
    int cont = 0;
    unsigned char c;
    
    for (int i = 0; i < len; i++) {
        c = (unsigned char)tolower(str[i]);
        if ((c >= 'a' && c <= 'z') || c == '-' || 
            (c == 0xE2 && i + 2 < len && 
             (unsigned char)str[i+1] == 0x80 && 
             (unsigned char)str[i+2] == 0x94)) {
            str[cont] = c;
            cont++;
            
            // Skip the next two bytes of the em dash
            if (c == 0xE2) {
                str[cont] = str[i+1];
                cont++;
                str[cont] = str[i+2];
                cont++;
                i += 2;
            }
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

    FILE* log_file = fopen("word_processing.log", "w");
    if (!log_file) {
        perror("Errore nell'apertura del file di log");
        fclose(file);
        return;
    }

    HashTable* table = hash_table_create(compare_strings, hash_string);
    char word[256];
    int total_words_read = 0;
    int words_processed = 0;

    while (fscanf(file, "%255s", word) == 1) {
        total_words_read++;
        
        // Log original word before cleaning
        fprintf(log_file, "Original word: %s\n", word);

        clean_word(word);

        fprintf(log_file, "Cleaned word: %s\n", word);

        // control the string lenght 
        if (strlen(word) >= min_length) {
            words_processed++;
            
            int* count = (int*)hash_table_get(table, word);
            if (count) {
                (*count)++;
                fprintf(log_file, "Incrementing count for: %s\n", word);
            } else {
                int* new_count = malloc(sizeof(int));
                *new_count = 1;
                hash_table_put(table, strdup(word), new_count);
                fprintf(log_file, "Adding new word: %s\n", word);
            }
        } else {
            fprintf(log_file, "Word too short: %s\n", word);
        }
    }

    fclose(file);
    
    // Log summary statistics
    fprintf(log_file, "\nTotal words read: %d\n", total_words_read);
    fprintf(log_file, "Words processed: %d\n", words_processed);
    fprintf(log_file, "Hash table size: %d\n", hash_table_size(table));

    fclose(log_file);

    // Debug print of word counts
    debug_print_word_counts(table);

    // More efficient most frequent word finding
    char* most_frequent_word = NULL;
    int max_frequency = 0;
    void** keys = hash_table_keyset(table);

    for (int i = 0; i < table->size; i++) {
        char* current_word = (char*)keys[i];
        int current_count = *(int*)hash_table_get(table, current_word);
        
        if (current_count >= max_frequency) {
            max_frequency = current_count;
            most_frequent_word = current_word;
        }
    }

    free(keys);

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