#include "math.h"

#include <stdlib.h>
#include <string.h>

int ***get_subsets(int n, int **counts)
{
    int i, j;
    long bucket_size;
    int ***res;
    int *current_combination;

    res = malloc(sizeof(int **) * (n + 2));
    for (i = 0; i < n + 2; i++)
    {
        bucket_size = get_bucket_size((n + 1), i);
        res[i] = malloc(sizeof(int *) * bucket_size);
        for (j = 0; j < bucket_size; j++)
        {
            res[i][j] = malloc(sizeof(int) * i);
            memset(res[i][j], -1, sizeof(int) * i);
        }
    }
    *counts = malloc(sizeof(int) * (n + 2));
    memset(*counts, 0, sizeof(int) * (n + 2));
    current_combination = malloc(sizeof(int) * (n + 1));
    memset(current_combination, -1, sizeof(int) * (n + 1));

    fill_buckets_recursive(res, *counts, 0, 0, n, current_combination);
    return res;
}

int fill_buckets_recursive(int ***result, int *bucket_counts, int current_size, int current_elem, int max_elem, int *current_array)
{
    if (current_elem == max_elem)
    { //last elem -> no more recursion
        //Current elem not added
        memcpy(result[current_size][bucket_counts[current_size]], current_array, sizeof(int) * current_size);
        bucket_counts[current_size]++;

        //Current elem added
        current_array[current_size++] = current_elem;
        memcpy(result[current_size][bucket_counts[current_size]], current_array, sizeof(int) * current_size); // add set without current elem
        bucket_counts[current_size]++;
    }
    else
    {
        //Current elem not added
        fill_buckets_recursive(result, bucket_counts, current_size, current_elem + 1, max_elem, current_array);
        //Current elem added
        current_array[current_size++] = current_elem;
        fill_buckets_recursive(result, bucket_counts, current_size, current_elem + 1, max_elem, current_array);
    }

    //cleanup
    current_array[current_size - 1] = -1;
    return 0;
}

long get_bucket_size(int n, int k)
{
    long res;
    res = long_factorial(n);
    res /= long_factorial(k);
    res /= long_factorial(n - k);
    return res;
}

long long_factorial(int n)
{
    long res = 1;
    long i;
    for (i = 1; i <= n; i++)
    {
        res *= i;
    }
    return res;
}

long long_pow(long base, long exp)
{
    long result = 1;
    while (exp)
    {
        if (exp & 1)
            result *= base;
        exp /= 2;
        base *= base;
    }
    return result;
}