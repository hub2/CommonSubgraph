#pragma once
#include<stdio.h> 

typedef struct {
    int size;
    int** data; 
} graph;

graph* create_graph_from_dump(char* dump);
graph* init_graph(int size);
int dump_graph(FILE* f, graph* g);
int add_edge(int from, int to, graph* g); 
graph* from_subset(graph* g,int* subset,int subset_size);