#include "graph.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

graph* init_graph(int size) {
    int i;
    graph* out;

    out = malloc(sizeof(graph));
    if(!out) {
        printf("malloc returned err\n");
        exit(1);
    }

    out->size = size;
    out->data = malloc(sizeof(int*) * size);
    if(!out->data) {
        printf("malloc returned err\n");
        exit(1);
    }
    
    for (i=0;i<size;i++) {
        out->data[i] = malloc(sizeof(int) * size);
        if(!out->data[i]) {
            printf("malloc returned err\n");
            exit(1);
        }
    }

    return out;
}

int dump_graph(FILE* file, graph* g) {
    int i,j;
    fprintf(file,"%d\n",g->size);
    for (i=0;i<g->size;i++){
        for(j=0;j<g->size;j++) {
            fprintf(file,"%d",g->data[i][j]);
            if(j!=g->size-1) {
                fprintf(file,",");
            }
        }
        fprintf(file,"\n");
    }
}

graph* create_graph_from_dump(char* dump) {
    char* token;
    char* line;
    char* next;
    int got_size=0,tokens_count,line_number=0;
    long tmp;
    graph* out;

    while (line = strsep(&dump, "\n")) {
        next = line; //strsep needs it not to be null
        if(got_size) {
            tokens_count = 0;
            while (tokens_count < out->size) {
                    token = strsep(&line, ",");
                    tmp = strtol(token,&next,10);
                    if (next == token) { // no chars converted
                        printf("bad value for line_number=%d, tokens_count=%d\n",line_number,tokens_count);
                        exit(1);
                    }
                    if(tmp) {
                        out->data[line_number][tokens_count] = 1;
                    } else {
                        out->data[line_number][tokens_count] = 0;
                    }
                    tokens_count++;
            }
            line_number++;
            if(line_number == out->size) {
                break;
            }
        } else {
            tmp = strtol(line,NULL,10);
            if (next == token) {
                printf("incorrect rows number\n");
                exit(1);
            }
            got_size = 1;
            out = init_graph((int)tmp);
        }
    }
    return out;
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