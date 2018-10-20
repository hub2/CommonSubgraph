typedef struct {
    int size;
    int** data;
} graph;


int init_graph(int size,graph* out);
int add_edge(int from, int to, graph* g);