
#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../src/hashtable.h"
#include <time.h>

typedef enum {false = 0, true = 1} Bool;

typedef struct edge {
    void* source;  // Nodo d'origine
    void* dest;    // Nodo di destinazione
    void* label;   // Etichetta dell'arco
} Edge;

typedef struct graph {
    HashTable* nodes;      // Tabella hash dei nodi e delle liste di adiacenza
    Bool is_directed;      // Indica se il grafo è diretto
    Bool is_labelled;      // Indica se il grafo è etichettato
    int edge_count;        // Numero di archi nel grafo
} Graph;

// Funzioni principali
Graph* graph_create(Bool labelled, Bool directed, int (*compare)(const void*, const void*),unsigned long (*hash)(const void*));
Bool graph_is_directed(const Graph* gr);
Bool graph_is_labelled(const Graph* gr);
Bool graph_add_node(Graph* gr, const void* node);                                                  // aggiunge un nodo -- O(1)
Bool graph_add_edge(Graph* gr, const void* node1, const void* node2, const void* label);           // aggiunge un arco dati estremi ed etichetta -- O(1) (*)
Bool graph_contains_node(const Graph* gr, const void* node);                                       // controlla se un nodo è nel grafo -- O(1)
Bool graph_contains_edge(const Graph* gr, const void* node1, const void* node2);                   // controlla se un arco è nel grafo -- O(1) (*)
Bool graph_remove_node(Graph* gr, const void* node);                                               // rimuove un nodo dal grafo -- O(N)
Bool graph_remove_edge(Graph* gr, const void* node1, const void* node2);                           // rimuove un arco dal grafo -- O(1) (*)
int graph_num_nodes(const Graph* gr);                                                              // numero di nodi -- O(1)
int graph_num_edges(const Graph* gr);                                                              // numero di archi -- O(N)
void** graph_get_nodes(const Graph* gr);                                                           // recupero dei nodi del grafo -- O(N)
Edge** graph_get_edges(const Graph* gr);                                                           // recupero degli archi del grafo -- O(N)
void** graph_get_neighbours(const Graph* gr, const void* node);                                    // recupero dei nodi adiacenti ad un dato nodo -- O(1) (*)
int graph_num_neighbours(const Graph* gr, const void* node);                                       // recupero del numero di nodi adiacenti ad un dato nodo -- O(1)
void* graph_get_label(const Graph* gr, const void* node1, const void* node2);                      // recupero dell'etichetta di un arco -- O(1) (*)
void graph_free(Graph* gr);

#endif // GRAPH_H
