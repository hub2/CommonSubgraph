#include "graph.h"
#include "math.h"
#include "algorithm.h"
#include <stdio.h>
#include <stdlib.h>

char *get_file_content(char *filename)
{
    char *buffer = 0;
    long length;
    FILE *f = fopen(filename, "rb");

    if (!f)
    {
        printf("could not open file\n");
        exit(1);
    }

    fseek(f, 0, SEEK_END);
    length = ftell(f);
    fseek(f, 0, SEEK_SET);
    buffer = malloc(length);
    if (!buffer)
    {
        printf("could not malloc\n");
        exit(1);
    }
    fread(buffer, 1, length, f);
    fclose(f);
    return buffer;
}

void print_mapping(iso_result *res)
{
    printf("mapping: \n");
    for (int i = 0; i < res->size; i++)
    {
        printf("%d", res->g1_indices[i]);
        if (i + 1 != res->size)
        {
            printf(",");
        }
    }
    puts("");

    for (int i = 0; i < res->size; i++)
    {
        printf("%d", res->g2_indices[i]);
        if (i + 1 != res->size)
        {
            printf(",");
        }
    }
    puts("");
}

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        printf("provide 2 paths for graph dumps\n");
        exit(1);
    }

    char *dump1 = get_file_content(argv[1]);
    char *dump2 = get_file_content(argv[2]);
    graph *g1 = create_graph_from_dump(dump1);
    free(dump1);
    graph *g2 = create_graph_from_dump(dump2);
    free(dump2);

    // iso_result *res = get_exact_best_subgraph(g1, g2, 0);
    iso_result *res = get_approx_subgraph(g1, g2);

    FILE *f = fopen("out", "w");
    if (f == NULL)
    {
        return 1;
    }

    print_mapping(res);
    dump_graph(f, res->out_graph);
    fclose(f);
    return 0;
}
