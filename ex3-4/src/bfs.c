#include "bfs.h"
#include <string.h>
#include <stdlib.h>


void** breadth_first_visit(Graph* gr, void* start, int (*compare)(const void*, const void*), unsigned long (*hash)(const void*)) {
    hash(start);
    if (!gr || !start) return NULL;

    int num_nodes = graph_num_nodes(gr);
    void** visited = malloc((num_nodes + 1) * sizeof(void*));
    if (!visited) return NULL;

    // Create a queue for BFS
    void** queue = malloc((num_nodes + 1) * sizeof(void*));
    if (!queue) {
        free(visited);
        return NULL;
    }

    int visited_count = 0;
    int queue_front = 0, queue_rear = 0;

    // Enqueue the start node and mark as visited
    queue[queue_rear++] = start;
    visited[visited_count++] = start;

    while (queue_front < queue_rear) {
        void* current = queue[queue_front++];

        // Get neighbors of the current node
        void** neighbors = graph_get_neighbours(gr, current);
        if (neighbors) {
            for (int i = 0; neighbors[i] != NULL; i++) {
                // Check if neighbor is already visited
                int is_visited = 0;
                for (int j = 0; j < visited_count; j++) {
                    if (compare(neighbors[i], visited[j]) == 0) {
                        is_visited = 1;
                        break;
                    }
                }

                // If not visited, enqueue and mark as visited
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

    free(queue);
    return visited;
}
