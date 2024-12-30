#include "unity.h"
#include <string.h>
#include <stdlib.h>
#include "../src/graph.h"
#include "../src/bfs.h"
#include "../src/hashtable.h"

// Utility function for string comparison
int test_compare_strings(const void* a, const void* b) {
    return strcmp((const char*)a, (const char*)b);
}

// Utility function for hashing strings
unsigned long test_hash_string(const void* key) {
    const char* str = (const char*)key;
    unsigned long hash = 5381;
    int c;
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash;
}

// Global variables for tests
static Graph* graph = NULL;
static HashTable* hash_table = NULL;

void setUp(void) {
    // Initialize graph for graph-related tests
    graph = graph_create(true, false, test_compare_strings, test_hash_string);
    TEST_ASSERT_NOT_NULL(graph);

    // Initialize hash table
    hash_table = hash_table_create(test_compare_strings, test_hash_string);
    TEST_ASSERT_NOT_NULL(hash_table);
}

void tearDown(void) {
    // Clean up graph after each test
    if (graph) {
        graph_free(graph);
        graph = NULL;
    }

    // Clean up hash table
    if (hash_table) {
        hash_table_free(hash_table);
        hash_table = NULL;
    }
}

// Hash Table Tests
void test_hash_table_create(void) {
    TEST_ASSERT_NOT_NULL(hash_table);
    TEST_ASSERT_EQUAL_INT(0, hash_table_size(hash_table));
}

void test_hash_table_put_get(void) {
    const char* key = "test_key";
    const char* value = "test_value";
    
    hash_table_put(hash_table, key, value);
    
    TEST_ASSERT_EQUAL_INT(1, hash_table_size(hash_table));
    TEST_ASSERT_EQUAL_PTR(value, hash_table_get(hash_table, key));
}

void test_hash_table_multiple_puts(void) {
    const char* key1 = "key1";
    const char* value1 = "value1";
    const char* key2 = "key2";
    const char* value2 = "value2";
    
    hash_table_put(hash_table, key1, value1);
    hash_table_put(hash_table, key2, value2);
    
    TEST_ASSERT_EQUAL_INT(2, hash_table_size(hash_table));
    TEST_ASSERT_EQUAL_PTR(value1, hash_table_get(hash_table, key1));
    TEST_ASSERT_EQUAL_PTR(value2, hash_table_get(hash_table, key2));
}

void test_hash_table_overwrite(void) {
    const char* key = "key";
    const char* value1 = "value1";
    const char* value2 = "value2";
    
    hash_table_put(hash_table, key, value1);
    hash_table_put(hash_table, key, value2);
    
    TEST_ASSERT_EQUAL_INT(1, hash_table_size(hash_table));
    TEST_ASSERT_EQUAL_PTR(value2, hash_table_get(hash_table, key));
}

void test_hash_table_contains_key(void) {
    const char* key = "existing_key";
    
    hash_table_put(hash_table, key, "some_value");
    
    TEST_ASSERT_TRUE(hash_table_contains_key(hash_table, key));
    TEST_ASSERT_FALSE(hash_table_contains_key(hash_table, "non_existing_key"));
}

void test_hash_table_remove(void) {
    const char* key = "key_to_remove";
    
    hash_table_put(hash_table, key, "value");
    hash_table_remove(hash_table, key);
    
    TEST_ASSERT_FALSE(hash_table_contains_key(hash_table, key));
    TEST_ASSERT_EQUAL_INT(0, hash_table_size(hash_table));
}

void test_hash_table_keyset(void) {
    const char* key1 = "key1";
    const char* key2 = "key2";
    
    hash_table_put(hash_table, key1, "value1");
    hash_table_put(hash_table, key2, "value2");
    
    void** keys = hash_table_keyset(hash_table);
    TEST_ASSERT_NOT_NULL(keys);
    
    // Check that both keys are in the keyset
    int found1 = 0, found2 = 0;
    for (int i = 0; keys[i] != NULL; i++) {
        if (strcmp(keys[i], key1) == 0) found1 = 1;
        if (strcmp(keys[i], key2) == 0) found2 = 1;
    }
    TEST_ASSERT_TRUE(found1);
    TEST_ASSERT_TRUE(found2);
    
    free(keys);
}

// Graph Tests
void test_graph_create(void) {
    TEST_ASSERT_NOT_NULL(graph);
    TEST_ASSERT_EQUAL_INT(0, graph_num_nodes(graph));
    TEST_ASSERT_EQUAL_INT(0, graph_num_edges(graph));
    TEST_ASSERT_TRUE(graph_is_labelled(graph));
    TEST_ASSERT_FALSE(graph_is_directed(graph));
}

void test_graph_add_node(void) {
    const char* node = "TestNode";
    
    TEST_ASSERT_TRUE(graph_add_node(graph, node));
    TEST_ASSERT_TRUE(graph_contains_node(graph, node));
    TEST_ASSERT_EQUAL_INT(1, graph_num_nodes(graph));
    
    // Try to add duplicate node
    TEST_ASSERT_FALSE(graph_add_node(graph, node));
    TEST_ASSERT_EQUAL_INT(1, graph_num_nodes(graph));
}

void test_graph_add_multiple_nodes(void) {
    const char* node1 = "Node1";
    const char* node2 = "Node2";
    
    TEST_ASSERT_TRUE(graph_add_node(graph, node1));
    TEST_ASSERT_TRUE(graph_add_node(graph, node2));
    TEST_ASSERT_EQUAL_INT(2, graph_num_nodes(graph));
}

void test_graph_add_edge(void) {
    const char* node1 = "A";
    const char* node2 = "B";
    float label = 1.5f;
    
    // Add nodes first
    TEST_ASSERT_TRUE(graph_add_node(graph, node1));
    TEST_ASSERT_TRUE(graph_add_node(graph, node2));
    
    // Add edge with label
    TEST_ASSERT_TRUE(graph_add_edge(graph, node1, node2, &label));
    TEST_ASSERT_TRUE(graph_contains_edge(graph, node1, node2));
    TEST_ASSERT_TRUE(graph_contains_edge(graph, node2, node1)); // undirected
    TEST_ASSERT_EQUAL_INT(1, graph_num_edges(graph));
    
    // Check label
    float* retrieved_label = (float*)graph_get_label(graph, node1, node2);
    TEST_ASSERT_NOT_NULL(retrieved_label);
    TEST_ASSERT_FLOAT_WITHIN(0.001f, label, *retrieved_label);
}

void test_graph_add_duplicate_edge(void) {
    const char* node1 = "A";
    const char* node2 = "B";
    float label1 = 1.5f;
    float label2 = 2.0f;
    
    TEST_ASSERT_TRUE(graph_add_node(graph, node1));
    TEST_ASSERT_TRUE(graph_add_node(graph, node2));
    
    TEST_ASSERT_TRUE(graph_add_edge(graph, node1, node2, &label1));
    TEST_ASSERT_TRUE(graph_add_edge(graph, node1, node2, &label2));
    TEST_ASSERT_EQUAL_INT(1, graph_num_edges(graph)); // Should not add duplicate
}

void test_graph_get_neighbours(void) {
    const char* node1 = "A";
    const char* node2 = "B";
    const char* node3 = "C";
    float label = 1.0f;
    
    TEST_ASSERT_TRUE(graph_add_node(graph, node1));
    TEST_ASSERT_TRUE(graph_add_node(graph, node2));
    TEST_ASSERT_TRUE(graph_add_node(graph, node3));
    
    TEST_ASSERT_TRUE(graph_add_edge(graph, node1, node2, &label));
    TEST_ASSERT_TRUE(graph_add_edge(graph, node1, node3, &label));
    
    void** neighbours = graph_get_neighbours(graph, node1);
    TEST_ASSERT_NOT_NULL(neighbours);
    
    // Check that both neighbours are found
    int found_node2 = 0, found_node3 = 0;
    for (int i = 0; neighbours[i] != NULL; i++) {
        if (strcmp(neighbours[i], node2) == 0) found_node2 = 1;
        if (strcmp(neighbours[i], node3) == 0) found_node3 = 1;
    }
    
    TEST_ASSERT_TRUE(found_node2);
    TEST_ASSERT_TRUE(found_node3);
    
    free(neighbours);
}

void test_graph_remove_node(void) {
    const char* node1 = "A";
    const char* node2 = "B";
    float label = 1.0f;
    
    TEST_ASSERT_TRUE(graph_add_node(graph, node1));
    TEST_ASSERT_TRUE(graph_add_node(graph, node2));
    TEST_ASSERT_TRUE(graph_add_edge(graph, node1, node2, &label));
    
    TEST_ASSERT_TRUE(graph_remove_node(graph, node1));
    TEST_ASSERT_FALSE(graph_contains_node(graph, node1));
    TEST_ASSERT_EQUAL_INT(1, graph_num_nodes(graph));
    TEST_ASSERT_EQUAL_INT(0, graph_num_edges(graph));
}

void test_graph_remove_edge(void) {
    const char* node1 = "A";
    const char* node2 = "B";
    float label = 1.0f;
    
    TEST_ASSERT_TRUE(graph_add_node(graph, node1));
    TEST_ASSERT_TRUE(graph_add_node(graph, node2));
    TEST_ASSERT_TRUE(graph_add_edge(graph, node1, node2, &label));
    
    TEST_ASSERT_TRUE(graph_remove_edge(graph, node1, node2));
    TEST_ASSERT_FALSE(graph_contains_edge(graph, node1, node2));
    TEST_ASSERT_EQUAL_INT(0, graph_num_edges(graph));
}

// BFS Tests
void test_breadth_first_visit(void) {
    const char* node1 = "A";
    const char* node2 = "B";
    const char* node3 = "C";
    float label = 1.0f;
    
    TEST_ASSERT_TRUE(graph_add_node(graph, node1));
    TEST_ASSERT_TRUE(graph_add_node(graph, node2));
    TEST_ASSERT_TRUE(graph_add_node(graph, node3));
    
    TEST_ASSERT_TRUE(graph_add_edge(graph, node1, node2, &label));
    TEST_ASSERT_TRUE(graph_add_edge(graph, node2, node3, &label));
    
    void** result = breadth_first_visit(graph, (void*)node1, test_compare_strings, test_hash_string);
    
    TEST_ASSERT_NOT_NULL(result);
    TEST_ASSERT_EQUAL_STRING(node1, result[0]);
    TEST_ASSERT_EQUAL_STRING(node2, result[1]);
    TEST_ASSERT_EQUAL_STRING(node3, result[2]);
    TEST_ASSERT_NULL(result[3]);
    
    free(result);
}

void test_bfs_single_node(void) {
    const char* node = "SingleNode";
    
    TEST_ASSERT_TRUE(graph_add_node(graph, node));
    
    void** result = breadth_first_visit(graph, (void*)node, test_compare_strings, test_hash_string);
    
    TEST_ASSERT_NOT_NULL(result);
    TEST_ASSERT_EQUAL_STRING(node, result[0]);
    TEST_ASSERT_NULL(result[1]);
    
    free(result);
}

void test_bfs_disconnected_graph(void) {
    const char* node1 = "A";
    const char* node2 = "B";
    const char* node3 = "C";
    const char* node4 = "D";
    float label = 1.0f;
    
    TEST_ASSERT_TRUE(graph_add_node(graph, node1));
    TEST_ASSERT_TRUE(graph_add_node(graph, node2));
    TEST_ASSERT_TRUE(graph_add_node(graph, node3));
    TEST_ASSERT_TRUE(graph_add_node(graph, node4));
    
    TEST_ASSERT_TRUE(graph_add_edge(graph, node1, node2, &label));
    // node3 and node4 are not connected
    
    void** result = breadth_first_visit(graph, (void*)node1, test_compare_strings, test_hash_string);
    
    TEST_ASSERT_NOT_NULL(result);
    TEST_ASSERT_EQUAL_STRING(node1, result[0]);
    TEST_ASSERT_EQUAL_STRING(node2, result[1]);
    TEST_ASSERT_NULL(result[2]);
    
    free(result);
}

void test_bfs_complex_graph(void) {
    // Create a more complex graph structure

    const char* node_a = "A";
    const char* node_b = "B";
    const char* node_c = "C";
    const char* node_d = "D";
    const char* node_e = "E";
    const char* node_f = "F";
    const char* node_g = "G";
    const char* node_h = "H";
    const char* node_i = "I";
    const char* node_j = "J";
    float label = 1.0f;

    // Add all nodes
    TEST_ASSERT_TRUE(graph_add_node(graph, node_a));
    TEST_ASSERT_TRUE(graph_add_node(graph, node_b));
    TEST_ASSERT_TRUE(graph_add_node(graph, node_c));
    TEST_ASSERT_TRUE(graph_add_node(graph, node_d));
    TEST_ASSERT_TRUE(graph_add_node(graph, node_e));
    TEST_ASSERT_TRUE(graph_add_node(graph, node_f));
    TEST_ASSERT_TRUE(graph_add_node(graph, node_g));
    TEST_ASSERT_TRUE(graph_add_node(graph, node_h));
    TEST_ASSERT_TRUE(graph_add_node(graph, node_i));
    TEST_ASSERT_TRUE(graph_add_node(graph, node_j));

    // Add edges to create the graph structure
    TEST_ASSERT_TRUE(graph_add_edge(graph, node_a, node_b, &label));
    TEST_ASSERT_TRUE(graph_add_edge(graph, node_a, node_c, &label));
    TEST_ASSERT_TRUE(graph_add_edge(graph, node_b, node_d, &label));
    TEST_ASSERT_TRUE(graph_add_edge(graph, node_b, node_e, &label));
    TEST_ASSERT_TRUE(graph_add_edge(graph, node_c, node_f, &label));
    TEST_ASSERT_TRUE(graph_add_edge(graph, node_c, node_g, &label));
    TEST_ASSERT_TRUE(graph_add_edge(graph, node_e, node_h, &label));
    TEST_ASSERT_TRUE(graph_add_edge(graph, node_g, node_i, &label));
    TEST_ASSERT_TRUE(graph_add_edge(graph, node_g, node_j, &label));

    // Perform BFS starting from node A
    void** result = breadth_first_visit(graph, (void*)node_a, test_compare_strings, test_hash_string);

    for(size_t i = 0; result[i] != NULL; i++){
        printf("%s\n", (char*)result[i]);
    }

    // Expected BFS order when starting from A
    const char* expected_order[] = {
        node_a,  // First node is A
        node_b,  // Adjacent to A
        node_c,  // Adjacent to A
        node_d,  // Level 2 nodes adjacent to B
        node_e,  // Level 2 nodes adjacent to B
        node_f,  // Level 2 nodes adjacent to C
        node_g,  // Level 2 nodes adjacent to C
        node_h,  // Level 3 node adjacent to E
        node_i,  // Level 3 node adjacent to G
        node_j   // Level 3 node adjacent to G
    };

    // Check the correctness of the BFS traversal order
    for (int i = 0; i < 10; i++) {
        TEST_ASSERT_EQUAL_STRING(expected_order[i], result[i]);
    }
    TEST_ASSERT_NULL(result[10]); // Ensure the list is terminated

    free(result);
}

// Main test runner
int main(void) {
    UNITY_BEGIN();
    
    // Hash Table Tests
    RUN_TEST(test_hash_table_create);
    RUN_TEST(test_hash_table_put_get);
    RUN_TEST(test_hash_table_multiple_puts);
    RUN_TEST(test_hash_table_overwrite);
    RUN_TEST(test_hash_table_contains_key);
    RUN_TEST(test_hash_table_remove);
    RUN_TEST(test_hash_table_keyset);
    
    // Graph Tests
    RUN_TEST(test_graph_create);
    RUN_TEST(test_graph_add_node);
    RUN_TEST(test_graph_add_multiple_nodes);
    RUN_TEST(test_graph_add_edge);
    RUN_TEST(test_graph_add_duplicate_edge);
    RUN_TEST(test_graph_get_neighbours);
    RUN_TEST(test_graph_remove_node);
    RUN_TEST(test_graph_remove_edge);

    RUN_TEST(test_breadth_first_visit);
    RUN_TEST(test_bfs_single_node);
    RUN_TEST(test_bfs_disconnected_graph);
    RUN_TEST(test_bfs_complex_graph);

    return UNITY_END();
}