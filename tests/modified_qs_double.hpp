// Copyright (c) 2018 S. D. Adams <s.d.adams.software@gmail.com>

#pragma once

//#include <bits/stdc++.h>
#include <bitset>
#include <immintrin.h>
#include <vector>
#include <array>
#include <limits>
//#include <iostream>
//using namespace std;

//typedef int T;
namespace modified_quickdouble
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

__attribute__((aligned(64))) int const PTR[16 * 8] = {
    0, 1, 2, 3, 4, 5, 6, 7,
    2, 3, 4, 5, 6, 7, 0, 0,
    0, 1, 4, 5, 6, 7, 0, 0,
    4, 5, 6, 7, 0, 0, 0, 0,
    0, 1, 2, 3, 6, 7, 0, 0,
    2, 3, 6, 7, 0, 0, 0, 0,
    0, 1, 6, 7, 0, 0, 0, 0,
    6, 7, 0, 0, 0, 0, 0, 0,
    0, 1, 2, 3, 4, 5, 0, 0,
    2, 3, 4, 5, 0, 0, 0, 0,
    0, 1, 4, 5, 0, 0, 0, 0,
    4, 5, 0, 0, 0, 0, 0, 0,
    0, 1, 2, 3, 0, 0, 0, 0,
    2, 3, 0, 0, 0, 0, 0, 0,
    0, 1, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0
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
void part(double *&in,
          __m256d &PIVOT, // a four-double pivot
          double *&bottom,
          double *&top)
{
    __m256d A;
    __m256d M;
    A = _mm256_loadu_pd(in); // load 4 doubles
    M = _mm256_cmp_pd(A, PIVOT, 2); // compare them to the pivot 4 doubles using less-than
    unsigned long mask = _mm256_movemask_pd(M); // effectively cast the comparison result to 4 bools

    // Parition the 4 doubles into less-than (M) and greater-or-equal-to (A).
    // consider _mm256_permute4x64_pd
    M = (__m256d)_mm256_permutevar8x32_ps((__m256)A, ((__m256i *)PTL)[mask]);
    A = (__m256d)_mm256_permutevar8x32_ps((__m256)A, ((__m256i *)PTR)[mask]);

    // Find the number moved to less-than
    mask = __builtin_popcount(mask);

    // Store unaligned the separated values in the extremes of each array.
    // Testing shows that these SIMD instructions are critical to keeping this algorithm performant.
    if (1)
    {
        _mm256_storeu_pd(bottom, M);
        _mm256_storeu_pd(top, A);
    }
    else
    {
        // The memcpy equivalent is correct, but very slow.
        // We would need this to be fast to allow for sorting in-place without the temporary array.
//        memcpy(bottom, (double *)&M, sizeof(double) * mask);
//        memcpy(top, (double *)&A, sizeof(double) * (4 - mask));
        switch (mask)
        {
        case 0:
        {
            _mm256_storeu_pd(top, A);
        }
            break;
        case 4:
        {
            _mm256_storeu_pd(bottom, M);
        }
            break;
        default:
        {
            _mm256_maskstore_pd(bottom, *(__m256i *)&store_mask[mask * 8], M);
            _mm256_maskstore_pd(top, *(__m256i *)&store_mask[(4 - mask) * 8], A);
        }
        }
    }

    // Shift the ends of the array inward by the number of elements stored.
    bottom += mask;
    top += 4 - mask;

    in += 4;
}

// SIMD AVX instructions for double
int qsort_AVX2(double *in, double *tmp, unsigned long n)
{
    double pivot;

    double *bottom = in;
    double *top = tmp;

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

    while (n >= 4)
    {
        part(in, PIVOT, bottom, top);
        n -= 4;
    }

    // This handles the remainder of elements that can't be vectorized.
    while (n > 0)
    {
        if (in[0] <= pivot)
        {
            bottom[0] = in[0];
            bottom += 1;
            in += 1;
            n--;
        }
        else
        {
            top[0] = in[0];
            top += 1;
            in += 1;
            n--;
        }
    }

    // The top is written into a temporary since the vector instructions would otherwise result in 'overlap' and therefore corruption.
    // These are then copied back into the main array.
    unsigned long const ret_val = ((uint64_t)top - (uint64_t)tmp) / 8;
    if (ret_val)
    {
        memcpy(bottom, tmp, ret_val * 8);
    }

    return ret_val;
}

template <typename T>
void my_qsort_AVX2(T *unsorted_array, T *tmp_array,
                   unsigned long n)
{
    int new_n;
    while (n > 32)
    {
        new_n = qsort_AVX2(unsorted_array, tmp_array, n);
        n = n - new_n - 1;
        my_qsort_AVX2(&unsorted_array[n + 1], tmp_array, new_n);
    }
    insertion_sort(unsorted_array, n);
}


template <typename T>
void qs_double(std::vector<T> &vec)
{
    T *data = &vec[0];
    std::vector<T> temp(vec.size());
    T *tmp = &temp[0];
    int len = vec.size();
    modified_quickdouble::my_qsort_AVX2(data, tmp, len);
}
} // namespace end
