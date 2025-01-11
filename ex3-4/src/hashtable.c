/**
 * @file hashtable.c
 * @brief Implementation of a generic hash table data structure
 * @details This file contains the implementation of a hash table that supports
 * generic key-value pairs using void pointers. The hash table uses chaining
 * for collision resolution.
 */

#include "hashtable.h"

/**
 * @brief Creates a new hash table
 * @param compare Function pointer to compare two keys
 * @param hash Function pointer to generate hash value for a key
 * @return Pointer to the newly created hash table, or NULL if allocation fails
 * @details Initializes a hash table with a default size of 16 buckets. The compare
 * and hash functions must be provided by the caller for proper key management.
 */
HashTable* hash_table_create(int (*compare)(const void*, const void*), unsigned long (*hash)(const void*)) {
    int initial_bucket_count = 16;
    HashTable* table = (HashTable*)malloc(sizeof(HashTable));
    table->buckets = (HashNode**)calloc(initial_bucket_count, sizeof(HashNode*));
    table->bucket_count = initial_bucket_count;
    table->size = 0;
    table->compare = compare;
    table->hash = hash;
    return table;
}

/**
 * @brief Inserts or updates a key-value pair in the hash table
 * @param table Pointer to the hash table
 * @param key Pointer to the key
 * @param value Pointer to the value
 * @details If the key already exists, its value is updated. Otherwise, a new
 * key-value pair is inserted into the appropriate bucket. The function handles
 * collisions using chaining.
 */
void hash_table_put(HashTable* table, const void* key, const void* value) {
    unsigned long hash_value = table->hash(key) % table->bucket_count;
    
    HashNode* current = table->buckets[hash_value];
    while (current) {
        if (table->compare(current->key, key) == 0) {
            current->value = (void*)value;
            return;
        }
        current = current->next;
    }
    
    HashNode* new_node = (HashNode*)malloc(sizeof(HashNode));
    new_node->key = (void*)key;
    new_node->value = (void*)value;
    
    new_node->next = table->buckets[hash_value];
    table->buckets[hash_value] = new_node;
    table->size++;
}

/**
 * @brief Retrieves the value associated with a given key
 * @param table Pointer to the hash table
 * @param key Pointer to the key to look up
 * @return Pointer to the value if found, NULL otherwise
 * @details Searches the appropriate bucket for the key and returns its associated
 * value. Returns NULL if the key is not found in the table.
 */
void* hash_table_get(const HashTable* table, const void* key) {
    unsigned long hash_value = table->hash(key) % table->bucket_count;
    HashNode* current = table->buckets[hash_value];
    while (current) {
        if (table->compare(current->key, key) == 0) {
            return current->value;
        }
        current = current->next;
    }
    return NULL;
}

/**
 * @brief Checks if a key exists in the hash table
 * @param table Pointer to the hash table
 * @param key Pointer to the key to check
 * @return 1 if the key exists, 0 otherwise
 */
int hash_table_contains_key(const HashTable* table, const void* key) {
    return hash_table_get(table, key) != NULL;
}

/**
 * @brief Removes a key-value pair from the hash table
 * @param table Pointer to the hash table
 * @param key Pointer to the key to remove
 * @details Removes the node containing the specified key and its associated value.
 * If the key is not found, the function does nothing.
 */
void hash_table_remove(HashTable* table, const void* key) {
    unsigned long hash_value = table->hash(key) % table->bucket_count;
    HashNode* current = table->buckets[hash_value];
    HashNode* prev = NULL;
    
    while (current) {
        if (table->compare(current->key, key) == 0) {
            if (prev) {
                prev->next = current->next;
            } else {
                table->buckets[hash_value] = current->next;
            }
            free(current);
            table->size--;
            return;
        }
        prev = current;
        current = current->next;
    }
}

/**
 * @brief Returns the number of key-value pairs in the hash table
 * @param table Pointer to the hash table
 * @return Number of entries in the table
 */
int hash_table_size(const HashTable* table) {
    return table->size;
}

/**
 * @brief Returns an array of all keys in the hash table
 * @param table Pointer to the hash table
 * @return NULL-terminated array of pointers to all keys
 * @details Allocates and returns a new array containing pointers to all keys
 * in the table. The caller is responsible for freeing the returned array.
 */
void** hash_table_keyset(const HashTable* table) {
    void** keys = (void**)malloc((table->size + 1) * sizeof(void*));
    int index = 0;
    
    for (int i = 0; i < table->bucket_count; i++) {
        HashNode* current = table->buckets[i];
        while (current) {
            keys[index++] = current->key;
            current = current->next;
        }
    }
    keys[table->size] = NULL;
    return keys;
}

/**
 * @brief Frees all memory associated with the hash table
 * @param table Pointer to the hash table to free
 * @details Frees all nodes, buckets, and the table structure itself.
 * Does not free the memory of stored keys and values as they might be
 * used elsewhere.
 */
void hash_table_free(HashTable* table) {
    if (!table) return;

    for (int i = 0; i < table->bucket_count; i++) {
        HashNode* current = table->buckets[i];
        while (current) {
            HashNode* temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(table->buckets);
    free(table);
}