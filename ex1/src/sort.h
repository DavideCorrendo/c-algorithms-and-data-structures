/**
 * @file sort.h
 * @brief Header file for sorting algorithms
 * @details Contains declarations for sorting functions and record management
 */

#ifndef SORTING_H
#define SORTING_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>

/**
 * @struct _Records
 * @brief Structure for storing multi-field records
 */
typedef struct _Records Records;

struct _Records{
    int     id;         /**< Record identifier */
    char    field1[15]; /**< String field */
    int     field2;     /**< Integer field */
    float   field3;     /**< Float field */
};

/**
 * @brief Creates an array of Record structures
 * @return Pointer to array of Record pointers
 * @throws Exit with code 1 if memory allocation fails
 */
Records** records_create();

/**
 * @brief Frees memory allocated for Records array
 * @param records Array of Record pointers to free
 */
void free_records(Records **records);

/**
 * @brief Compares two records by field1 (string)
 * @param a First record
 * @param b Second record
 * @return Comparison result (-1, 0, or 1)
 */
int compare_f1(const void *a, const void *b);

/**
 * @brief Compares two records by field2 (integer)
 * @param a First record
 * @param b Second record
 * @return Difference between field2 values
 */
int compare_f2(const void *a, const void *b);

/**
 * @brief Compares two records by field3 (float)
 * @param a First record
 * @param b Second record
 * @return -1 if a<b, 0 if equal, 1 if a>b
 */
int compare_f3(const void *a, const void *b);

/**
 * @brief Main sorting function
 * @param infile Input file pointer
 * @param outfile Output file pointer
 * @param field Field to sort by (1-3)
 * @param algo Algorithm choice (1=merge, 2=quick)
 */
void sort_records(FILE *infile, FILE *outfile, size_t field, size_t algo);

/**
 * @brief Merges two sorted subarrays
 * @param base Array containing elements
 * @param first Start index
 * @param mid Middle index
 * @param last End index
 * @param compar Comparison function
 */
void merge(void **base, int first, int mid, int last, int (*compar)(const void *, const void*));

/**
 * @brief Recursive merge sort function
 * @param base Array to sort
 * @param first Start index
 * @param last End index
 * @param compar Comparison function
 */
void merge_sort_rec(void **base, int first, int last, int (*compar)(const void *, const void*));

/**
 * @brief Merge sort wrapper with timing
 * @param base Array to sort
 * @param nitems Number of items
 * @param compar Comparison function
 */
void merge_sort(void** base, int nitems, int (*compar)(const void*, const void*));

/**
 * @brief Swaps two elements
 * @param a First element
 * @param b Second element
 */
void swap(void **a, void**b);

/**
 * @brief Partitions array for quicksort
 * @param base Array to partition
 * @param left Start index
 * @param right End index
 * @param compar Comparison function
 * @return Partition position
 */
int partition(void **base, int left, int right, int (*compar)(const void*, const void*));

/**
 * @brief Recursive quicksort function
 * @param base Array to sort
 * @param left Start index
 * @param right End index
 * @param compar Comparison function
 */
void quick_sort_rec(void **base, int left, int right, int (*compar)(const void*, const void*));

/**
 * @brief Quicksort wrapper with timing
 * @param base Array to sort
 * @param nitems Number of items
 * @param compar Comparison function
 */
void quick_sort(void **base, size_t nitems, int (*compar)(const void*, const void*));

#endif