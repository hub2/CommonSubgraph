#include "graph.h"


int init_graph(int size,graph* out) {
    int i;
    
    out->size = size;
    out->data = malloc(sizeof(int*) * size);
    if(!out->data) {
        return -1;
    }
    
    for (i=0;i<size;i++) {
        out->data[i] = malloc(sizeof(int) * size);
        if(!out->data[i]) {
            return -1;
        }
    }

    return 0;
}


int add_edge(int from, int to, graph* g) {
    if(from < 0  || from >= g->size ) {
        printf("add_edge: 'from' value incorrect got %d when max is %d\n", from, g->size-1);
        return -1;
    }
    if(to < 0 || to >= g->size) {
        printf("add_edge: 'to' value incorrect got %d when max is %d\n", to, g->size-1);
        return -1;
    }

    g->data[from][to] = 1;
    g->data[to][from] = 1;
    return 0;
}