#include "graph.h"

typedef struct stack_node
{
    int idx;
    struct stack_node *next;
} stack_node;

typedef struct iso_result
{
    int size;
    int *g1_indices;
    int *g2_indices;
    graph *out_graph;
} iso_result;

iso_result *get_exact_best_subgraph(graph *g1, graph *g2, int count_edges);
iso_result *get_approx_subgraph(graph *g1, graph *g2);