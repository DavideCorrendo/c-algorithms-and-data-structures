/**
 * @file distance.h
 * @brief Header file containing declarations for edit distance calculation and word matching
 * @details This module provides functionality to find similar words based on edit distance
 */

#ifndef DISTANCE_H
#define DISTANCE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>
#include <time.h>

/**
 * @struct WordDistance
 * @brief Structure to store a word and its edit distance from a target word
 */
typedef struct {
    char *word;      /**< The dictionary word */
    int distance;    /**< Edit distance from the target word */
} WordDistance;

/**
 * @brief Finds the minimum value among three integers
 * @param a First integer
 * @param b Second integer
 * @param c Third integer
 * @return The minimum value among a, b, and c
 */
int min3(int a, int b, int c);

/**
 * @brief Initializes the memoization matrix
 * @param rows Number of rows in the matrix
 * @param cols Number of columns in the matrix
 * @return Pointer to the initialized memoization matrix
 */
int **initialize_memo(int rows, int cols);

/**
 * @brief Resets all values in the memoization matrix to -1
 * @param memo The memoization matrix
 * @param rows Number of rows in the matrix
 * @param cols Number of columns in the matrix
 */
void reset_memo(int **memo, int rows, int cols);

/**
 * @brief Frees the memory allocated for the memoization matrix
 * @param memo The memoization matrix
 * @param rows Number of rows in the matrix
 */
void free_memo(int **memo, int rows);

/**
 * @brief Calculates the edit distance between two strings
 * @param s1 First string
 * @param s2 Second string
 * @param memo Memoization matrix
 * @return Edit distance between s1 and s2
 */
int edit_distance(const char *s1, const char *s2, int **memo);

/**
 * @brief Comparison function for qsort to sort WordDistance structures
 * @param a Pointer to first WordDistance structure
 * @param b Pointer to second WordDistance structure
 * @return Difference between distances
 */
int compare_distance(const void *a, const void *b);

/**
 * @brief Finds the closest matching words for a given target word
 * @param dictionary Array of dictionary words
 * @param dict_size Size of the dictionary
 * @param target Target word to find matches for
 * @param memo Memoization matrix
 */
void find_closest_words(const char **dictionary, int dict_size, char *target, int **memo);

#endif