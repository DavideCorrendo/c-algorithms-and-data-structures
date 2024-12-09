#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "hashtable.h"

unsigned long hash_string(const void *);
int compare_strings(const void *, const void *);
void clean_word(char *);
void find_most_frequent_word(const char *, size_t);
void debug_print_word_counts(HashTable *);