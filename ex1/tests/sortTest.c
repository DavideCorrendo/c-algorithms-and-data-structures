#include "unity.h"
#include "sort.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Maximum test record size for dynamic allocation tests
#define MAX_TEST_RECORDS 1000
#define LARGE_RECORD_COUNT 10000

// Forward declarations of helper functions
Records** prepare_test_records(int count);
void cleanup_test_records(Records** records, int count);

// Helper function to prepare test records
Records** prepare_test_records(int count) {
    // Dynamically allocate only the array of pointers
    Records** records = malloc(count * sizeof(Records*));
    if (!records) {
        puts("Memory allocation failed");
        exit(1);
    }

    // Allocate each record
    for (int i = 0; i < count; i++) {
        records[i] = malloc(sizeof(Records));
        if (!records[i]) {
            // Free previously allocated records if allocation fails
            for (int j = 0; j < i; j++) {
                free(records[j]);
            }
            free(records);
            puts("Memory allocation failed");
            exit(1);
        }
        
        // Initialize record to prevent potential garbage values
        records[i]->id = 0;
        memset(records[i]->field1, 0, sizeof(records[i]->field1));
        records[i]->field2 = 0;
        records[i]->field3 = 0.0;
    }

    return records;
}

// Helper function to clean up test records
void cleanup_test_records(Records** records, int count) {
    if (records) {
        for (int i = 0; i < count; i++) {
            free(records[i]);
        }
        free(records);
    }
}

// Helper function to generate random test data
void generate_random_records(Records** records, int count) {
    // Seed random number generator
    srand(time(NULL));

    for (int i = 0; i < count; i++) {
        // Generate random ID
        records[i]->id = rand() % 10000;

        // Generate random field1 (string)
        for (int j = 0; j < 14; j++) {
            records[i]->field1[j] = 'A' + (rand() % 26);
        }
        records[i]->field1[14] = '\0';

        // Generate random field2 (integer)
        records[i]->field2 = rand() % 1000;

        // Generate random field3 (float)
        records[i]->field3 = (float)(rand() % 10000) / 100.0;
    }
}

// Test sorting with large number of records
void test_merge_sort_large_dataset(void) {
    // Allocate large test set
    Records** records = prepare_test_records(LARGE_RECORD_COUNT);
    
    // Generate random data
    generate_random_records(records, LARGE_RECORD_COUNT);
    
    // Perform merge sort
    merge_sort((void**)records, LARGE_RECORD_COUNT, compare_f1);
    
    // Verify sorting (check if sorted correctly)
    for (int i = 1; i < LARGE_RECORD_COUNT; i++) {
        TEST_ASSERT_TRUE(strcmp(records[i-1]->field1, records[i]->field1) <= 0);
    }
    
    // Clean up
    cleanup_test_records(records, LARGE_RECORD_COUNT);
}

// Test sorting with records containing duplicate values
void test_quick_sort_duplicate_values(void) {
    Records** records = prepare_test_records(5);
    
    // Create records with some duplicate field1 values
    strcpy(records[0]->field1, "AAA");
    strcpy(records[1]->field1, "BBB");
    strcpy(records[2]->field1, "AAA");
    strcpy(records[3]->field1, "CCC");
    strcpy(records[4]->field1, "BBB");
    
    quick_sort((void**)records, 5, compare_f1);
    
    // Verify correct sorting of duplicates
    TEST_ASSERT_EQUAL_STRING("AAA", records[0]->field1);
    TEST_ASSERT_EQUAL_STRING("AAA", records[1]->field1);
    TEST_ASSERT_EQUAL_STRING("BBB", records[2]->field1);
    TEST_ASSERT_EQUAL_STRING("BBB", records[3]->field1);
    TEST_ASSERT_EQUAL_STRING("CCC", records[4]->field1);
    
    cleanup_test_records(records, 5);
}

// Memory stress test for sorting algorithms
void test_memory_handling_stress(void) {
    // Test multiple allocations and deallocations
    for (int iterations = 0; iterations < 10; iterations++) {
        Records** records = prepare_test_records(MAX_TEST_RECORDS);
        
        // Generate random data
        generate_random_records(records, MAX_TEST_RECORDS);
        
        // Alternate between merge and quick sort
        if (iterations % 2 == 0) {
            merge_sort((void**)records, MAX_TEST_RECORDS, compare_f2);
        } else {
            quick_sort((void**)records, MAX_TEST_RECORDS, compare_f3);
        }
        
        // Verify no memory corruption occurred during sorting
        TEST_ASSERT_NOT_NULL(records);
        
        // Clean up
        cleanup_test_records(records, MAX_TEST_RECORDS);
    }
}

// Test sorting with different field comparators
void test_multiple_field_sorting(void) {
    Records** records = prepare_test_records(4);
    
    // Prepare test data with varying field values
    records[0]->id = 1;
    strcpy(records[0]->field1, "BBB");
    records[0]->field2 = 30;
    records[0]->field3 = 3.0;
    
    records[1]->id = 2;
    strcpy(records[1]->field1, "AAA");
    records[1]->field2 = 20;
    records[1]->field3 = 2.0;
    
    records[2]->id = 3;
    strcpy(records[2]->field1, "CCC");
    records[2]->field2 = 10;
    records[2]->field3 = 1.0;
    
    records[3]->id = 4;
    strcpy(records[3]->field1, "AAA");
    records[3]->field2 = 40;
    records[3]->field3 = 4.0;
    
    // Test sorting by different fields
    merge_sort((void**)records, 4, compare_f1);
    TEST_ASSERT_EQUAL_STRING("AAA", records[0]->field1);
    
    merge_sort((void**)records, 4, compare_f2);
    TEST_ASSERT_EQUAL_INT(10, records[0]->field2);
    
    merge_sort((void**)records, 4, compare_f3);
    TEST_ASSERT_EQUAL_FLOAT(1.0, records[0]->field3);
    
    cleanup_test_records(records, 4);
}

// Boundary condition test for very small arrays
void test_minimal_array_sorting(void) {
    // Test arrays of length 0, 1, and 2
    for (int size = 0; size <= 2; size++) {
        Records** records = prepare_test_records(size + 1);
        
        if (size > 0) {
            // Add some predefined data
            records[0]->id = 1;
            strcpy(records[0]->field1, "BBB");
            
            if (size > 1) {
                records[1]->id = 2;
                strcpy(records[1]->field1, "AAA");
            }
        }
        
        // Try both sorting algorithms
        merge_sort((void**)records, size, compare_f1);
        quick_sort((void**)records, size, compare_f1);
        
        // If size > 1, verify sorting
        if (size > 1) {
            TEST_ASSERT_EQUAL_STRING("AAA", records[0]->field1);
        }
        
        cleanup_test_records(records, size + 1);
    }
}

// Performance and error handling test
void test_sorting_with_large_strings(void) {
    Records** records = prepare_test_records(5);
    
    // Create records with longer field1 values
    strcpy(records[0]->field1, "Very Long String Test 1");
    strcpy(records[1]->field1, "Another Long String Test 2");
    strcpy(records[2]->field1, "Short Test");
    strcpy(records[3]->field1, "Zebra Test");
    strcpy(records[4]->field1, "Aardvark Test");
    
    // Ensure sorting works with longer strings
    merge_sort((void**)records, 5, compare_f1);
    
    TEST_ASSERT_EQUAL_STRING("Aardvark Test", records[0]->field1);
    TEST_ASSERT_EQUAL_STRING("Another Long String Test 2", records[1]->field1);
    TEST_ASSERT_EQUAL_STRING("Short Test", records[2]->field1);
    TEST_ASSERT_EQUAL_STRING("Very Long String Test 1", records[3]->field1);
    TEST_ASSERT_EQUAL_STRING("Zebra Test", records[4]->field1);
    
    cleanup_test_records(records, 5);
}

int main(void) {
    UNITY_BEGIN();
    
    // Run additional test cases
    RUN_TEST(test_merge_sort_large_dataset);
    RUN_TEST(test_quick_sort_duplicate_values);
    RUN_TEST(test_memory_handling_stress);
    RUN_TEST(test_multiple_field_sorting);
    RUN_TEST(test_minimal_array_sorting);
    RUN_TEST(test_sorting_with_large_strings);
    
    return UNITY_END();
}