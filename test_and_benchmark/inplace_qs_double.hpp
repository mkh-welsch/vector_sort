// Copyright (c) 2018 S. D. Adams <s.d.adams.software@gmail.com>

#pragma once

#include <cassert>

//#include <bits/stdc++.h>
#include <bitset>
#include <immintrin.h>
#include <vector>
#include <array>
#include <limits>
//#include <iostream>
//using namespace std;

//typedef int T;
namespace inplace_quickdouble
{

template <typename T>
void swap(T &a, T &b, T &t)
{
    t = a;
    a = b;
    b = t;
}

template <typename T>
T med3(T const &a, T const &b, T const &c)
{
    if (a < b)
    {
        if (b < c)
        {
            return b;
        }
        else
        {
            return a < c ? c : a;
        }
    }
    else
    {
        if (b > c)
        {
            return b;
        }
        else
        {
            return a > c ? c : a;
        }
    }
}

__attribute__((aligned(64))) int const PTL[16 * 8] = {
    0, 1, 2, 3, 4, 5, 6, 7,
    0, 1, 2, 3, 4, 5, 6, 7,
    2, 3, 0, 1, 4, 5, 6, 7,
    0, 1, 2, 3, 4, 5, 6, 7,
    4, 5, 0, 1, 2, 3, 6, 7,
    0, 1, 4, 5, 2, 3, 6, 7,
    2, 3, 4, 5, 0, 1, 6, 7,
    0, 1, 2, 3, 4, 5, 6, 7,
    6, 7, 0, 1, 2, 3, 4, 5,
    0, 1, 6, 7, 2, 3, 4, 5,
    2, 3, 6, 7, 0, 1, 4, 5,
    0, 1, 2, 3, 6, 7, 4, 5,
    4, 5, 6, 7, 0, 1, 2, 3,
    0, 1, 4, 5, 6, 7, 2, 3,
    2, 3, 4, 5, 6, 7, 0, 1,
    0, 1, 2, 3, 4, 5, 6, 7
};

__attribute__((aligned(64))) int const PTR[16 * 8] = {
    0, 1, 2, 3, 4, 5, 6, 7,
    2, 3, 4, 5, 6, 7, 0, 1,
    0, 1, 4, 5, 6, 7, 2, 3,
    4, 5, 6, 7, 0, 1, 2, 3,
    0, 1, 2, 3, 6, 7, 4, 5,
    2, 3, 6, 7, 0, 1, 4, 5,
    0, 1, 6, 7, 2, 3, 4, 5,
    6, 7, 0, 1, 2, 3, 4, 5,
    0, 1, 2, 3, 4, 5, 6, 7,
    2, 3, 4, 5, 0, 1, 6, 7,
    0, 1, 4, 5, 2, 3, 6, 7,
    4, 5, 0, 1, 2, 3, 6, 7,
    0, 1, 2, 3, 4, 5, 6, 7,
    2, 3, 0, 1, 4, 5, 6, 7,
    0, 1, 2, 3, 4, 5, 6, 7,
    0, 1, 2, 3, 4, 5, 6, 7
};

__attribute__((aligned(64))) int const reverse_mask[8] = {
    6, 7, 4, 5, 2, 3, 0, 1
};

__attribute__((aligned(64))) unsigned int const store_mask[] = {
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0xFFFFFFFF, 0xFFFFFFFF, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000, 0x00000000,
    0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF
};

template <typename T>
static void insertion_sort(T *d, unsigned long n)
{
    if (n <= 1)
        return;
    long i, j;
    for (i = 1; i < n; i++)
    {
        T tmp = d[i];
        for (j = i; j >= 1 && tmp < d[j - 1]; j--)
            d[j] = d[j - 1];
        d[j] = tmp;
    }
}

// SIMD AVX instructions for double
unsigned long
part(__m256d &PIVOT, // a four-double pivot
     double *&bottom,
     double *&top)
{
    __m256d BOTTOM_IN;
    __m256d TOP_IN;
    __m256d BOTTOM_OUT;
    __m256d TOP_OUT;
    __m256d M;
    BOTTOM_IN = _mm256_loadu_pd(bottom); // load 4 doubles from the bottom.
    TOP_IN = _mm256_loadu_pd(top - 4); // load 4 doubles from the top.
    TOP_IN = (__m256d)_mm256_permutevar8x32_ps((__m256)TOP_IN, *((__m256i *)reverse_mask)); // reverse the 4 doubles from the top.
    M = _mm256_cmp_pd(BOTTOM_IN, PIVOT, 2); // compare them to the pivot 4 doubles using less-than
    unsigned long const mask = _mm256_movemask_pd(M); // effectively cast the comparison result to 4 bools

    switch (mask)
    {
    case 0:
        BOTTOM_OUT = _mm256_blend_pd(BOTTOM_IN, TOP_IN, 0);
        TOP_OUT    = _mm256_blend_pd(TOP_IN, BOTTOM_IN, 0);
    break;
    case 1:
        BOTTOM_OUT = _mm256_blend_pd(BOTTOM_IN, TOP_IN, 1);
        TOP_OUT    = _mm256_blend_pd(TOP_IN, BOTTOM_IN, 1);
    break;
    case 2:
        BOTTOM_OUT = _mm256_blend_pd(BOTTOM_IN, TOP_IN, 2);
        TOP_OUT    = _mm256_blend_pd(TOP_IN, BOTTOM_IN, 2);
    break;
    case 3:
        BOTTOM_OUT = _mm256_blend_pd(BOTTOM_IN, TOP_IN, 3);
        TOP_OUT    = _mm256_blend_pd(TOP_IN, BOTTOM_IN, 3);
    break;
    case 4:
        BOTTOM_OUT = _mm256_blend_pd(BOTTOM_IN, TOP_IN, 4);
        TOP_OUT    = _mm256_blend_pd(TOP_IN, BOTTOM_IN, 4);
    break;
    case 5:
        BOTTOM_OUT = _mm256_blend_pd(BOTTOM_IN, TOP_IN, 5);
        TOP_OUT    = _mm256_blend_pd(TOP_IN, BOTTOM_IN, 5);
    break;
    case 6:
        BOTTOM_OUT = _mm256_blend_pd(BOTTOM_IN, TOP_IN, 6);
        TOP_OUT    = _mm256_blend_pd(TOP_IN, BOTTOM_IN, 6);
    break;
    case 7:
        BOTTOM_OUT = _mm256_blend_pd(BOTTOM_IN, TOP_IN, 7);
        TOP_OUT    = _mm256_blend_pd(TOP_IN, BOTTOM_IN, 7);
    break;
    case 8:
        BOTTOM_OUT = _mm256_blend_pd(BOTTOM_IN, TOP_IN, 8);
        TOP_OUT    = _mm256_blend_pd(TOP_IN, BOTTOM_IN, 8);
    break;
    case 9:
        BOTTOM_OUT = _mm256_blend_pd(BOTTOM_IN, TOP_IN, 9);
        TOP_OUT    = _mm256_blend_pd(TOP_IN, BOTTOM_IN, 9);
    break;
    case 10:
        BOTTOM_OUT = _mm256_blend_pd(BOTTOM_IN, TOP_IN, 10);
        TOP_OUT    = _mm256_blend_pd(TOP_IN, BOTTOM_IN, 10);
    break;
    case 11:
        BOTTOM_OUT = _mm256_blend_pd(BOTTOM_IN, TOP_IN, 11);
        TOP_OUT    = _mm256_blend_pd(TOP_IN, BOTTOM_IN, 11);
    break;
    case 12:
        BOTTOM_OUT = _mm256_blend_pd(BOTTOM_IN, TOP_IN, 12);
        TOP_OUT    = _mm256_blend_pd(TOP_IN, BOTTOM_IN, 12);
    break;
    case 13:
        BOTTOM_OUT = _mm256_blend_pd(BOTTOM_IN, TOP_IN, 13);
        TOP_OUT    = _mm256_blend_pd(TOP_IN, BOTTOM_IN, 13);
    break;
    case 14:
        BOTTOM_OUT = _mm256_blend_pd(BOTTOM_IN, TOP_IN, 14);
        TOP_OUT    = _mm256_blend_pd(TOP_IN, BOTTOM_IN, 14);
    break;
    case 15:
        BOTTOM_OUT = _mm256_blend_pd(BOTTOM_IN, TOP_IN, 15);
        TOP_OUT    = _mm256_blend_pd(TOP_IN, BOTTOM_IN, 15);
    break;
    default: assert(false);
    }

    // Parition the 4 doubles into less-than (M) and greater-or-equal-to (A).
    BOTTOM_OUT = (__m256d)_mm256_permutevar8x32_ps((__m256)BOTTOM_OUT, ((__m256i *)PTL)[mask]);
//    TOP_OUT = (__m256d)_mm256_permutevar8x32_ps((__m256)TOP_OUT, ((__m256i *)PTR)[mask]);

    // Reverse the 4 doubles from the top.
    TOP_OUT = (__m256d)_mm256_permutevar8x32_ps((__m256)TOP_OUT, *((__m256i *)reverse_mask));

    // Find the number moved to less-than
    unsigned long const less_count = __builtin_popcount(mask);

    _mm256_storeu_pd(bottom, BOTTOM_OUT);
    _mm256_storeu_pd(top - 4, TOP_OUT);
    bottom += less_count;
    top -= 4 - less_count;
    return less_count;
}

// SIMD AVX instructions for double
int qsort_AVX2(double * const in, unsigned long const n)
{
    double pivot;

    double *bottom = in;
    double *top = in + n;

    // Selects the pivot to be the middle of three values, and rearranges the sampled values accordingly.
    double &el1 = in[0];
    double &el2 = in[n - 1];
    double &el3 = in[n / 2];
    if (el1 > el2)
    {
        swap(el1, el2, pivot);
    }
    if (el2 > el3)
    {
        swap(el2, el3, pivot);
        if (el1 > el2)
        {
            swap(el1, el2, pivot);
        }
    }
    pivot = el2;

    // Duplicates the pivot value 4 times into the vector version.
    __m256d PIVOT = _mm256_broadcast_sd(&pivot);

    while ((top - bottom) >= 8)
    {
        part(PIVOT, bottom, top);
    }

    // This handles the remainder of elements that can't be vectorized.
    while (bottom < (top - 1))
    {
        if (bottom[0] < pivot)
        {
            bottom += 1;
        }
        else
        {
            top -= 1;
            std::swap(bottom[0], top[0]);
        }
    }

    unsigned long const ret_val = ((uint64_t)(in + n) - (uint64_t)top) / sizeof(double);

    return ret_val;
}

template <typename T>
void my_qsort_AVX2(T *unsorted_array, unsigned long n)
{
    int new_n;
    while (n > 32)
    {
        new_n = qsort_AVX2(unsorted_array, n);
        n = n - new_n - 1;
        my_qsort_AVX2(&unsorted_array[n + 1], new_n);
    }
    insertion_sort(unsorted_array, n);
}


template <typename T>
void qs_double(std::vector<T> &vec)
{
    T *data = &vec[0];
    int len = vec.size();
    inplace_quickdouble::my_qsort_AVX2(data, len);
}
} // namespace end
