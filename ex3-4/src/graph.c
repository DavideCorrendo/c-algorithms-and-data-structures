/**
 * @file graph.c
 * @brief Implementation of graph data structure functions
 * @details Provides implementation for a generic graph structure supporting both
 * directed/undirected graphs and optional edge labels
 */

#include "graph.h"

/**
 * @brief Creates a new graph
 * @param labelled Boolean indicating if edges have labels
 * @param directed Boolean indicating if graph is directed
 * @param compare Function pointer for comparing node values
 * @param hash Function pointer for hashing node values
 * @return Pointer to new Graph structure, NULL if allocation fails
 */
Graph* graph_create(Bool labelled, Bool directed, int (*compare)(const void*, const void*), unsigned long (*hash)(const void*)) {
    Graph* gr = malloc(sizeof(Graph));
    if (!gr) return NULL;

    gr->nodes = hash_table_create(compare, hash);
    if (!gr->nodes) {
        free(gr);
        return NULL;
    }

    gr->is_labelled = labelled;
    gr->is_directed = directed;
    gr->edge_count = 0;

    return gr;
}

/**
 * @brief Checks if graph is directed
 * @param gr Pointer to the graph
 * @return true if graph is directed, false otherwise or if gr is NULL
 */
Bool graph_is_directed(const Graph* gr) {
    return gr ? gr->is_directed : false;
}

/**
 * @brief Checks if graph has edge labels
 * @param gr Pointer to the graph
 * @return true if graph has edge labels, false otherwise or if gr is NULL
 */
Bool graph_is_labelled(const Graph* gr) {
    return gr ? gr->is_labelled : false;
}

/**
 * @brief Adds a new node to the graph
 * @param gr Pointer to the graph
 * @param node Pointer to the node value to add
 * @return true if node was added successfully, false otherwise
 * @details Creates a deep copy of the node value and initializes its adjacency list
 */
Bool graph_add_node(Graph* gr, const void* node) {
    if (!gr || !node) return false;
    
    // Check if node already exists
    if (graph_contains_node(gr, node)) return false;

    // Create new adjacency list for the node
    HashTable* adjacency_list = hash_table_create(gr->nodes->compare, gr->nodes->hash);
    if (!adjacency_list) return false;

    // Create deep copy of node value
    char* node_copy = strdup((const char*)node);
    if (!node_copy) {
        hash_table_free(adjacency_list);
        return false;
    }

    // Add node and its adjacency list to graph
    hash_table_put(gr->nodes, node_copy, adjacency_list);
    return true;
}

/**
 * @brief Adds a new edge to the graph
 * @param gr Pointer to the graph
 * @param node1 Source node
 * @param node2 Destination node
 * @param label Edge label (required if graph is labelled)
 * @return true if edge was added successfully, false otherwise
 * @details For undirected graphs, adds edges in both directions
 */
Bool graph_add_edge(Graph* gr, const void* node1, const void* node2, const void* label) {
    if (!gr || !node1 || !node2) return false;
    if (gr->is_labelled && !label) return false;

    // Get adjacency lists for both nodes
    HashTable* adj1 = hash_table_get(gr->nodes, node1);
    HashTable* adj2 = hash_table_get(gr->nodes, node2);
    if (!adj1 || !adj2) return false;

    // Check if edge already exists
    if (hash_table_contains_key(adj1, node2)) {
        return true;  // Edge already exists
    }

    // Create copy of label if graph is labelled
    void* label_copy = NULL;
    if (gr->is_labelled) {
        label_copy = malloc(sizeof(float));
        if (!label_copy) return false;
        memcpy(label_copy, label, sizeof(float));
    }

    // Add forward edge
    hash_table_put(adj1, node2, label_copy);

    // For undirected graphs, add reverse edge
    if (!gr->is_directed) {
        void* reverse_label = NULL;
        if (gr->is_labelled) {
            reverse_label = malloc(sizeof(float));
            if (!reverse_label) {
                // Cleanup if allocation fails
                hash_table_remove(adj1, node2);
                free(label_copy);
                return false;
            }
            memcpy(reverse_label, label, sizeof(float));
        }
        hash_table_put(adj2, node1, reverse_label);
    }

    gr->edge_count++;
    return true;
}

/**
 * @brief Checks if a node exists in the graph
 * @param gr Pointer to the graph
 * @param node Node to check
 * @return true if node exists, false otherwise
 */
Bool graph_contains_node(const Graph* gr, const void* node) {
    if (!gr || !node) return false;
    return hash_table_contains_key(gr->nodes, node);
}

/**
 * @brief Checks if an edge exists in the graph
 * @param gr Pointer to the graph
 * @param node1 Source node
 * @param node2 Destination node
 * @return true if edge exists, false otherwise
 */
Bool graph_contains_edge(const Graph* gr, const void* node1, const void* node2) {
    if (!gr || !node1 || !node2) return false;
    
    HashTable* adj = hash_table_get(gr->nodes, node1);
    return adj && hash_table_contains_key(adj, node2);
}

/**
 * @brief Removes a node and all its edges from the graph
 * @param gr Pointer to the graph
 * @param node Node to remove
 * @return true if node was removed successfully, false otherwise
 */
Bool graph_remove_node(Graph* gr, const void* node) {
    if (!gr || !node) return false;

    HashTable* adj = hash_table_get(gr->nodes, node);
    if (!adj) return false;

    // Remove all edges connected to this node
    void** neighbors = hash_table_keyset(adj);
    if (neighbors) {
        for (int i = 0; neighbors[i] != NULL; i++) {
            graph_remove_edge(gr, node, neighbors[i]);
            if (!gr->is_directed) {
                graph_remove_edge(gr, neighbors[i], node);
            }
        }
        free(neighbors);
    }

    // Free adjacency list and remove node
    hash_table_free(adj);
    hash_table_remove(gr->nodes, node);

    return true;
}

/**
 * @brief Removes an edge from the graph
 * @param gr Pointer to the graph
 * @param node1 Source node
 * @param node2 Destination node
 * @return true if edge was removed successfully, false otherwise
 */
Bool graph_remove_edge(Graph* gr, const void* node1, const void* node2) {
    if (!gr || !node1 || !node2) return false;

    HashTable* adj1 = hash_table_get(gr->nodes, node1);
    if (!adj1) return false;

    // Remove edge(s)
    if (hash_table_contains_key(adj1, node2)) {
        // Free label if graph is labelled
        if (gr->is_labelled) {
            void* label = hash_table_get(adj1, node2);
            free(label);
        }
        hash_table_remove(adj1, node2);

        // Remove reverse edge for undirected graphs
        if (!gr->is_directed) {
            HashTable* adj2 = hash_table_get(gr->nodes, node2);
            if (adj2) {
                if (gr->is_labelled) {
                    void* reverse_label = hash_table_get(adj2, node1);
                    free(reverse_label);
                }
                hash_table_remove(adj2, node1);
            }
        }

        gr->edge_count--;
        return true;
    }

    return false;
}

/**
 * @brief Gets the number of nodes in the graph
 * @param gr Pointer to the graph
 * @return Number of nodes, 0 if gr is NULL
 */
int graph_num_nodes(const Graph* gr) {
    return gr ? hash_table_size(gr->nodes) : 0;
}

/**
 * @brief Gets the number of edges in the graph
 * @param gr Pointer to the graph
 * @return Number of edges, 0 if gr is NULL
 */
int graph_num_edges(const Graph* gr) {
    return gr ? gr->edge_count : 0;
}

/**
 * @brief Gets array of all nodes in the graph
 * @param gr Pointer to the graph
 * @return NULL-terminated array of node pointers, NULL if gr is NULL
 */
void** graph_get_nodes(const Graph* gr) {
    return gr ? hash_table_keyset(gr->nodes) : NULL;
}

/**
 * @brief Gets array of all edges in the graph
 * @param gr Pointer to the graph
 * @return NULL-terminated array of Edge pointers, NULL if gr is NULL or empty
 */
Edge** graph_get_edges(const Graph* gr) {
    if (!gr || gr->edge_count == 0) return NULL;

    // Allocate array for edges
    Edge** edges = malloc((gr->edge_count + 1) * sizeof(Edge*));
    if (!edges) return NULL;

    int index = 0;
    void** nodes = hash_table_keyset(gr->nodes);
    if (!nodes) {
        free(edges);
        return NULL;
    }

    // Iterate through all nodes and their edges
    for (int i = 0; nodes[i] != NULL; i++) {
        HashTable* adj = hash_table_get(gr->nodes, nodes[i]);
        void** neighbors = hash_table_keyset(adj);
        
        if (neighbors) {
            for (int j = 0; neighbors[j] != NULL; j++) {
                Edge* edge = malloc(sizeof(Edge));
                if (!edge) {
                    // Cleanup on allocation failure
                    for (int k = 0; k < index; k++) {
                        free(edges[k]);
                    }
                    free(edges);
                    free(neighbors);
                    free(nodes);
                    return NULL;
                }

                edge->source = nodes[i];
                edge->dest = neighbors[j];
                edge->label = graph_get_label(gr, nodes[i], neighbors[j]);
                edges[index++] = edge;
            }
            free(neighbors);
        }
    }
    free(nodes);

    edges[index] = NULL; // NULL terminate array
    return edges;
}

/**
 * @brief Gets array of neighboring nodes
 * @param gr Pointer to the graph
 * @param node Source node
 * @return NULL-terminated array of neighbor pointers, NULL if node not found
 */
void** graph_get_neighbours(const Graph* gr, const void* node) {
    if (!gr || !node) return NULL;
    
    HashTable* adj = hash_table_get(gr->nodes, node);
    return adj ? hash_table_keyset(adj) : NULL;
}

/**
 * @brief Gets number of neighbors for a node
 * @param gr Pointer to the graph
 * @param node Source node
 * @return Number of neighbors, 0 if node not found
 */
int graph_num_neighbours(const Graph* gr, const void* node) {
    if (!gr || !node) return 0;

    HashTable* adj = hash_table_get(gr->nodes, node);
    return adj ? hash_table_size(adj) : 0;
}

/**
 * @brief Gets label of an edge
 * @param gr Pointer to the graph
 * @param node1 Source node
 * @param node2 Destination node
 * @return Pointer to edge label, NULL if edge not found or graph unlabelled
 */
void* graph_get_label(const Graph* gr, const void* node1, const void* node2) {
    if (!gr || !node1 || !node2) return NULL;

    HashTable* adj = hash_table_get(gr->nodes, node1);
    return adj ? hash_table_get(adj, node2) : NULL;
}

/**
 * @brief Frees all memory associated with the graph
 * @param gr Pointer to the graph to free
 */
void graph_free(Graph* gr) {
    if (!gr) return;

    // Free all nodes and their adjacency lists
    if (gr->nodes) {
        for (int i = 0; i < gr->nodes->bucket_count; i++) {
            HashNode* entry = gr->nodes->buckets[i];
            while (entry) {
                // Free node key (strdup'd in add_node)
                free((void*)entry->key);
                
                // Free adjacency list and its contents
                if (entry->value) {
                    HashTable* adj = (HashTable*)entry->value;
                    if (gr->is_labelled) {
                        // Free edge labels
                        void** neighbors = hash_table_keyset(adj);
                        if (neighbors) {
                            for (int j = 0; neighbors[j] != NULL; j++) {
                                void* label = hash_table_get(adj, neighbors[j]);
                                free(label);
                            }
                            free(neighbors);
                        }
                    }
                    hash_table_free(adj);
                }
                entry = entry->next;
            }
        }
        hash_table_free(gr->nodes);
    }

    free(gr);
}