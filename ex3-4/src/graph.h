/**
 * @file graph.h
 * @brief Graph data structure header
 * @details Defines the interface for a generic graph implementation supporting both directed and undirected graphs,
 * with optional edge labels
 */

#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../src/hashtable.h"
#include <time.h>

/** @brief Boolean type definition */
typedef enum {false = 0, true = 1} Bool;

/**
 * @struct edge
 * @brief Structure representing a graph edge
 */
typedef struct edge {
    void* source;  /**< Source node of the edge */
    void* dest;    /**< Destination node of the edge */
    void* label;   /**< Edge label (optional) */
} Edge;

/**
 * @struct graph
 * @brief Structure representing the graph
 */
typedef struct graph {
    HashTable* nodes;      /**< Hash table storing nodes and their adjacency lists */
    Bool is_directed;      /**< Flag indicating if the graph is directed */
    Bool is_labelled;      /**< Flag indicating if the graph has edge labels */
    int edge_count;        /**< Total number of edges in the graph */
} Graph;

/**
 * @brief Creates a new graph
 * @param labelled Whether the graph has edge labels
 * @param directed Whether the graph is directed
 * @param compare Function for comparing node values
 * @param hash Function for hashing node values
 * @return Pointer to the created graph, NULL on failure
 */
Graph* graph_create(Bool labelled, Bool directed, int (*compare)(const void*, const void*), unsigned long (*hash)(const void*));

/**
 * @brief Checks if the graph is directed
 * @param gr The graph
 * @return true if directed, false otherwise
 */
Bool graph_is_directed(const Graph* gr);

/**
 * @brief Checks if the graph has edge labels
 * @param gr The graph
 * @return true if labelled, false otherwise
 */
Bool graph_is_labelled(const Graph* gr);

/**
 * @brief Adds a node to the graph
 * @param gr The graph
 * @param node The node to add
 * @return true if successful, false otherwise
 */
Bool graph_add_node(Graph* gr, const void* node);

/**
 * @brief Adds an edge to the graph
 * @param gr The graph
 * @param node1 Source node
 * @param node2 Destination node
 * @param label Edge label (can be NULL for unlabelled graphs)
 * @return true if successful, false otherwise
 */
Bool graph_add_edge(Graph* gr, const void* node1, const void* node2, const void* label);

/**
 * @brief Checks if a node exists in the graph
 * @param gr The graph
 * @param node The node to check
 * @return true if node exists, false otherwise
 */
Bool graph_contains_node(const Graph* gr, const void* node);

/**
 * @brief Checks if an edge exists in the graph
 * @param gr The graph
 * @param node1 Source node
 * @param node2 Destination node
 * @return true if edge exists, false otherwise
 */
Bool graph_contains_edge(const Graph* gr, const void* node1, const void* node2);

/**
 * @brief Removes a node from the graph
 * @param gr The graph
 * @param node The node to remove
 * @return true if successful, false otherwise
 */
Bool graph_remove_node(Graph* gr, const void* node);

/**
 * @brief Removes an edge from the graph
 * @param gr The graph
 * @param node1 Source node
 * @param node2 Destination node
 * @return true if successful, false otherwise
 */
Bool graph_remove_edge(Graph* gr, const void* node1, const void* node2);

/**
 * @brief Gets the number of nodes in the graph
 * @param gr The graph
 * @return Number of nodes
 */
int graph_num_nodes(const Graph* gr);

/**
 * @brief Gets the number of edges in the graph
 * @param gr The graph
 * @return Number of edges
 */
int graph_num_edges(const Graph* gr);

/**
 * @brief Gets an array of all nodes in the graph
 * @param gr The graph
 * @return NULL-terminated array of nodes
 */
void** graph_get_nodes(const Graph* gr);

/**
 * @brief Gets an array of all edges in the graph
 * @param gr The graph
 * @return NULL-terminated array of Edge pointers
 */
Edge** graph_get_edges(const Graph* gr);

/**
 * @brief Gets an array of all neighboring nodes
 * @param gr The graph
 * @param node The node whose neighbors to get
 * @return NULL-terminated array of neighboring nodes
 */
void** graph_get_neighbours(const Graph* gr, const void* node);

/**
 * @brief Gets the number of neighbors for a node
 * @param gr The graph
 * @param node The node to check
 * @return Number of neighboring nodes
 */
int graph_num_neighbours(const Graph* gr, const void* node);

/**
 * @brief Gets the label of an edge
 * @param gr The graph
 * @param node1 Source node
 * @param node2 Destination node
 * @return Edge label, NULL if edge doesn't exist or graph is unlabelled
 */
void* graph_get_label(const Graph* gr, const void* node1, const void* node2);

/**
 * @brief Frees all memory associated with the graph
 * @param gr The graph to free
 */
void graph_free(Graph* gr);

#endif // GRAPH_H