/**
 * @file main.c
 * @brief Main program for graph traversal implementation
 * @details Implements the main functionality to read a graph from a file,
 * perform breadth-first search, and output the results
 */

#include "graph.h"
#include "bfs.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * @brief Main entry point of the program
 * @param argc Number of command line arguments
 * @param argv Array of command line arguments
 * @return EXIT_SUCCESS on successful execution, EXIT_FAILURE on error
 * 
 * Expected command line arguments:
 * - argv[1]: Input graph file path
 * - argv[2]: Starting city name
 * - argv[3]: Output file path
 */
int main(int argc, char *argv[]) {
    if(argc != 4){
        fprintf(stderr, "Usage: %s <graph file> <starting city> <output file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE *filegraph = fopen(argv[1], "r");
    if(!filegraph){
        fprintf(stderr, "ERROR IN GRAPH FILE OPENING\n");
        return EXIT_FAILURE;
    }

    Graph *gr = graph_create(true, false, compare_strings, hash_string);
    if (!gr) {
        fprintf(stderr, "Failed to create graph\n");
        fclose(filegraph);
        return EXIT_FAILURE;
    }

    char node1[256];
    char node2[256];
    char w[256];
    
    while (fscanf(filegraph, "%[^,],%[^,],%[^\n]\n", node1, node2, w) == 3) {
        if (strlen(node1) == 0 || strlen(node2) == 0) {
            fprintf(stderr, "Invalid node name\n");
            continue;
        }

        char* node1_copy = malloc(30 * sizeof(char));
        char* node2_copy = malloc(30 * sizeof(char));

        strcpy(node1_copy, node1);
        strcpy(node2_copy, node2);

        if (!graph_contains_node(gr, node1_copy)) {
            graph_add_node(gr, node1_copy);
        }

        if (!graph_contains_node(gr, node2_copy)) {
            graph_add_node(gr, node2_copy);
        }

        float label = atof(w);
        
        if (!graph_add_edge(gr, node1_copy, node2_copy, &label)) {
            fprintf(stderr, "Failed to add edge on line\n");
        }
    }

    char* start_node = argv[2];
    if (!graph_contains_node(gr, start_node)) {
        fprintf(stderr, "Starting node '%s' not found in graph\n", start_node);
        graph_free(gr);
        return EXIT_FAILURE;
    }

    void** res = breadth_first_visit(gr, start_node, compare_strings, hash_string);
    if (!res) {
        fprintf(stderr, "BFS traversal failed\n");
        graph_free(gr);
        return EXIT_FAILURE;
    }

    FILE *fileout = fopen(argv[3], "w");
    if(!fileout){
        fprintf(stderr, "ERROR IN OUTPUT FILE OPENING\n");
        graph_free(gr);
        free(res);
        return EXIT_FAILURE;
    }

    for(int i = 0; res[i] != NULL; i++){
        fprintf(fileout, "%s\n", (char*)res[i]);
    }

    fclose(fileout);
    graph_free(gr);
    free(res);

    return 0;
}

/**
 * @brief Generates a hash value for a string
 * @param key Pointer to the string to hash
 * @return Unsigned long hash value
 * @details Uses the DJB2 hash algorithm
 */
unsigned long hash_string(const void* key) {
    const char* str = (const char*)key;
    unsigned long hash = 5381;
    int c;
    while ((c = *str++))
        hash = ((hash << 5) + hash) + c;
    return hash;
}

/**
 * @brief Compares two strings case-insensitively
 * @param a Pointer to first string
 * @param b Pointer to second string
 * @return Integer less than, equal to, or greater than zero if a is found,
 *         respectively, to be less than, to match, or be greater than b
 */
int compare_strings(const void* a, const void* b) {
    return strcasecmp((const char*)a, (const char*)b);
}