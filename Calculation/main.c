#include "graph.h"
#include "math.h"
#include "algorithm.h"
#include <stdio.h>
#include <stdlib.h>



char* get_file_content(char* filename) {
    char * buffer = 0;
    long length;
    FILE * f = fopen(filename, "rb");

    if(!f){
        printf("could not open file\n");
        exit(1);
    }

    fseek(f, 0, SEEK_END);
    length = ftell(f);  
    fseek(f, 0, SEEK_SET);
    buffer = malloc(length);
    if(!buffer) {
        printf("could not malloc\n");
        exit(1);
    }
    fread(buffer, 1, length, f);
    fclose(f);
    return buffer;
}

int main(int argc, char *argv[]) {
    char* dump1 = get_file_content("rand9");
    char* dump2 = get_file_content("rand10");
    graph* g1 = create_graph_from_dump(dump1);
    free(dump1);
    graph* g2 = create_graph_from_dump(dump2);
    free(dump2);
    graph* g = get_exact_best_subgraph(g1,g2,0);

    FILE *f = fopen("out", "w");   
    if (f == NULL) {
        return 1;
    }
    
    dump_graph(f,g);
    fclose(f);
    return 0;
} 
