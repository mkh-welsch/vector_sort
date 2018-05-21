# vector_sort
a header only SIMD optimized sort implementation for int, float and double primitives.

uses dual pivot sort algorithm for partition sizes greater than 32 and a static sorting network with bose-swaps for fewer.

speedup for sorting 1 Mio random values againt std::sort is 3 - 6 times (depending on type and processor)

## usage
```Cpp
#include "vector_sort.hpp"

std::vector<double> a = {3,2,6,1,5,4};
vector_sort::sort(a);

float[6] b = {3,2,6,1,5,4};
vector_sort::sort(b);
```

## additional infos

The code is highly optimized for intel specific register instructions (AVX2) to vectorize the partitioning process (it's like doing multiprocessing on a single core)

If no AVX2 intrinsics are available, it falls back to std::sort. 

a dual privot sorting is just like a quicksort but with three instead of two partitions. it shows up to 20% more performance than standard quicksort.

the algorithm uses a memory allocation overhead of double the size of the original data.

it only works for alligned data like std::vector or pure arrays.

it may need the flag -march=native to compile and the flag -Ofast to get all the boost.
