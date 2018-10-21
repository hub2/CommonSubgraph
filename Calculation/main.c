#include "graph.h"
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
    // if(argc < 5) {
    //     printf
    // }

    char* dump = get_file_content(argv[1]);
    graph* g = create_graph_from_dump(dump);
    dump_graph(g);
    printf("%d\n", g->size);
} 
