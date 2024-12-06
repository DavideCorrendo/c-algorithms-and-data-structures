// File: test_hashtable.c
#include "unity.h"
#include "../src/hashtable.h"
#include <string.h>
#include <stdlib.h>

// Utility function for string comparison
int test_compare_strings(const void* a, const void* b) {
    return strcmp((const char*)a, (const char*)b);
}

// Utility function for hashing strings
unsigned long test_hash_string(const void* key) {
    const char* str = (const char*)key;
    unsigned long hash = 5381;
    int c;
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash;
}

// Setup and Teardown (if necessary)
void setUp(void) {}
void tearDown(void) {}

// Test hash_table_create
void test_hash_table_create(void) {
    HashTable* table = hash_table_create(test_compare_strings, test_hash_string);
    TEST_ASSERT_NOT_NULL(table);
    TEST_ASSERT_EQUAL(0, hash_table_size(table));
    hash_table_free(table);
}

// Test hash_table_put and hash_table_get
void test_hash_table_put_get(void) {
    HashTable* table = hash_table_create(test_compare_strings, test_hash_string);
    const char* key = "key1";
    const char* value = "value1";
    hash_table_put(table, key, value);
    TEST_ASSERT_EQUAL_STRING(value, (char*)hash_table_get(table, key));
    hash_table_free(table);
}

// Test hash_table_contains_key
void test_hash_table_contains_key(void) {
    HashTable* table = hash_table_create(test_compare_strings, test_hash_string);
    const char* key = "key1";
    hash_table_put(table, key, "value1");
    TEST_ASSERT_TRUE(hash_table_contains_key(table, key));
    TEST_ASSERT_FALSE(hash_table_contains_key(table, "nonexistent"));
    hash_table_free(table);
}

// Test hash_table_remove
void test_hash_table_remove(void) {
    HashTable* table = hash_table_create(test_compare_strings, test_hash_string);
    const char* key = "key1";
    hash_table_put(table, key, "value1");
    hash_table_remove(table, key);
    TEST_ASSERT_FALSE(hash_table_contains_key(table, key));
    hash_table_free(table);
}

// Test hash_table_size
void test_hash_table_size(void) {
    HashTable* table = hash_table_create(test_compare_strings, test_hash_string);
    hash_table_put(table, "key1", "value1");
    hash_table_put(table, "key2", "value2");
    TEST_ASSERT_EQUAL(2, hash_table_size(table));
    hash_table_remove(table, "key1");
    TEST_ASSERT_EQUAL(1, hash_table_size(table));
    hash_table_free(table);
}

// Test hash_table_keyset
void test_hash_table_keyset(void) {
    HashTable* table = hash_table_create(test_compare_strings, test_hash_string);
    hash_table_put(table, "key1", "value1");
    hash_table_put(table, "key2", "value2");
    void** keys = hash_table_keyset(table);
    TEST_ASSERT_NOT_NULL(keys);
    free(keys);
    hash_table_free(table);
}

// Main entry for Unity tests
int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_hash_table_create);
    RUN_TEST(test_hash_table_put_get);
    RUN_TEST(test_hash_table_contains_key);
    RUN_TEST(test_hash_table_remove);
    RUN_TEST(test_hash_table_size);
    RUN_TEST(test_hash_table_keyset);
    return UNITY_END();
}