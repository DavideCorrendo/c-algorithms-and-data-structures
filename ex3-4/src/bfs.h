#include "graph.h"

unsigned long hash_string(const void* key);

int compare_strings(const void* a, const void* b);

void** breadth_first_visit(Graph* gr, void* start, int (*compare)(const void*, const void*), unsigned long (*hash)(const void*));
