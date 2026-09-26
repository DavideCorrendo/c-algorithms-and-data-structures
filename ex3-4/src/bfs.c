/**
 * @file bfs.c
 * @brief Implementation of Breadth-First Search algorithm for graphs
 * @details This file contains the implementation of a breadth-first search
 * algorithm that can be used with any graph implementation that provides
 * the required interface.
 */

#include "bfs.h"
#include <string.h>
#include <stdlib.h>

/**
 * @brief Performs a breadth-first search traversal of a graph
 * @param gr Pointer to the graph structure
 * @param start Pointer to the starting node
 * @param compare Function pointer to compare two nodes
 * @param hash Function pointer to generate hash value for a node
 * @return NULL-terminated array of pointers to visited nodes in BFS order,
 *         or NULL if an error occurs
 * @details Implements the breadth-first search algorithm using a queue.
 * The function measures and prints the execution time. The returned array
 * must be freed by the caller.
 * 
 * @note The hash parameter is used for compatibility with the graph interface
 * but is not essential for the BFS algorithm itself.
 */
void** breadth_first_visit(Graph gr, void* start, int (*compare)(const void*, const void*), unsigned long (*hash)(const void*)) {
    clock_t from = clock();
    if (!gr || !start) return NULL;

    int num_nodes = graph_num_nodes(gr);
    void** visited_array = malloc((num_nodes + 1) * sizeof(void*));
    void** queue = malloc((num_nodes + 1) * sizeof(void*));
    
    if (!visited_array || !queue) {
        free(visited_array);
        free(queue);
        return NULL;
    }
    
    HashTable* visited_map = hash_table_create(compare, hash);
    if (!visited_map) {
        free(visited_array);
        free(queue);
        return NULL;
    }

    int visited_count = 0;
    int queue_front = 0, queue_rear = 0;

    queue[queue_rear++] = start;
    visited_array[visited_count++] = start;
    hash_table_put(visited_map, start, (void*)1);

    while (queue_front < queue_rear) {
        void* current = queue[queue_front++];
        void** neighbors = graph_get_neighbours(gr, current);
        
        if (neighbors) {
            for (int i = 0; neighbors[i] != NULL; i++) {
                if (!hash_table_contains_key(visited_map, neighbors[i])) {
                    hash_table_put(visited_map, neighbors[i], (void*)1);
                    queue[queue_rear++] = neighbors[i];
                    visited_array[visited_count++] = neighbors[i];
                }
            }
            free(neighbors);
        }
    }

    visited_array[visited_count] = NULL;
    
    free(queue);
    hash_table_free(visited_map);

    clock_t to = clock();
    double time_taken = (double)(to - from) / CLOCKS_PER_SEC;
    printf("The time taken by the breadth_first_visit is: %f sec\n", time_taken);

    return visited_array;
}