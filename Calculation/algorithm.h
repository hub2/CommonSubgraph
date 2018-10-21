#include "graph.h"

typedef struct stack_node{
    int idx;
    struct stack_node* next;
} stack_node;

int isomorphic_in_any_perm(graph* g1, graph* g2, int* subset1, int* subset2, int subset_size);
int isomorphic_in_any_perm_rec(graph* g1, graph* g2, int* subset1, int* subset2, int subset_size, int recursion_depth);
int isomorphic(graph* g1, graph* g2, int* subset1, int* subset2, int subset_size);
int subset_is_connected(graph* g,int* subset,int subset_size,int* edge_count);
graph* get_exact_best_subgraph(graph* g1,  graph* g2, int count_edges);