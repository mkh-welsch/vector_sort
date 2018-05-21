/*
      |                |            _)                |                           |   
   _` |  |   |   _` |  |      __ \   | \ \   /  _ \   __|       __|   _ \    __|  __| 
  (   |  |   |  (   |  |      |   |  |  \ \ /  (   |  |       \__ \  (   |  |     |   
 \__,_| \__,_| \__,_| _|      .__/  _|   \_/  \___/  \__|     ____/ \___/  _|    \__| 
                             _|                                                       
                                        Copyright (c) 2018 M. Welsch <michael@welsch.one>
                            Copyright (c) 2018 S. D. Adams <s.d.adams.software@gmail.com>
*/


namespace vector_sort
{
    namespace internal // Implementation details.
    {
        extern bool has_avx2;
        extern bool initialized_avx2;
        void init_avx2();

        static __attribute__((aligned(64))) int PTL[16 * 8] = {
            0, 0, 0, 0, 0, 0, 0, 0,
            0, 1, 0, 0, 0, 0, 0, 0,
            2, 3, 0, 0, 0, 0, 0, 0,
            0, 1, 2, 3, 0, 0, 0, 0,
            4, 5, 0, 0, 0, 0, 0, 0,
            0, 1, 4, 5, 0, 0, 0, 0,
            2, 3, 4, 5, 0, 0, 0, 0,
            0, 1, 2, 3, 4, 5, 0, 0,
            6, 7, 0, 0, 0, 0, 0, 0,
            0, 1, 6, 7, 0, 0, 0, 0,
            2, 3, 6, 7, 0, 0, 0, 0,
            0, 1, 2, 3, 6, 7, 0, 0,
            4, 5, 6, 7, 0, 0, 0, 0,
            0, 1, 4, 5, 6, 7, 0, 0,
            2, 3, 4, 5, 6, 7, 0, 0,
            0, 1, 2, 3, 4, 5, 6, 7
        };

        static __attribute__((aligned(64))) int PTL2[256 * 8] = {
            0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,
            1,0,0,0,0,0,0,0,
            0,1,0,0,0,0,0,0,
            2,0,0,0,0,0,0,0,
            0,2,0,0,0,0,0,0,
            1,2,0,0,0,0,0,0,
            0,1,2,0,0,0,0,0,
            3,0,0,0,0,0,0,0,
            0,3,0,0,0,0,0,0,
            1,3,0,0,0,0,0,0,
            0,1,3,0,0,0,0,0,
            2,3,0,0,0,0,0,0,
            0,2,3,0,0,0,0,0,
            1,2,3,0,0,0,0,0,
            0,1,2,3,0,0,0,0,
            4,0,0,0,0,0,0,0,
            0,4,0,0,0,0,0,0,
            1,4,0,0,0,0,0,0,
            0,1,4,0,0,0,0,0,
            2,4,0,0,0,0,0,0,
            0,2,4,0,0,0,0,0,
            1,2,4,0,0,0,0,0,
            0,1,2,4,0,0,0,0,
            3,4,0,0,0,0,0,0,
            0,3,4,0,0,0,0,0,
            1,3,4,0,0,0,0,0,
            0,1,3,4,0,0,0,0,
            2,3,4,0,0,0,0,0,
            0,2,3,4,0,0,0,0,
            1,2,3,4,0,0,0,0,
            0,1,2,3,4,0,0,0,
            5,0,0,0,0,0,0,0,
            0,5,0,0,0,0,0,0,
            1,5,0,0,0,0,0,0,
            0,1,5,0,0,0,0,0,
            2,5,0,0,0,0,0,0,
            0,2,5,0,0,0,0,0,
            1,2,5,0,0,0,0,0,
            0,1,2,5,0,0,0,0,
            3,5,0,0,0,0,0,0,
            0,3,5,0,0,0,0,0,
            1,3,5,0,0,0,0,0,
            0,1,3,5,0,0,0,0,
            2,3,5,0,0,0,0,0,
            0,2,3,5,0,0,0,0,
            1,2,3,5,0,0,0,0,
            0,1,2,3,5,0,0,0,
            4,5,0,0,0,0,0,0,
            0,4,5,0,0,0,0,0,
            1,4,5,0,0,0,0,0,
            0,1,4,5,0,0,0,0,
            2,4,5,0,0,0,0,0,
            0,2,4,5,0,0,0,0,
            1,2,4,5,0,0,0,0,
            0,1,2,4,5,0,0,0,
            3,4,5,0,0,0,0,0,
            0,3,4,5,0,0,0,0,
            1,3,4,5,0,0,0,0,
            0,1,3,4,5,0,0,0,
            2,3,4,5,0,0,0,0,
            0,2,3,4,5,0,0,0,
            1,2,3,4,5,0,0,0,
            0,1,2,3,4,5,0,0,
            6,0,0,0,0,0,0,0,
            0,6,0,0,0,0,0,0,
            1,6,0,0,0,0,0,0,
            0,1,6,0,0,0,0,0,
            2,6,0,0,0,0,0,0,
            0,2,6,0,0,0,0,0,
            1,2,6,0,0,0,0,0,
            0,1,2,6,0,0,0,0,
            3,6,0,0,0,0,0,0,
            0,3,6,0,0,0,0,0,
            1,3,6,0,0,0,0,0,
            0,1,3,6,0,0,0,0,
            2,3,6,0,0,0,0,0,
            0,2,3,6,0,0,0,0,
            1,2,3,6,0,0,0,0,
            0,1,2,3,6,0,0,0,
            4,6,0,0,0,0,0,0,
            0,4,6,0,0,0,0,0,
            1,4,6,0,0,0,0,0,
            0,1,4,6,0,0,0,0,
            2,4,6,0,0,0,0,0,
            0,2,4,6,0,0,0,0,
            1,2,4,6,0,0,0,0,
            0,1,2,4,6,0,0,0,
            3,4,6,0,0,0,0,0,
            0,3,4,6,0,0,0,0,
            1,3,4,6,0,0,0,0,
            0,1,3,4,6,0,0,0,
            2,3,4,6,0,0,0,0,
            0,2,3,4,6,0,0,0,
            1,2,3,4,6,0,0,0,
            0,1,2,3,4,6,0,0,
            5,6,0,0,0,0,0,0,
            0,5,6,0,0,0,0,0,
            1,5,6,0,0,0,0,0,
            0,1,5,6,0,0,0,0,
            2,5,6,0,0,0,0,0,
            0,2,5,6,0,0,0,0,
            1,2,5,6,0,0,0,0,
            0,1,2,5,6,0,0,0,
            3,5,6,0,0,0,0,0,
            0,3,5,6,0,0,0,0,
            1,3,5,6,0,0,0,0,
            0,1,3,5,6,0,0,0,
            2,3,5,6,0,0,0,0,
            0,2,3,5,6,0,0,0,
            1,2,3,5,6,0,0,0,
            0,1,2,3,5,6,0,0,
            4,5,6,0,0,0,0,0,
            0,4,5,6,0,0,0,0,
            1,4,5,6,0,0,0,0,
            0,1,4,5,6,0,0,0,
            2,4,5,6,0,0,0,0,
            0,2,4,5,6,0,0,0,
            1,2,4,5,6,0,0,0,
            0,1,2,4,5,6,0,0,
            3,4,5,6,0,0,0,0,
            0,3,4,5,6,0,0,0,
            1,3,4,5,6,0,0,0,
            0,1,3,4,5,6,0,0,
            2,3,4,5,6,0,0,0,
            0,2,3,4,5,6,0,0,
            1,2,3,4,5,6,0,0,
            0,1,2,3,4,5,6,0,
            7,0,0,0,0,0,0,0,
            0,7,0,0,0,0,0,0,
            1,7,0,0,0,0,0,0,
            0,1,7,0,0,0,0,0,
            2,7,0,0,0,0,0,0,
            0,2,7,0,0,0,0,0,
            1,2,7,0,0,0,0,0,
            0,1,2,7,0,0,0,0,
            3,7,0,0,0,0,0,0,
            0,3,7,0,0,0,0,0,
            1,3,7,0,0,0,0,0,
            0,1,3,7,0,0,0,0,
            2,3,7,0,0,0,0,0,
            0,2,3,7,0,0,0,0,
            1,2,3,7,0,0,0,0,
            0,1,2,3,7,0,0,0,
            4,7,0,0,0,0,0,0,
            0,4,7,0,0,0,0,0,
            1,4,7,0,0,0,0,0,
            0,1,4,7,0,0,0,0,
            2,4,7,0,0,0,0,0,
            0,2,4,7,0,0,0,0,
            1,2,4,7,0,0,0,0,
            0,1,2,4,7,0,0,0,
            3,4,7,0,0,0,0,0,
            0,3,4,7,0,0,0,0,
            1,3,4,7,0,0,0,0,
            0,1,3,4,7,0,0,0,
            2,3,4,7,0,0,0,0,
            0,2,3,4,7,0,0,0,
            1,2,3,4,7,0,0,0,
            0,1,2,3,4,7,0,0,
            5,7,0,0,0,0,0,0,
            0,5,7,0,0,0,0,0,
            1,5,7,0,0,0,0,0,
            0,1,5,7,0,0,0,0,
            2,5,7,0,0,0,0,0,
            0,2,5,7,0,0,0,0,
            1,2,5,7,0,0,0,0,
            0,1,2,5,7,0,0,0,
            3,5,7,0,0,0,0,0,
            0,3,5,7,0,0,0,0,
            1,3,5,7,0,0,0,0,
            0,1,3,5,7,0,0,0,
            2,3,5,7,0,0,0,0,
            0,2,3,5,7,0,0,0,
            1,2,3,5,7,0,0,0,
            0,1,2,3,5,7,0,0,
            4,5,7,0,0,0,0,0,
            0,4,5,7,0,0,0,0,
            1,4,5,7,0,0,0,0,
            0,1,4,5,7,0,0,0,
            2,4,5,7,0,0,0,0,
            0,2,4,5,7,0,0,0,
            1,2,4,5,7,0,0,0,
            0,1,2,4,5,7,0,0,
            3,4,5,7,0,0,0,0,
            0,3,4,5,7,0,0,0,
            1,3,4,5,7,0,0,0,
            0,1,3,4,5,7,0,0,
            2,3,4,5,7,0,0,0,
            0,2,3,4,5,7,0,0,
            1,2,3,4,5,7,0,0,
            0,1,2,3,4,5,7,0,
            6,7,0,0,0,0,0,0,
            0,6,7,0,0,0,0,0,
            1,6,7,0,0,0,0,0,
            0,1,6,7,0,0,0,0,
            2,6,7,0,0,0,0,0,
            0,2,6,7,0,0,0,0,
            1,2,6,7,0,0,0,0,
            0,1,2,6,7,0,0,0,
            3,6,7,0,0,0,0,0,
            0,3,6,7,0,0,0,0,
            1,3,6,7,0,0,0,0,
            0,1,3,6,7,0,0,0,
            2,3,6,7,0,0,0,0,
            0,2,3,6,7,0,0,0,
            1,2,3,6,7,0,0,0,
            0,1,2,3,6,7,0,0,
            4,6,7,0,0,0,0,0,
            0,4,6,7,0,0,0,0,
            1,4,6,7,0,0,0,0,
            0,1,4,6,7,0,0,0,
            2,4,6,7,0,0,0,0,
            0,2,4,6,7,0,0,0,
            1,2,4,6,7,0,0,0,
            0,1,2,4,6,7,0,0,
            3,4,6,7,0,0,0,0,
            0,3,4,6,7,0,0,0,
            1,3,4,6,7,0,0,0,
            0,1,3,4,6,7,0,0,
            2,3,4,6,7,0,0,0,
            0,2,3,4,6,7,0,0,
            1,2,3,4,6,7,0,0,
            0,1,2,3,4,6,7,0,
            5,6,7,0,0,0,0,0,
            0,5,6,7,0,0,0,0,
            1,5,6,7,0,0,0,0,
            0,1,5,6,7,0,0,0,
            2,5,6,7,0,0,0,0,
            0,2,5,6,7,0,0,0,
            1,2,5,6,7,0,0,0,
            0,1,2,5,6,7,0,0,
            3,5,6,7,0,0,0,0,
            0,3,5,6,7,0,0,0,
            1,3,5,6,7,0,0,0,
            0,1,3,5,6,7,0,0,
            2,3,5,6,7,0,0,0,
            0,2,3,5,6,7,0,0,
            1,2,3,5,6,7,0,0,
            0,1,2,3,5,6,7,0,
            4,5,6,7,0,0,0,0,
            0,4,5,6,7,0,0,0,
            1,4,5,6,7,0,0,0,
            0,1,4,5,6,7,0,0,
            2,4,5,6,7,0,0,0,
            0,2,4,5,6,7,0,0,
            1,2,4,5,6,7,0,0,
            0,1,2,4,5,6,7,0,
            3,4,5,6,7,0,0,0,
            0,3,4,5,6,7,0,0,
            1,3,4,5,6,7,0,0,
            0,1,3,4,5,6,7,0,
            2,3,4,5,6,7,0,0,
            0,2,3,4,5,6,7,0,
            1,2,3,4,5,6,7,0,
            0,1,2,3,4,5,6,7
        };

        template <typename T>
        void
        partition(T *in,
                  T *tmp1,
                  T *tmp2,
                  unsigned long n,
                  unsigned long &out_bottom_offset,
                  unsigned long &out_bottom_count,
                  unsigned long &out_middle_offset,
                  unsigned long &out_middle_count,
                  unsigned long &out_top_offset,
                  unsigned long &out_top_count);

        template <typename T>
        void
        insertion_sort(T *d, unsigned long n);

        template <typename T>
        void
        partition_avx2(T *&in,
                       unsigned long &n,
                       T pivot1,
                       T pivot2,
                       T *&bottom,
                       T *&middle,
                       T *&top);

        template <typename T>
        void
        partition_avx2(T *&in,
                       unsigned long &n,
                       T pivot,
                       T *&bottom,
                       T *&middle,
                       T *&top);

        void
        partition_4d(double *&in,
                     __m256d &PIVOT_L,
                     __m256d &PIVOT_H,
                     double *&bottom,
                     double *&middle,
                     double *&top);
        void
        partition_4d(double *&in,
                     __m256d &PIVOT,
                     double *&bottom,
                     double *&middle,
                     double *&top);

        void
        partition_8f(float *&in,
                     __m256 &PIVOT_L,
                     __m256 &PIVOT_H,
                     float *&bottom,
                     float *&middle,
                     float *&top);
        void
        partition_8f(float *&in,
                     __m256 &PIVOT,
                     float *&bottom,
                     float *&middle,
                     float *&top);

        void
        partition_8i(int *&in,
                     __m256i &PIVOT_L,
                     __m256i &PIVOT_H,
                     int *&bottom,
                     int *&middle,
                     int *&top);
        void
        partition_8i(int *&in,
                     __m256i &PIVOT,
                     int *&bottom,
                     int *&middle,
                     int *&top);

        template <typename T>
        void
        sort_recursive(T *unsorted_array, T *tmp_array1, T *tmp_array2, unsigned long n);
    } // end namespace internal
} // end namespace vector_sort

template <typename T>
void vector_sort::internal::insertion_sort(T * const data, unsigned long const count)
{
    if (count <= 1)
    {
        return;
    }

    long i, j;
    for (i = 1; i < count; i++)
    {
        T tmp = data[i];
        for (j = i; j >= 1 && tmp < data[j - 1]; j--)
            data[j] = data[j - 1];
        data[j] = tmp;
    }
}

// Separates 4 doubles into 3 partitions using AVX2.
inline
void
vector_sort::internal::partition_4d(double *&in,
                                    __m256d &PIVOT_L,
                                    __m256d &PIVOT_H,
                                    double *&bottom,
                                    double *&middle,
                                    double *&top)
{
    __m256d INPUT;
    __m256d LOW;
    __m256d MED;
    __m256d HIGH;

    INPUT = _mm256_loadu_pd(in);                     // Load 4 doubles.
    MED = _mm256_cmp_pd(INPUT, PIVOT_L, _CMP_LE_OQ); // Compare less than or equal to the low pivot.
    unsigned long lmask = _mm256_movemask_pd(MED);   // Convert the 4 comparisons to bits in lmask.
    MED = _mm256_cmp_pd(INPUT, PIVOT_H, _CMP_GE_OQ); // Compare greater than or equal to the high pivot.
    unsigned long hmask = _mm256_movemask_pd(MED);   // Convert the 4 comparisons to bits in hmask.
    unsigned long mmask = 0xF & (~lmask & ~hmask);   // Compute the comparisons that produced false for both tests.

    // Partition using the comparisons to index into a permuation array.
    LOW  = (__m256d)_mm256_permutevar8x32_ps((__m256)INPUT, ((__m256i *)PTL)[lmask]);
    MED  = (__m256d)_mm256_permutevar8x32_ps((__m256)INPUT, ((__m256i *)PTL)[mmask]);
    HIGH = (__m256d)_mm256_permutevar8x32_ps((__m256)INPUT, ((__m256i *)PTL)[hmask]);

    // Store unaligned the partitioned values in the corresponding array.
    _mm256_storeu_pd(bottom, LOW);
    _mm256_storeu_pd(middle, MED);
    _mm256_storeu_pd(top, HIGH);

    // Shift the partition bounds by the number of elements stored.
    bottom += __builtin_popcount(lmask);
    middle += __builtin_popcount(mmask);
    top    += __builtin_popcount(hmask);

    in += 4;
}
inline
void
vector_sort::internal::partition_4d(double *&in,
                                    __m256d &PIVOT,
                                    double *&bottom,
                                    double *&middle,
                                    double *&top)
{
    __m256d INPUT;
    __m256d LOW;
    __m256d MED;
    __m256d HIGH;

    INPUT = _mm256_loadu_pd(in);                   // Load 4 doubles.
    MED = _mm256_cmp_pd(INPUT, PIVOT, _CMP_LT_OQ); // Compare less than or equal to the low pivot.
    unsigned long lmask = _mm256_movemask_pd(MED); // Convert the 4 comparisons to bits in lmask.
    MED = _mm256_cmp_pd(INPUT, PIVOT, _CMP_GT_OQ); // Compare greater than or equal to the high pivot.
    unsigned long hmask = _mm256_movemask_pd(MED); // Convert the 4 comparisons to bits in hmask.
    unsigned long mmask = 0xF & (~lmask & ~hmask); // Compute the comparisons that produced false for both tests.

    // Partition using the comparisons to index into a permuation array.
    LOW  = (__m256d)_mm256_permutevar8x32_ps((__m256)INPUT, ((__m256i *)PTL)[lmask]);
    MED  = (__m256d)_mm256_permutevar8x32_ps((__m256)INPUT, ((__m256i *)PTL)[mmask]);
    HIGH = (__m256d)_mm256_permutevar8x32_ps((__m256)INPUT, ((__m256i *)PTL)[hmask]);

    // Store unaligned the partitioned values in the corresponding array.
    _mm256_storeu_pd(bottom, LOW);
    _mm256_storeu_pd(middle, MED);
    _mm256_storeu_pd(top, HIGH);

    // Shift the partition bounds by the number of elements stored.
    bottom += __builtin_popcount(lmask);
    middle += __builtin_popcount(mmask);
    top    += __builtin_popcount(hmask);

    in += 4;
}

// Separates 8 floats into 3 partitions using AVX2.
inline
void
vector_sort::internal::partition_8f(float *&in,
                                    __m256 &PIVOT_L,
                                    __m256 &PIVOT_H,
                                    float *&bottom,
                                    float *&middle,
                                    float *&top)
{
    __m256 INPUT;
    __m256 LOW;
    __m256 MED;
    __m256 HIGH;

    INPUT = _mm256_loadu_ps(in);                    // Load 8 floats.
    MED = _mm256_cmp_ps(INPUT, PIVOT_L, _CMP_LE_OQ);         // Compare less than or equal to the low pivot.
    unsigned long lmask = _mm256_movemask_ps(MED);  // Convert the 8 comparisons to bits in lmask.
    MED = _mm256_cmp_ps(INPUT, PIVOT_H, _CMP_GE_OQ);        // Compare greater than or equal to the high pivot.
    unsigned long hmask = _mm256_movemask_ps(MED);  // Convert the 8 comparisons to bits in hmask.
    unsigned long mmask = 0xFF & (~lmask & ~hmask); // Compute the comparisons that produced false for both tests.

    // Partition using the comparisons to index into a permuation array.
    LOW  = _mm256_permutevar8x32_ps(INPUT, ((__m256i *)PTL2)[lmask]);
    MED  = _mm256_permutevar8x32_ps(INPUT, ((__m256i *)PTL2)[mmask]);
    HIGH = _mm256_permutevar8x32_ps(INPUT, ((__m256i *)PTL2)[hmask]);

    // Store unaligned the partitioned values in the corresponding array.
    _mm256_storeu_ps(bottom, LOW);
    _mm256_storeu_ps(middle, MED);
    _mm256_storeu_ps(top, HIGH);

    // Shift the partition bounds by the number of elements stored.
    bottom += __builtin_popcount(lmask);
    middle += __builtin_popcount(mmask);
    top    += __builtin_popcount(hmask);

    in += 8;
}
inline
void
vector_sort::internal::partition_8f(float *&in,
                                    __m256 &PIVOT,
                                    float *&bottom,
                                    float *&middle,
                                    float *&top)
{
    __m256 INPUT;
    __m256 LOW;
    __m256 MED;
    __m256 HIGH;

    INPUT = _mm256_loadu_ps(in);                    // Load 8 floats.
    MED = _mm256_cmp_ps(INPUT, PIVOT, _CMP_LT_OQ);         // Compare less than or equal to the low pivot.
    unsigned long lmask = _mm256_movemask_ps(MED);  // Convert the 8 comparisons to bits in lmask.
    MED = _mm256_cmp_ps(INPUT, PIVOT, _CMP_GT_OQ);        // Compare greater than or equal to the high pivot.
    unsigned long hmask = _mm256_movemask_ps(MED);  // Convert the 8 comparisons to bits in hmask.
    unsigned long mmask = 0xFF & (~lmask & ~hmask); // Compute the comparisons that produced false for both tests.

    // Partition using the comparisons to index into a permuation array.
    LOW  = _mm256_permutevar8x32_ps(INPUT, ((__m256i *)PTL2)[lmask]);
    MED  = _mm256_permutevar8x32_ps(INPUT, ((__m256i *)PTL2)[mmask]);
    HIGH = _mm256_permutevar8x32_ps(INPUT, ((__m256i *)PTL2)[hmask]);

    // Store unaligned the partitioned values in the corresponding array.
    _mm256_storeu_ps(bottom, LOW);
    _mm256_storeu_ps(middle, MED);
    _mm256_storeu_ps(top, HIGH);

    // Shift the partition bounds by the number of elements stored.
    bottom += __builtin_popcount(lmask);
    middle += __builtin_popcount(mmask);
    top    += __builtin_popcount(hmask);

    in += 8;
}

// Separates 8 ints into 3 partitions using AVX2.
inline
void
vector_sort::internal::partition_8i(int *&in,
                                    __m256i &PIVOT_L,
                                    __m256i &PIVOT_H,
                                    int *&bottom,
                                    int *&middle,
                                    int *&top)
{
    __m256i INPUT;
    __m256i LOW;
    __m256i MED;
    __m256i HIGH;

    INPUT = _mm256_loadu_si256((__m256i *)in);       // Load 8 ints.
    __m256i LMASK_LT = _mm256_cmpgt_epi32(PIVOT_L, INPUT);        // Compare less than the low pivot.
    __m256i LMASK_EQ = _mm256_cmpeq_epi32(PIVOT_L, INPUT);        // Compare equal to the low pivot.
    __m256i HMASK_GT = _mm256_cmpgt_epi32(INPUT, PIVOT_H);        // Compare greater than the high pivot.
    __m256i HMASK_EQ = _mm256_cmpeq_epi32(INPUT, PIVOT_H);        // Compare equal to the high pivot.
    __m256i LMASK = _mm256_or_si256(LMASK_LT, LMASK_EQ);
    __m256i HMASK = _mm256_or_si256(HMASK_GT, HMASK_EQ);
    __m256i TMASK = _mm256_set1_epi32(-1);
    __m256i MMASK = _mm256_andnot_si256(HMASK, _mm256_andnot_si256(LMASK, TMASK));

//    unsigned long int lmask = _mm256_movemask_ps(_mm256_castsi256_ps(LMASK));
//    unsigned long int mmask = _mm256_movemask_ps(_mm256_castsi256_ps(MMASK));
//    unsigned long int hmask = _mm256_movemask_ps(_mm256_castsi256_ps(HMASK));

    unsigned long int lmask = _mm256_movemask_ps((__m256)LMASK);
    unsigned long int mmask = _mm256_movemask_ps((__m256)MMASK);
    unsigned long int hmask = _mm256_movemask_ps((__m256)HMASK);

    // Partition using the comparisons to index into a permuation array.
    LOW  = _mm256_permutevar8x32_epi32(INPUT, ((__m256i *)PTL2)[lmask]);
    MED  = _mm256_permutevar8x32_epi32(INPUT, ((__m256i *)PTL2)[mmask]);
    HIGH = _mm256_permutevar8x32_epi32(INPUT, ((__m256i *)PTL2)[hmask]);

    // Store unaligned the partitioned values in the corresponding array.
    _mm256_storeu_si256((__m256i *)bottom, LOW);
    _mm256_storeu_si256((__m256i *)middle, MED);
    _mm256_storeu_si256((__m256i *)top, HIGH);

    // Shift the partition bounds by the number of elements stored.
    unsigned long int lp = __builtin_popcount(lmask);
    unsigned long int mp = __builtin_popcount(mmask);
    unsigned long int hp = __builtin_popcount(hmask);
    assert (lp + mp + hp == 8);
    bottom += lp;
    middle += mp;
    top    += hp;

    in += 8;
}
inline
void
vector_sort::internal::partition_8i(int *&in,
                                    __m256i &PIVOT,
                                    int *&bottom,
                                    int *&middle,
                                    int *&top)
{
    __m256i INPUT;
    __m256i LOW;
    __m256i MED;
    __m256i HIGH;

    INPUT = _mm256_loadu_si256((__m256i *)in);       // Load 8 ints.
    __m256i LMASK = _mm256_cmpgt_epi32(PIVOT, INPUT);        // Compare less than the low pivot.
    __m256i HMASK = _mm256_cmpgt_epi32(INPUT, PIVOT);        // Compare greater than the high pivot.
    __m256i TMASK = _mm256_set1_epi32(-1);
    __m256i MMASK = _mm256_andnot_si256(HMASK, _mm256_andnot_si256(LMASK, TMASK));

//    unsigned long int lmask = _mm256_movemask_ps(_mm256_castsi256_ps(LMASK));
//    unsigned long int mmask = _mm256_movemask_ps(_mm256_castsi256_ps(MMASK));
//    unsigned long int hmask = _mm256_movemask_ps(_mm256_castsi256_ps(HMASK));

    unsigned long int lmask = _mm256_movemask_ps((__m256)LMASK);
    unsigned long int mmask = _mm256_movemask_ps((__m256)MMASK);
    unsigned long int hmask = _mm256_movemask_ps((__m256)HMASK);

    // Partition using the comparisons to index into a permuation array.
    LOW  = _mm256_permutevar8x32_epi32(INPUT, ((__m256i *)PTL2)[lmask]);
    MED  = _mm256_permutevar8x32_epi32(INPUT, ((__m256i *)PTL2)[mmask]);
    HIGH = _mm256_permutevar8x32_epi32(INPUT, ((__m256i *)PTL2)[hmask]);

    // Store unaligned the partitioned values in the corresponding array.
    _mm256_storeu_si256((__m256i *)bottom, LOW);
    _mm256_storeu_si256((__m256i *)middle, MED);
    _mm256_storeu_si256((__m256i *)top, HIGH);

    // Shift the partition bounds by the number of elements stored.
    unsigned long int lp = __builtin_popcount(lmask);
    unsigned long int mp = __builtin_popcount(mmask);
    unsigned long int hp = __builtin_popcount(hmask);
    assert (lp + mp + hp == 8);
    bottom += lp;
    middle += mp;
    top    += hp;

    in += 8;
}

template <>
inline
void
vector_sort::internal::partition_avx2<double>(double *&in,
                                              unsigned long &n,
                                              double pivot1,
                                              double pivot2,
                                              double *&bottom,
                                              double *&middle,
                                              double *&top)
{
    // Duplicate the pivot values 4 times into vector equivalents.
    __m256d PIVOT1 = _mm256_broadcast_sd(&pivot1);
    __m256d PIVOT2 = _mm256_broadcast_sd(&pivot2);

    // Partition the input one 4-element AVX2 vector per loop iteration.
    while (n >= 4)
    {
        partition_4d(in, PIVOT1, PIVOT2, bottom, middle, top);
        n -= 4;
    }
}

template <>
inline
void
vector_sort::internal::partition_avx2<double>(double *&in,
                                              unsigned long &n,
                                              double pivot,
                                              double *&bottom,
                                              double *&middle,
                                              double *&top)
{
    // Duplicate the pivot values 4 times into a vector equivalent.
    __m256d PIVOT = _mm256_broadcast_sd(&pivot);

    // Partition the input one 4-element AVX2 vector per loop iteration.
    while (n >= 4)
    {
        partition_4d(in, PIVOT, bottom, middle, top);
        n -= 4;
    }
}

template <>
inline
void
vector_sort::internal::partition_avx2<float>(float *&in,
                                             unsigned long &n,
                                             float pivot1,
                                             float pivot2,
                                             float *&bottom,
                                             float *&middle,
                                             float *&top)
{
    // Duplicate the pivot values 8 times into vector equivalents.
    __m256 PIVOT1 = _mm256_broadcast_ss(&pivot1);
    __m256 PIVOT2 = _mm256_broadcast_ss(&pivot2);

    // Partition the input one 8-element AVX2 vector per loop iteration.
    while (n >= 8)
    {
        partition_8f(in, PIVOT1, PIVOT2, bottom, middle, top);
        n -= 8;
    }
}

template <>
inline
void
vector_sort::internal::partition_avx2<float>(float *&in,
                                             unsigned long &n,
                                             float pivot,
                                             float *&bottom,
                                             float *&middle,
                                             float *&top)
{
    // Duplicate the pivot values 8 times into vector equivalents.
    __m256 PIVOT = _mm256_broadcast_ss(&pivot);

    // Partition the input one 8-element AVX2 vector per loop iteration.
    while (n >= 8)
    {
        partition_8f(in, PIVOT, bottom, middle, top);
        n -= 8;
    }
}

template <>
inline
void
vector_sort::internal::partition_avx2<int>(int *&in,
                                           unsigned long &n,
                                           int pivot1,
                                           int pivot2,
                                           int *&bottom,
                                           int *&middle,
                                           int *&top)
{
    // Duplicate the pivot values 8 times into vector equivalents.
    __m256i PIVOT1 = _mm256_set1_epi32(pivot1);
    __m256i PIVOT2 = _mm256_set1_epi32(pivot2);

    // Partition the input one 8-element AVX2 vector per loop iteration.
    while (n >= 8)
    {
        partition_8i(in, PIVOT1, PIVOT2, bottom, middle, top);
        n -= 8;
    }
}

template <>
inline
void
vector_sort::internal::partition_avx2<int>(int *&in,
                                           unsigned long &n,
                                           int pivot,
                                           int *&bottom,
                                           int *&middle,
                                           int *&top)
{
    // Duplicate the pivot values 8 times into vector equivalents.
    __m256i PIVOT = _mm256_set1_epi32(pivot);

    // Partition the input one 8-element AVX2 vector per loop iteration.
    while (n >= 8)
    {
        partition_8i(in, PIVOT, bottom, middle, top);
        n -= 8;
    }
}

template <typename T>
void
vector_sort::internal::partition(T *in,
                                 T *tmp1,
                                 T *tmp2,
                                 unsigned long n,
                                 unsigned long &out_bottom_offset,
                                 unsigned long &out_bottom_count,
                                 unsigned long &out_middle_offset,
                                 unsigned long &out_middle_count,
                                 unsigned long &out_top_offset,
                                 unsigned long &out_top_count)
{
    T * const orig_in = in;

    T *bottom = in;
    T *middle = tmp1;
    T *top = tmp2;

    // Compute the two pivots by looking at 5 elements.
    size_t
        quarter = n / 4,
        i1 = 0,
        i5 = n - 1,
        i3 = n / 2,
        i2 = i3 - quarter,
        i4 = i3 + quarter;
    T
        &e1 = in[i1],
        &e2 = in[i2],
        &e3 = in[i3],
        &e4 = in[i4],
        &e5 = in[i5];

    T t; // A temporary to assist swapping.

    // Sort the five elements.
    if (e1 > e2)
        t = e1, e1 = e2, e2 = t;
    if (e4 > e5)
        t = e4, e4 = e5, e5 = t;
    if (e1 > e3)
        t = e1, e1 = e3, e3 = t;
    if (e2 > e3)
        t = e2, e2 = e3, e3 = t;
    if (e1 > e4)
        t = e1, e1 = e4, e4 = t;
    if (e3 > e4)
        t = e3, e3 = e4, e4 = t;
    if (e2 > e5)
        t = e2, e2 = e5, e5 = t;
    if (e2 > e3)
        t = e2, e2 = e3, e3 = t;
    if (e4 > e5)
        t = e4, e4 = e5, e5 = t;

    // Establish the pivot values.
    T pivot1 = e2, pivot2 = e4;

    bool const single_pivoted = (pivot1 == pivot2);

    // The bulk of the partitioning is passed to a type-specific implementation accelerated using AVX2.
    if (!single_pivoted)
    {
        partition_avx2<T>(in, n, pivot1, pivot2, bottom, middle, top);
    }
    else
    {
        partition_avx2<T>(in, n, pivot1, bottom, middle, top);
    }

    // Handle the remainder of elements that can't be vectorized.
    if (!single_pivoted)
    {
        while (n > 0)
        {
            if (in[0] <= pivot1)
            {
                bottom[0] = in[0];
                bottom += 1;
                in += 1;
                n--;
            }
            else if (in[0] >= pivot2)
            {
                top[0] = in[0];
                top += 1;
                in += 1;
                n--;
            }
            else
            {
                middle[0] = in[0];
                middle += 1;
                in += 1;
                n--;
            }
        }
    }
    else
    {
        while (n > 0)
        {
            if (in[0] < pivot1)
            {
                bottom[0] = in[0];
                bottom += 1;
                in += 1;
                n--;
            }
            else if (in[0] > pivot2)
            {
                top[0] = in[0];
                top += 1;
                in += 1;
                n--;
            }
            else
            {
                middle[0] = in[0];
                middle += 1;
                in += 1;
                n--;
            }
        }
    }

    // Rejoin the partitioned elements to the input array.
    unsigned long const bottom_count = ((uint64_t)bottom - (uint64_t)orig_in) / sizeof(T);
    unsigned long const middle_count = ((uint64_t)middle - (uint64_t)tmp1) / sizeof(T);
    unsigned long const top_count    = ((uint64_t)top - (uint64_t)tmp2) / sizeof(T);
    if (middle_count > 0)
    {
        memcpy(bottom, tmp1, middle_count * sizeof(T));
    }
    if (top_count > 0)
    {
        memcpy(bottom + middle_count, tmp2, top_count * sizeof(T));
    }

    out_bottom_offset = 0;
    out_bottom_count = bottom_count;
    out_middle_offset = bottom_count;
    out_middle_count = single_pivoted ? 0 : middle_count;
    out_top_offset = bottom_count + middle_count;
    out_top_count = top_count;
    while (out_bottom_count > 0 && orig_in[out_bottom_count - 1] == pivot1)
    {
        --out_bottom_count;
    }
    while (out_top_count > 0 && orig_in[out_top_offset] == pivot2)
    {
        ++out_top_offset;
        --out_top_count;
    }
    while (out_middle_count > 0 && orig_in[out_middle_offset] == pivot1)
    {
        ++out_middle_offset;
        --out_middle_count;
    }
    while (out_middle_count > 0 && orig_in[out_middle_count - 1] == pivot2)
    {
        --out_middle_count;
    }
}





