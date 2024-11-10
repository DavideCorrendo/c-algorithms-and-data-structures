#include "unity.h"
#include "sort.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Helper function to create test record
Records** create_test_record(int id, const char* field1, int field2, float field3) {
    Records** record = malloc(sizeof(Records*));
    *record = malloc(sizeof(Records));
    (*record)->id = id;
    strncpy((*record)->field1, field1, 15);
    (*record)->field2 = field2;
    (*record)->field3 = field3;
    return record;
}

// Test records_create function
void test_records_create(void) {
    Records** records = records_create();
    TEST_ASSERT_NOT_NULL(records);
    free(records);
}

// Test compare functions
void test_compare_f1(void) {
    Records** record1 = create_test_record(1, "AAA", 10, 1.0);
    Records** record2 = create_test_record(2, "BBB", 20, 2.0);
    
    TEST_ASSERT_TRUE(compare_f1(*record1, *record2) < 0);
    TEST_ASSERT_TRUE(compare_f1(*record2, *record1) > 0);
    TEST_ASSERT_EQUAL_INT(0, compare_f1(*record1, *record1));
    
    free(*record1);
    free(record1);
    free(*record2);
    free(record2);
}

void test_compare_f2(void) {
    Records** record1 = create_test_record(1, "AAA", 10, 1.0);
    Records** record2 = create_test_record(2, "BBB", 20, 2.0);
    
    TEST_ASSERT_TRUE(compare_f2(*record1, *record2) < 0);
    TEST_ASSERT_TRUE(compare_f2(*record2, *record1) > 0);
    TEST_ASSERT_EQUAL_INT(0, compare_f2(*record1, *record1));
    
    free(*record1);
    free(record1);
    free(*record2);
    free(record2);
}

void test_compare_f3(void) {
    Records** record1 = create_test_record(1, "AAA", 10, 1.0);
    Records** record2 = create_test_record(2, "BBB", 20, 2.0);
    
    TEST_ASSERT_TRUE(compare_f3(*record1, *record2) < 0);
    TEST_ASSERT_TRUE(compare_f3(*record2, *record1) > 0);
    TEST_ASSERT_EQUAL_INT(0, compare_f3(*record1, *record1));
    
    free(*record1);
    free(record1);
    free(*record2);
    free(record2);
}

// Test merge sort
void test_merge_sort_field1(void) {
    Records** records = records_create();
    records[0] = malloc(sizeof(Records));
    records[1] = malloc(sizeof(Records));
    records[2] = malloc(sizeof(Records));
    
    // Initialize records
    records[0]->id = 1;
    strcpy(records[0]->field1, "CCC");
    records[0]->field2 = 10;
    records[0]->field3 = 1.0;
    
    records[1]->id = 2;
    strcpy(records[1]->field1, "AAA");
    records[1]->field2 = 20;
    records[1]->field3 = 2.0;
    
    records[2]->id = 3;
    strcpy(records[2]->field1, "BBB");
    records[2]->field2 = 30;
    records[2]->field3 = 3.0;
    
    merge_sort((void**)records, 3, compare_f1);
    
    TEST_ASSERT_EQUAL_STRING("AAA", records[0]->field1);
    TEST_ASSERT_EQUAL_STRING("BBB", records[1]->field1);
    TEST_ASSERT_EQUAL_STRING("CCC", records[2]->field1);
    
    for(int i = 0; i < 3; i++) {
        free(records[i]);
    }
    free(records);
}

void test_merge_sort_field2(void) {
    Records** records = records_create();
    records[0] = malloc(sizeof(Records));
    records[1] = malloc(sizeof(Records));
    records[2] = malloc(sizeof(Records));
    
    records[0]->id = 1;
    strcpy(records[0]->field1, "AAA");
    records[0]->field2 = 30;
    records[0]->field3 = 1.0;
    
    records[1]->id = 2;
    strcpy(records[1]->field1, "BBB");
    records[1]->field2 = 10;
    records[1]->field3 = 2.0;
    
    records[2]->id = 3;
    strcpy(records[2]->field1, "CCC");
    records[2]->field2 = 20;
    records[2]->field3 = 3.0;
    
    merge_sort((void**)records, 3, compare_f2);
    
    TEST_ASSERT_EQUAL_INT(10, records[0]->field2);
    TEST_ASSERT_EQUAL_INT(20, records[1]->field2);
    TEST_ASSERT_EQUAL_INT(30, records[2]->field2);
    
    for(int i = 0; i < 3; i++) {
        free(records[i]);
    }
    free(records);
}

void test_merge_sort_field3(void) {
    Records** records = records_create();
    records[0] = malloc(sizeof(Records));
    records[1] = malloc(sizeof(Records));
    records[2] = malloc(sizeof(Records));
    
    records[0]->id = 1;
    strcpy(records[0]->field1, "AAA");
    records[0]->field2 = 10;
    records[0]->field3 = 3.0;
    
    records[1]->id = 2;
    strcpy(records[1]->field1, "BBB");
    records[1]->field2 = 20;
    records[1]->field3 = 1.0;
    
    records[2]->id = 3;
    strcpy(records[2]->field1, "CCC");
    records[2]->field2 = 30;
    records[2]->field3 = 2.0;
    
    merge_sort((void**)records, 3, compare_f3);
    
    TEST_ASSERT_FLOAT_WITHIN(0.01, 1.0, records[0]->field3);
    TEST_ASSERT_FLOAT_WITHIN(0.01, 2.0, records[1]->field3);
    TEST_ASSERT_FLOAT_WITHIN(0.01, 3.0, records[2]->field3);
    
    for(int i = 0; i < 3; i++) {
        free(records[i]);
    }
    free(records);
}

// Test quick sort
void test_quick_sort_field1(void) {
    Records** records = records_create();
    records[0] = malloc(sizeof(Records));
    records[1] = malloc(sizeof(Records));
    records[2] = malloc(sizeof(Records));
    
    records[0]->id = 1;
    strcpy(records[0]->field1, "CCC");
    records[0]->field2 = 10;
    records[0]->field3 = 1.0;
    
    records[1]->id = 2;
    strcpy(records[1]->field1, "AAA");
    records[1]->field2 = 20;
    records[1]->field3 = 2.0;
    
    records[2]->id = 3;
    strcpy(records[2]->field1, "BBB");
    records[2]->field2 = 30;
    records[2]->field3 = 3.0;
    
    quick_sort((void**)records, 3, compare_f1);
    
    TEST_ASSERT_EQUAL_STRING("AAA", records[0]->field1);
    TEST_ASSERT_EQUAL_STRING("BBB", records[1]->field1);
    TEST_ASSERT_EQUAL_STRING("CCC", records[2]->field1);
    
    for(int i = 0; i < 3; i++) {
        free(records[i]);
    }
    free(records);
}

void test_quick_sort_field2(void) {
    Records** records = records_create();
    records[0] = malloc(sizeof(Records));
    records[1] = malloc(sizeof(Records));
    records[2] = malloc(sizeof(Records));
    
    records[0]->id = 1;
    strcpy(records[0]->field1, "AAA");
    records[0]->field2 = 30;
    records[0]->field3 = 1.0;
    
    records[1]->id = 2;
    strcpy(records[1]->field1, "BBB");
    records[1]->field2 = 10;
    records[1]->field3 = 2.0;
    
    records[2]->id = 3;
    strcpy(records[2]->field1, "CCC");
    records[2]->field2 = 20;
    records[2]->field3 = 3.0;
    
    quick_sort((void**)records, 3, compare_f2);
    
    TEST_ASSERT_EQUAL_INT(10, records[0]->field2);
    TEST_ASSERT_EQUAL_INT(20, records[1]->field2);
    TEST_ASSERT_EQUAL_INT(30, records[2]->field2);
    
    for(int i = 0; i < 3; i++) {
        free(records[i]);
    }
    free(records);
}

void test_quick_sort_field3(void) {
    Records** records = records_create();
    records[0] = malloc(sizeof(Records));
    records[1] = malloc(sizeof(Records));
    records[2] = malloc(sizeof(Records));
    
    records[0]->id = 1;
    strcpy(records[0]->field1, "AAA");
    records[0]->field2 = 10;
    records[0]->field3 = 3.0;
    
    records[1]->id = 2;
    strcpy(records[1]->field1, "BBB");
    records[1]->field2 = 20;
    records[1]->field3 = 1.0;
    
    records[2]->id = 3;
    strcpy(records[2]->field1, "CCC");
    records[2]->field2 = 30;
    records[2]->field3 = 2.0;
    
    quick_sort((void**)records, 3, compare_f3);
    
    TEST_ASSERT_FLOAT_WITHIN(0.01, 1.0, records[0]->field3);
    TEST_ASSERT_FLOAT_WITHIN(0.01, 2.0, records[1]->field3);
    TEST_ASSERT_FLOAT_WITHIN(0.01, 3.0, records[2]->field3);
    
    for(int i = 0; i < 3; i++) {
        free(records[i]);
    }
    free(records);
}

// Test edge cases
void test_sort_empty_array(void) {
    Records** records = records_create();
    
    // Test both sorting algorithms with empty array
    merge_sort((void**)records, 0, compare_f1);
    quick_sort((void**)records, 0, compare_f1);
    
    TEST_PASS();
    
    free(records);
}

void test_sort_single_element(void) {
    Records** records = records_create();
    records[0] = malloc(sizeof(Records));
    
    records[0]->id = 1;
    strcpy(records[0]->field1, "AAA");
    records[0]->field2 = 10;
    records[0]->field3 = 1.0;
    
    merge_sort((void**)records, 1, compare_f1);
    TEST_ASSERT_EQUAL_STRING("AAA", records[0]->field1);
    
    quick_sort((void**)records, 1, compare_f1);
    TEST_ASSERT_EQUAL_STRING("AAA", records[0]->field1);
    
    free(records[0]);
    free(records);
}

// Test file operations
void test_sort_records_file_operations(void) {
    // Create a temporary input file
    FILE* infile = fopen("test_input.txt", "w");

    fprintf(infile, "1,BBB,20,2.5\n");
    fprintf(infile, "2,AAA,10,1.5\n");
    fprintf(infile, "3,CCC,30,3.5\n");
    fclose(infile);
    
    // Open files for testing
    infile = fopen("test_input.txt", "r");
    FILE* outfile = fopen("test_output.txt", "w");
    
    TEST_ASSERT_NOT_NULL(infile);
    TEST_ASSERT_NOT_NULL(outfile);
    
    // Test sorting with different fields and algorithms
    sort_records(infile, outfile, 1, 1); // Test merge sort on field1
    
    fclose(infile);
    fclose(outfile);
    
    // Clean up temporary files
    remove("test_input.txt");
    remove("test_output.txt");
}

int main(void) {
    UNITY_BEGIN();
    
    // Basic functionality tests
    RUN_TEST(test_records_create);
    RUN_TEST(test_compare_f1);
    RUN_TEST(test_compare_f2);
    RUN_TEST(test_compare_f3);
    
    // Merge sort tests
    RUN_TEST(test_merge_sort_field1);
    RUN_TEST(test_merge_sort_field2);
    RUN_TEST(test_merge_sort_field3);
    
    // Quick sort tests
    RUN_TEST(test_quick_sort_field1);
    RUN_TEST(test_quick_sort_field2);
    RUN_TEST(test_quick_sort_field3);
    
    // Edge cases
    RUN_TEST(test_sort_empty_array);
    RUN_TEST(test_sort_single_element);
    
    // File operations test
    RUN_TEST(test_sort_records_file_operations);
    
    return UNITY_END();
}