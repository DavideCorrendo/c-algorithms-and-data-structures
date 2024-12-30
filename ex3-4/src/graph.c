#include "graph.h"

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

// Verifica se il grafo è diretto
Bool graph_is_directed(const Graph* gr) {
    return gr ? gr->is_directed : false;
}

// Verifica se il grafo è etichettato
Bool graph_is_labelled(const Graph* gr) {
    return gr ? gr->is_labelled : false;
}

Bool graph_add_node(Graph* gr, const void* node) {
    if (!gr || !node) return false;
    if (hash_table_get(gr->nodes, node)) return false; // Nodo già esistente

    HashTable* adjacency_list = hash_table_create(gr->nodes->compare, gr->nodes->hash);
    if (!adjacency_list) return false;

    // Create a copy of the node
    void* node_copy = strdup((const char*)node);
    if (!node_copy) {
        hash_table_free(adjacency_list);
        return false;
    }

    hash_table_put(gr->nodes, node_copy, adjacency_list);
    return true;
}

// Aggiunge un arco al grafo
Bool graph_add_edge(Graph* gr, const void* node1, const void* node2, const void* label) {
    if (!gr || !node1 || !node2) return false;

    // Controllo esistenza nodi
    HashTable* adjacency_list1 = hash_table_get(gr->nodes, node1);
    HashTable* adjacency_list2 = hash_table_get(gr->nodes, node2);
    if (!adjacency_list1 || !adjacency_list2) return false;

    // Controllo etichetta per grafi etichettati
    if (gr->is_labelled && !label) return false;

    // Controllo se l'arco esiste già in entrambe le direzioni
    if (hash_table_get(adjacency_list1, node2) && 
        (!gr->is_directed && hash_table_get(adjacency_list2, node1))) {
        return true; // Arco già esistente, non incrementare il contatore
    }

    // Copia dell'etichetta se necessario
    void* label_copy = gr->is_labelled ? memcpy(malloc(sizeof(float)), label, sizeof(float)) : NULL;

    hash_table_put(adjacency_list1, node2, label_copy);

    // Per grafi non diretti, aggiungo anche l'arco inverso
    if (!gr->is_directed) {
        hash_table_put(adjacency_list2, node1, label_copy);
    }

    gr->edge_count++;

    return true;
}

// Controlla se un nodo è nel grafo
Bool graph_contains_node(const Graph* gr, const void* node) {
    if (!gr || !node) return false;
    return hash_table_get(gr->nodes, node) != NULL;
}

// Controlla se un arco è nel grafo
Bool graph_contains_edge(const Graph* gr, const void* node1, const void* node2) {
    if (!gr || !node1 || !node2) return false;

    HashTable* adjacency_list = hash_table_get(gr->nodes, node1);
    if (!adjacency_list) return false;

    return hash_table_get(adjacency_list, node2) != NULL;
}

// Rimuove un nodo dal grafo
Bool graph_remove_node(Graph* gr, const void* node) {
    if (!gr || !node) return false;

    HashTable* adjacency_list = hash_table_get(gr->nodes, node);
    if (!adjacency_list) return false;

    // Rimuove archi con questo nodo
    void** neighbours = hash_table_keyset(adjacency_list);
    if (neighbours) {
        for (int i = 0; neighbours[i] != NULL; i++) {
            graph_remove_edge(gr, node, neighbours[i]);
        }
        free(neighbours);
    }

    hash_table_free(adjacency_list);
    hash_table_remove(gr->nodes, node);
    return true;
}

// Rimuove un arco dal grafo
Bool graph_remove_edge(Graph* gr, const void* node1, const void* node2) {
    if (!gr || !node1 || !node2) return false;

    HashTable* adjacency_list = hash_table_get(gr->nodes, node1);
    if (!adjacency_list) return false;

    hash_table_remove(adjacency_list, node2);

    // Per grafi non diretti, rimuove l'arco inverso
    if (!gr->is_directed) {
        HashTable* reverse_list = hash_table_get(gr->nodes, node2);
        if (reverse_list) {
            hash_table_remove(reverse_list, node1);
        }
    }

    gr->edge_count--;
    return true;
}

// Recupera il numero di nodi
int graph_num_nodes(const Graph* gr) {
    return gr ? gr->nodes->size : 0;
}

// Recupera il numero di archi
int graph_num_edges(const Graph* gr) {
    return gr ? gr->edge_count : 0;
}

// Recupero dei nodi del grafo
void** graph_get_nodes(const Graph* gr) {
    if (!gr) return NULL;
    return gr ? hash_table_keyset(gr->nodes) : NULL; // Uso di hash_table_keyset
}

// Recupera tutti gli archi del grafo
Edge** graph_get_edges(const Graph* gr) {
    if (!gr) return NULL;

    // Calcola il numero totale di archi
    int edge_count = graph_num_edges(gr);
    if (edge_count == 0) return NULL;

    // Alloca memoria per gli archi
    Edge** edges = malloc((edge_count + 1) * sizeof(Edge*));
    if (!edges) return NULL;

    int index = 0;
    void** nodes = hash_table_keyset(gr->nodes);
    
    // Itera sui nodi
    for (int i = 0; nodes[i] != NULL; i++) {
        HashTable* adjacency_list = hash_table_get(gr->nodes, nodes[i]);
        void** neighbours = hash_table_keyset(adjacency_list);
        
        // Itera sui vicini
        for (int j = 0; neighbours[j] != NULL; j++) {
            Edge* edge = malloc(sizeof(Edge));
            if (!edge) {
                // Libera memoria in caso di errore
                for (int k = 0; k < index; k++) {
                    free(edges[k]);
                }
                free(edges);
                free(nodes);
                return NULL;
            }

            edge->source = nodes[i];
            edge->dest = neighbours[j];
            edge->label = graph_get_label(gr, nodes[i], neighbours[j]);
            
            edges[index++] = edge;
        }

        free(neighbours);
    }

    free(nodes);
    edges[index] = NULL; // Terminatore
    return edges;
}

// Recupero dei vicini di un nodo
void** graph_get_neighbours(const Graph* gr, const void* node) {
    if (!gr || !node) return NULL;
    HashTable* adjacency_list = hash_table_get(gr->nodes, node);
    return adjacency_list ? hash_table_keyset(adjacency_list) : NULL; // Uso di hash_table_keyset
}

// Recupera il numero di nodi adiacenti
int graph_num_neighbours(const Graph* gr, const void* node) {
    if (!gr || !node) return 0;

    HashTable* adjacency_list = hash_table_get(gr->nodes, node);
    return adjacency_list ? adjacency_list->size : 0;
}

// Recupera l'etichetta di un arco
void* graph_get_label(const Graph* gr, const void* node1, const void* node2) {
    if (!gr || !node1 || !node2) return NULL;

    HashTable* adjacency_list = hash_table_get(gr->nodes, node1);
    return adjacency_list ? hash_table_get(adjacency_list, node2) : NULL;
}

void graph_free(Graph* gr) {
    if (!gr) return;

    if (gr->nodes) {
        for (int i = 0; i < gr->nodes->bucket_count; i++) {
            HashNode* entry = gr->nodes->buckets[i];
            while (entry) {
                // Free the node key
                free((void*)entry->key);
                
                // Free the adjacency list
                if (entry->value) {
                    hash_table_free((HashTable*)entry->value);
                }
                entry = entry->next;
            }
        }

        hash_table_free(gr->nodes);
    }

    free(gr);
}
