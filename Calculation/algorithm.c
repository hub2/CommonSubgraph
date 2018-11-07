#include "algorithm.h"
#include "math.h"

#include <string.h>
#include <stdlib.h>

graph *get_exact_best_subgraph(graph *g1, graph *g2, int count_edges)
{
    int min_vertices = g1->size < g2->size ? g1->size : g2->size;
    int best_graph_size = 0, current_size, max_combination_size;
    int *max_combination;
    int *edge_count = malloc(sizeof(int));
    int **subsets_count_g1 = malloc(sizeof(int *));
    int **subsets_count_g2 = malloc(sizeof(int *));
    int ***combinations_g1 = get_subsets(g1->size - 1, subsets_count_g1);
    int ***combinations_g2 = get_subsets(g2->size - 1, subsets_count_g2);
    int i, j, k;

    // combinations_g1[2] -> [
    //     [1,2],[2,3],[3,1]
    // ]

    for (i = min_vertices; i >= 1; i--)
    { // for each vertices count set
        if (best_graph_size > (i + i * (i - 1) / 2))
        { //even fully connected graph of this size would be too small to beat our best
            goto GraphFound;
        }
        printf("handling subsets of size %d\n", i);
        for (j = 0; j < (*subsets_count_g1)[i]; j++)
        { // for each such subset in g1
            for (k = 0; k < (*subsets_count_g2)[i]; k++)
            { // for each such subset in g2
                if (subset_is_connected(g1, combinations_g1[i][j], i, edge_count))
                { // easier to check and lets count edges here
                    current_size = i;
                    if (count_edges)
                    {
                        current_size += *edge_count;
                    }
                    if (i == 3)
                    {
                        printf("cos tam mam i 3 to mam\n");
                    }

                    if (current_size > best_graph_size)
                    { // need to check only if new graph is bigger
                        if (isomorphic_in_any_perm(g1, g2, combinations_g1[i][j], combinations_g2[i][k], i))
                        {
                            printf("found iso graph ! size: %d, edge_count: %d\n", i, *edge_count);
                            max_combination_size = i;
                            max_combination = combinations_g1[i][j];
                            best_graph_size = current_size;
                            if (!count_edges)
                            { // if edges are not important first graph is best since we start from biggest number of vertices
                                goto GraphFound;
                            }
                        }
                    }
                }
            }
        }
    }
    free(edge_count);
    free(subsets_count_g1);
    free(subsets_count_g2);

GraphFound:
    return from_subset(g1, max_combination, max_combination_size);
}

void swap(int *str, int i, int j)
{
    int temp = str[i];
    str[i] = str[j];
    str[j] = temp;
}

int isomorphic_in_any_perm(graph *g1, graph *g2, int *subset1, int *subset2, int subset_size)
{
    return isomorphic_in_any_perm_rec(g1, g2, subset1, subset2, subset_size, 0);
}

int isomorphic_in_any_perm_rec(graph *g1, graph *g2, int *subset1, int *subset2, int subset_size, int recursion_depth)
{
    int result;
    int i;
    if (recursion_depth == subset_size)
    {
        return isomorphic(g1, g2, subset1, subset2, subset_size);
    }

    result = isomorphic_in_any_perm_rec(g1, g2, subset1, subset2, subset_size, recursion_depth + 1);
    if (result)
    {
        return 1;
    }

    for (i = recursion_depth + 1; i < subset_size; i++)
    {
        if (subset1[recursion_depth] == subset1[i])
            continue;
        swap(subset1, recursion_depth, i);
        result = isomorphic_in_any_perm_rec(g1, g2, subset1, subset2, subset_size, recursion_depth + 1);
        if (result)
        {
            return 1;
        }
        swap(subset1, recursion_depth, i);
    }
    return 0;
}

//subs1 [0,6,7]
//subs2 [0,1,2]
int isomorphic(graph *g1, graph *g2, int *subset1, int *subset2, int subset_size)
{
    int i, j, mapped_i, mapped_j;

    for (i = 0; i < subset_size; i++)
    {
        for (j = i + 1; j < subset_size; j++)
        {
            if (!g1->data[subset1[i]][subset1[j]])
            { // i - j  edge does not exist
                continue;
            }

            // i and j are connected , lets check corespsonding edge in g2
            mapped_i = subset2[i];
            mapped_j = subset2[j];
            if (!g2->data[mapped_i][mapped_j])
            {
                return 0;
            }
        }
    }

    //All edges from subset 1 are in subset 2
    //Lets check reverse
    for (i = 0; i < subset_size; i++)
    {
        for (j = i + 1; j < subset_size; j++)
        {

            if (!g2->data[subset2[i]][subset2[j]])
            { // i - j  edge does not exist
                continue;
            }

            mapped_i = subset1[i];
            mapped_j = subset1[j];
            if (!g1->data[mapped_i][mapped_j])
            {
                return 0;
            }
        }
    }

    return 1;
}

int subset_is_connected(graph *g, int *subset, int subset_size, int *edge_count)
{
    int i;
    stack_node *curr;
    stack_node *tmp;
    stack_node *stack;

    int *visited = malloc(sizeof(int) * subset_size);
    int *reverse_lookup = malloc(sizeof(int) * g->size);
    memset(visited, 0, sizeof(int) * subset_size);
    memset(reverse_lookup, -1, sizeof(int) * g->size);
    stack = malloc(sizeof(stack_node));
    stack->next = NULL;
    stack->idx = subset[0];
    *edge_count = 0;

    for (i = 0; i < subset_size; i++)
    {
        reverse_lookup[subset[i]] = i;
    }

    visited[0] = 1;

    while (stack)
    {
        curr = stack;
        stack = stack->next;
        for (i = 0; i < g->size; i++)
        {
            if (i == curr->idx)
                continue;
            if (g->data[curr->idx][i])
            {
                if (reverse_lookup[i] != -1)
                {
                    *edge_count = (*edge_count) + 1;
                    if (!visited[reverse_lookup[i]])
                    {
                        visited[reverse_lookup[i]] = 1;
                        tmp = malloc(sizeof(stack_node));
                        tmp->next = stack;
                        tmp->idx = i;
                        stack = tmp;
                    }
                }
            }
        }
        free(curr);
    }
    free(reverse_lookup);
    for (i = 0; i < subset_size; i++)
    {
        if (!visited[i])
        {
            free(visited);
            return 0;
        }
    }
    free(visited);
    return 1;
}

void add_unique(int value, stack_node **stack)
{
    stack_node *current = *stack;
    stack_node *new_node;
    while (current)
    {
        if (current->idx == value)
        {
            return;
        }
        current = current->next;
    }

    new_node = malloc(sizeof(stack_node));
    new_node->idx = value;
    new_node->next = *stack;
    *stack = new_node;
    return;
}

void fill_with_neighbours(graph *g, int idx, stack_node **stack)
{
    int j;
    for (j = 0; j < g->size; j++)
    {
        if (g->data[j][idx])
        {
            add_unique(j, stack);
        }
    }
}

void remove_value(stack_node **stack, int idx)
{
    stack_node *current = *stack;
    stack_node *prev;
    while (current)
    {
        if (current->idx == idx)
        {
            if(current == *stack) {
                *stack = current->next;
                return;
            }
            prev->next = current->next;
            return;
        }
        prev = current;
        current = current->next;
    }
}

graph *get_approx_subgraph(graph *g1, graph *g2)
{
    stack_node *g1_candidates = NULL;
    stack_node *g2_candidates = NULL;
    int *g1_sub_indices = malloc(sizeof(int) * g1->size);
    int *g2_sub_indices = malloc(sizeof(int) * g2->size);
    memset(g1_sub_indices, -1, sizeof(int) * g1->size);
    memset(g2_sub_indices, -1, sizeof(int) * g2->size);

    //These lists are used to check fast if given idx was lookup to subgraph. 
    //if(g1_subgraph_idx_lookup[i]) -> i-th vertex from g1 is in subgraph_g1 at index of value in array
    int *g1_subgraph_idx_lookup = malloc(sizeof(int) * g1->size);
    int *g2_subgraph_idx_lookup = malloc(sizeof(int) * g2->size);
    memset(g1_sub_indices, 0, sizeof(int) * g1->size);
    memset(g2_sub_indices, 0, sizeof(int) * g2->size);

    int vertices = 1;

    g1_sub_indices[0] = 0;
    g1_subgraph_idx_lookup[0] = 1;
    g2_sub_indices[0] = 0;
    g2_subgraph_idx_lookup[0] = 1;

    fill_with_neighbours(g1, 0, &g1_candidates);
    fill_with_neighbours(g2, 0, &g2_candidates);

    int vertex_found = 1;
    while (vertex_found)
    {
        vertex_found = 0;
        stack_node *g1_candidate = g1_candidates;
        while (g1_candidate)
        {
            stack_node *g2_candidate = g2_candidates;
            while (g2_candidate)
            {
                int all_edges_match = 1;
                for (register int i = 0; i < g1->size; i++)
                {
                    if (!g1_subgraph_idx_lookup[i]) // i is not in subgraph of g1
                        continue;
                    if (g1->data[g1_candidate->idx][i])
                    {
                        int mapped_i = g2_sub_indices[g1_subgraph_idx_lookup[i]];
                        if (!g2->data[g2_candidate->idx][mapped_i])
                        {
                            all_edges_match = 0;
                            break;
                        }
                    }
                }

                if (all_edges_match)
                {
                    for (register int i = 0; i < g2->size; i++)
                    {
                        if (!g2_subgraph_idx_lookup[i]) // i is not in subgraph of g2
                            continue;
                        if (g2->data[g2_candidate->idx][i]) 
                        {
                            int mapped_i = g1_sub_indices[g2_subgraph_idx_lookup[i]];
                            if (!g1->data[g1_candidate->idx][mapped_i])
                            {
                                all_edges_match = 0;
                                break;
                            }
                        }
                    }
                }

                if (all_edges_match)
                {
                    fill_with_neighbours(g1, g1_candidate->idx, &g1_candidates);
                    remove_value(&g1_candidates, g1_candidate->idx);
                    g1_sub_indices[vertices] = g1_candidate->idx;
                    free(g1_candidate);

                    fill_with_neighbours(g2, g2_candidate->idx, &g2_candidates);
                    remove_value(&g2_candidates, g2_candidate->idx);
                    g2_sub_indices[vertices] = g2_candidate->idx;
                    free(g2_candidate);

                    vertices++;
                    vertex_found = 1;
                }

                if (vertex_found)
                    break;
                g2_candidate = g2_candidate->next;
            }
            if (vertex_found)
                break;
            g1_candidate = g1_candidate->next;
        }
    }

    free(g1_subgraph_idx_lookup);
    free(g2_subgraph_idx_lookup);
    return from_subset(g1, g1_sub_indices, vertices);
}
