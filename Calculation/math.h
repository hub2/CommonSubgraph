int*** get_subsets(int n,int** out_counts);
long get_bucket_size(int n, int k);
long long_factorial(int n);
long long_pow(long base, long exp);
int fill_buckets_recursive(int*** result,int* bucket_counts,int current_size, int current_elem, int max_elem,int* current_array) ;