/**
 * @file bfs.h
 * @brief Breadth-First Search implementation header
 * @details Defines the interface for performing breadth-first search traversal on a graph
 */

#include "graph.h"

/**
 * @brief Hash function for string values
 * @param key Pointer to string to hash
 * @return Hash value for the string
 */
unsigned long hash_string(const void* key);

/**
 * @brief Comparison function for strings
 * @param a First string to compare
 * @param b Second string to compare
 * @return Integer less than, equal to, or greater than zero if a is found,
 *         respectively, to be less than, to match, or be greater than b
 */
int compare_strings(const void* a, const void* b);

/**
 * @brief Performs breadth-first traversal of a graph
 * @param gr The graph to traverse
 * @param start Starting node for the traversal
 * @param compare Function for comparing node values
 * @param hash Function for hashing node values
 * @return NULL-terminated array of nodes in BFS order, NULL on failure
 */
void** breadth_first_visit(Graph* gr, void* start, int (*compare)(const void*, const void*), unsigned long (*hash)(const void*));