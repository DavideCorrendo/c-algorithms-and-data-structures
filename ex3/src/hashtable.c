#include "hashtable.h"

// create a new hash table
HashTable* hash_table_create(int (*compare)(const void*, const void*), unsigned long (*hash)(const void*)) {
    int initial_bucket_count = 16; // Numero iniziale di bucket
    HashTable* table = (HashTable*)malloc(sizeof(HashTable));
    table->buckets = (HashNode**)calloc(initial_bucket_count, sizeof(HashNode*));
    table->bucket_count = initial_bucket_count;
    table->size = 0;
    table->compare = compare;
    table->hash = hash;
    return table;
}

void hash_table_put(HashTable* table, const void* key, const void* value) {
    // Calculate the bucket index directly
    unsigned long hash_value = table->hash(key) % table->bucket_count;
    
    // Create a new node for insertion
    HashNode* new_node = (HashNode*)malloc(sizeof(HashNode));
    new_node->key = (void*)key;
    new_node->value = (void*)value;
    
    // Insert at the beginning of the bucket's linked list
    new_node->next = table->buckets[hash_value];
    table->buckets[hash_value] = new_node;
    
    // Increment the table size
    table->size++;
}

// get the value associated to a key
void* hash_table_get(const HashTable* table, const void* key) {
    unsigned long hash_value = table->hash(key) % table->bucket_count;
    HashNode* current = table->buckets[hash_value];
    while (current) {
        if (table->compare(current->key, key) == 0) {
            return current->value;
        }
        current = current->next;
    }
    return NULL; // key not found
}

// verify if a key is present in a table
int hash_table_contains_key(const HashTable* table, const void* key) {
    return hash_table_get(table, key) != NULL;
}

// remove a key from a table
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

// return the size of the table
int hash_table_size(const HashTable* table) {
    return table->size;
}

// return a key array
void** hash_table_keyset(const HashTable* table) {
    void** keys = (void**)malloc(table->size * sizeof(void*));
    int index = 0;
    for (int i = 0; i < table->bucket_count; i++) {
        HashNode* current = table->buckets[i];
        while (current) {
            keys[index++] = current->key;
            current = current->next;
        }
    }
    return keys;
}

void hash_table_free(HashTable* table) {
    for (int i = 0; i < table->bucket_count; i++) {
        HashNode* current = table->buckets[i];
        while (current) {
            HashNode* temp = current;
            current = current->next;

            // free separately key and value
            free(temp->key);   
            free(temp->value); 
            free(temp);
        }
    }
    free(table->buckets);
    free(table);
}