#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Forward declaration
typedef struct HashNode HashNode;

// structure of the hashtable node
struct HashNode {
    void* key;
    void* value;
    struct HashNode* next;
};

// structure of hashtable
typedef struct HashTable {
    HashNode** buckets;
    int bucket_count;
    int size;
    int (*compare)(const void*, const void*);
    unsigned long (*hash)(const void*);
} HashTable;

HashTable* hash_table_create(int (*f1)(const void*,const void*), unsigned long (*f2)(const void*));
void hash_table_put(HashTable*, const void*, const void*);
void* hash_table_get(const HashTable*, const void*);
int hash_table_contains_key(const HashTable*, const void*);
void hash_table_remove(HashTable*, const void*);
int hash_table_size(const HashTable*);
void** hash_table_keyset(const HashTable*);
void hash_table_free(HashTable*);

#endif