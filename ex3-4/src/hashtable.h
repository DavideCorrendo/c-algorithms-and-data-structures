/**
 * @file hashtable.h
 * @brief Hash table implementation header
 * @details Defines the interface for a generic hash table data structure
 */

#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Forward declaration
typedef struct HashNode HashNode;

/**
 * @struct HashNode
 * @brief Node structure for hash table entries
 */
struct HashNode {
    void* key;    /**< Key of the hash table entry */
    void* value;  /**< Value associated with the key */
    struct HashNode* next;  /**< Pointer to next node in case of collision */
};

/**
 * @struct HashTable
 * @brief Hash table structure
 */
typedef struct HashTable {
    HashNode** buckets;     /**< Array of bucket pointers */
    int bucket_count;       /**< Number of buckets in the table */
    int size;              /**< Number of elements in the table */
    int (*compare)(const void*, const void*);  /**< Function pointer for comparing keys */
    unsigned long (*hash)(const void*);        /**< Function pointer for hashing keys */
} HashTable;

/**
 * @brief Creates a new hash table
 * @param f1 Comparison function for keys
 * @param f2 Hash function for keys
 * @return Pointer to the created hash table, NULL on failure
 */
HashTable* hash_table_create(int (*f1)(const void*,const void*), unsigned long (*f2)(const void*));

/**
 * @brief Inserts or updates a key-value pair in the hash table
 * @param table The hash table
 * @param key The key to insert
 * @param value The value to associate with the key
 */
void hash_table_put(HashTable*, const void*, const void*);

/**
 * @brief Retrieves the value associated with a key
 * @param table The hash table
 * @param key The key to look up
 * @return The associated value, or NULL if key not found
 */
void* hash_table_get(const HashTable*, const void*);

/**
 * @brief Checks if a key exists in the hash table
 * @param table The hash table
 * @param key The key to check
 * @return 1 if key exists, 0 otherwise
 */
int hash_table_contains_key(const HashTable*, const void*);

/**
 * @brief Removes a key-value pair from the hash table
 * @param table The hash table
 * @param key The key to remove
 */
void hash_table_remove(HashTable*, const void*);

/**
 * @brief Returns the number of elements in the hash table
 * @param table The hash table
 * @return Number of elements in the table
 */
int hash_table_size(const HashTable*);

/**
 * @brief Returns an array of all keys in the hash table
 * @param table The hash table
 * @return NULL-terminated array of keys
 */
void** hash_table_keyset(const HashTable*);

/**
 * @brief Frees all memory associated with the hash table
 * @param table The hash table to free
 */
void hash_table_free(HashTable*);

#endif