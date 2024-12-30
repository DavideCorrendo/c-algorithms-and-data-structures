#include "graph.h"
#include "bfs.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]){
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

        // Convert weight to float
        float label = atof(w);
        
        // Add edge 
        if (!graph_add_edge(gr, node1_copy, node2_copy, &label)) {
            fprintf(stderr, "Failed to add edge on line\n");
        }
    }



    // Verify starting node exists
    char* start_node = argv[2];
    if (!graph_contains_node(gr, start_node)) {
        fprintf(stderr, "Starting node '%s' not found in graph\n", start_node);
        graph_free(gr);
        return EXIT_FAILURE;
    }

    // Perform BFS
    void** res = breadth_first_visit(gr, start_node, compare_strings, hash_string);
    if (!res) {
        fprintf(stderr, "BFS traversal failed\n");
        graph_free(gr);
        return EXIT_FAILURE;
    }

    // Open output file
    FILE *fileout = fopen(argv[3], "w");
    if(!fileout){
        fprintf(stderr, "ERROR IN OUTPUT FILE OPENING\n");
        graph_free(gr);
        free(res);
        return EXIT_FAILURE;
    }

    // Write BFS results
    for(int i = 0; res[i] != NULL; i++){
        fprintf(fileout, "%s\n", (char*)res[i]);
    }

    // Cleanup
    fclose(fileout);
    graph_free(gr);
    free(res);

    return 0;
}

unsigned long hash_string(const void* key) {
    const char* str = (const char*)key;
    unsigned long hash = 5381;
    int c;
    while ((c = *str++))
        hash = ((hash << 5) + hash) + c;
    return hash;
}

int compare_strings(const void* a, const void* b) {
    return strcasecmp((const char*)a, (const char*)b);
}