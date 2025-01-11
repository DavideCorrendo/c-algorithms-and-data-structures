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
void** breadth_first_visit(Graph* gr, void* start, int (*compare)(const void*, const void*), unsigned long (*hash)(const void*)) {
    clock_t from = clock();

    hash(start); // Used for interface compatibility
    if (!gr || !start) return NULL;

    // Allocate memory for visited nodes array
    int num_nodes = graph_num_nodes(gr);
    void** visited = malloc((num_nodes + 1) * sizeof(void*));
    if (!visited) return NULL;

    // Allocate memory for BFS queue
    void** queue = malloc((num_nodes + 1) * sizeof(void*));
    if (!queue) {
        free(visited);
        return NULL;
    }

    int visited_count = 0;
    int queue_front = 0, queue_rear = 0;

    // Initialize BFS with start node
    queue[queue_rear++] = start;
    visited[visited_count++] = start;

    // Main BFS loop
    while (queue_front < queue_rear) {
        void* current = queue[queue_front++];

        // Process all neighbors of current node
        void** neighbors = graph_get_neighbours(gr, current);
        if (neighbors) {
            for (int i = 0; neighbors[i] != NULL; i++) {
                // Check if neighbor has been visited
                int is_visited = 0;
                for (int j = 0; j < visited_count; j++) {
                    if (compare(neighbors[i], visited[j]) == 0) {
                        is_visited = 1;
                        break;
                    }
                }

                // Add unvisited neighbors to queue
                if (!is_visited) {
                    queue[queue_rear++] = neighbors[i];
                    visited[visited_count++] = neighbors[i];
                }
            }
            free(neighbors);
        }
    }

    // Null-terminate the visited array
    visited[visited_count] = NULL;

    // Clean up and measure execution time
    free(queue);
    clock_t to = clock();
    double time_taken = (double)(to - from) / CLOCKS_PER_SEC;
    printf("The time taken by the breadth_first_visit is: %f sec\n", time_taken);

    return visited;
}