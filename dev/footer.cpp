

namespace vector_sort
{
    template <typename T>
    void
    sort(T *data, size_t const count); // Entry-point to this module for plain arrays.

    template <typename T>
    void
    sort(std::vector<T> &vec);         // Entry-point to this module for std::vectors.

    bool has_avx2();


#define VECTOR_SORT_FALLBACK_INSERTION_SORT 0

} // namepace vector_sort

template <typename T>
void
vector_sort::internal::sort_recursive(T *unsorted_array, T *tmp_array1, T *tmp_array2, unsigned long n)
{
    if (n < 2)
    {
        return;
    }

    // Recursively sort until partitions are switchPoint-or-less elements in size.
    unsigned long
            low_offset,
            low_count,
            middle_offset,
            middle_count,
            high_offset,
            high_count;
    while (n > vector_sort::internal::switchPoint)
    {
        vector_sort::internal::partition(unsorted_array,
                                                                tmp_array1,
                                                                tmp_array2,
                                                                n,
                                                                low_offset,
                                                                low_count,
                                                                middle_offset,
                                                                middle_count,
                                                                high_offset,
                                                                high_count);
        n = low_count;
        vector_sort::internal::sort_recursive(&unsorted_array[middle_offset], tmp_array1, tmp_array2, middle_count);
        vector_sort::internal::sort_recursive(&unsorted_array[high_offset],   tmp_array1, tmp_array2, high_count);
    }

#if VECTOR_SORT_FALLBACK_INSERTION_SORT
    // Delegate the sorting of partitions of at most switchPoint elements to insertion sort.
    vector_sort::internal::insertion_sort(unsorted_array, n);
#else
    vector_sort::internal::static_sort<T>(unsorted_array, n);
#endif
}

template <typename T>
void
vector_sort::sort(T * const data, size_t const count)
{
    if (vector_sort::has_avx2())
    {
        T * const tmp1 = (T *)malloc(sizeof(T) * count);
        T * const tmp2 = (T *)malloc(sizeof(T) * count);
    
        vector_sort::internal::sort_recursive(data, tmp1, tmp2, count);
    
        free(tmp1);
        free(tmp2);
    }
    else
    {
        std::sort(data, data + count);
    }
}

template <typename T>
void
vector_sort::sort(std::vector<T> &vec)
{
    T *data = &vec[0];
    size_t const count = vec.size();

    vector_sort::sort(data, count);
}

bool vector_sort::has_avx2()
{
    if (!vector_sort::internal::initialized_avx2)
    {
        vector_sort::internal::init_avx2();
    }
    return vector_sort::internal::has_avx2;
}

bool vector_sort::internal::has_avx2(false);

bool vector_sort::internal::initialized_avx2(false);

void vector_sort::internal::init_avx2()
{
    if (vector_sort::internal::initialized_avx2)
    {
        return;
    }
#if defined(__INTEL_COMPILER)
    if (_may_i_use_cpu_feature(_FEATURE_AVX2))
    {
        vector_sort::internal::has_avx2 = true;
    }
#else
#if defined(__GNUC__) && !defined(__clang__)
    __builtin_cpu_init();
#endif
    if (__builtin_cpu_supports("avx2"))
    {
        vector_sort::internal::has_avx2 = true;
    }
#endif
    vector_sort::internal::initialized_avx2 = true;
}

#endif //SIMD_SORT_H_GUARD