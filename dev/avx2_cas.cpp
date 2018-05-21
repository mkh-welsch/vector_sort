/*                                             
   _` | \ \   / \ \  /       __|   _` |   __| 
  (   |  \ \ /   `  <       (     (   | \__ \ 
 \__,_|   \_/    _/\_\     \___| \__,_| ____/                                                                                                          
Copyright (c) 2018 S. D. Adams <s.d.adams.software@gmail.com>
*/

#ifndef AVX2_CAS_HPP
#define AVX2_CAS_HPP

#include <cstddef>
#include <immintrin.h>

#define AVX2_CAS_NO_BRANCHING 1
#define AVX2_CAS_ENABLE_SIMD 1

namespace avx2_cas // Compare and swap (cas).
{
    template <typename T, size_t const a0, size_t const b0> void cas (T *data);

    // Declared as a class to allow partial-specialization.
    template <typename T> class cas2 {public: template <size_t const a0, size_t const b0, size_t const a1, size_t const b1> static void cas (T *data);};
    template <typename T> class cas3 {public: template <size_t const a0, size_t const b0, size_t const a1, size_t const b1, size_t const a2, size_t const b2> static void cas (T *data);};
    template <typename T> class cas4 {public: template <size_t const a0, size_t const b0, size_t const a1, size_t const b1, size_t const a2, size_t const b2, size_t const a3, size_t const b3> static void cas (T *data);};

} // end namespace avx2_cas


template <typename T, size_t const a0, size_t const b0>
void
avx2_cas::cas(T * const data)
{
    static_assert(a0 < b0, "Function vector_sort::internal::cas requires i to be less than j.");
    T &d0 = data[a0];
    T &d1 = data[b0];
#if AVX2_CAS_NO_BRANCHING
    int const pi = ((int)(d0 < d1));
    int const qi = ((int)1) - pi;
    T const p = static_cast<T>(pi);
    T const q = static_cast<T>(qi);
    T const a = (p * d0) + (q * d1);
    T const b = (q * d0) + (p * d1);
    d0 = a;
    d1 = b;
#else
    if (d1 < d0)
    {
        std::swap(d0, d1);
    }
#endif
}

template<>
template <size_t const a0, size_t const b0, size_t const a1, size_t const b1>
void
avx2_cas::cas2<double>::cas(double * const data)
{
#if AVX2_CAS_ENABLE_SIMD
    static_assert(a0 < b0, "Function avx2_cas::cas2<double>::cas requires a0 to be less than b0.");
    static_assert(a1 < b1, "Function avx2_cas::cas2<double>::cas requires a1 to be less than b1.");

    // Load the 4 values into two vectors.
    __m128d A;
    __m128d B;
    double * const ap = reinterpret_cast<double *>(& A);
    double * const bp = reinterpret_cast<double *>(& B);
    ap[0] = data[a0];
    ap[1] = data[a1];
    bp[0] = data[b0];
    bp[1] = data[b1];

    // Compare the vectors.
    __m128d AA = _mm_min_pd(A, B);
    __m128d BB = _mm_max_pd(A, B);

    // Store the values back into the source array.
    double * const aap = reinterpret_cast<double *>(& AA);
    double * const bbp = reinterpret_cast<double *>(& BB);
    data[a0] = aap[0];
    data[a1] = aap[1];
    data[b0] = bbp[0];
    data[b1] = bbp[1];
#else
    avx2_cas::cas<double, a0, b0>(data);
    avx2_cas::cas<double, a1, b1>(data);
#endif
}

template<>
template <size_t const a0, size_t const b0, size_t const a1, size_t const b1>
void
avx2_cas::cas2<float>::cas(float * const data)
{
#if AVX2_CAS_ENABLE_SIMD
    static_assert(a0 < b0, "Function avx2_cas::cas2<float>::cas requires a0 to be less than b0.");
    static_assert(a1 < b1, "Function avx2_cas::cas2<float>::cas requires a1 to be less than b1.");

    // Load the 4 values into two vectors.
    __m128 A;
    __m128 B;
    float * const ap = reinterpret_cast<float *>(& A);
    float * const bp = reinterpret_cast<float *>(& B);
    ap[0] = data[a0];
    ap[1] = data[a1];
    ap[2] = 0.0F;
    ap[3] = 0.0F;
    bp[0] = data[b0];
    bp[1] = data[b1];
    bp[2] = 0.0F;
    bp[3] = 0.0F;

    // Compare the vectors.
    __m128 AA = _mm_min_ps(A, B);
    __m128 BB = _mm_max_ps(A, B);

    // Store the values back into the source array.
    float * const aap = reinterpret_cast<float *>(& AA);
    float * const bbp = reinterpret_cast<float *>(& BB);
    data[a0] = aap[0];
    data[a1] = aap[1];
    data[b0] = bbp[0];
    data[b1] = bbp[1];
#else
    avx2_cas::cas<float, a0, b0>(data);
    avx2_cas::cas<float, a1, b1>(data);
#endif
}

template<>
template <size_t const a0, size_t const b0, size_t const a1, size_t const b1>
void
avx2_cas::cas2<int>::cas(int * const data)
{
#if AVX2_CAS_ENABLE_SIMD
    static_assert(a0 < b0, "Function avx2_cas::cas2<int>::cas requires a0 to be less than b0.");
    static_assert(a1 < b1, "Function avx2_cas::cas2<int>::cas requires a1 to be less than b1.");

    // Load the 4 values into two vectors.
    __m128i A;
    __m128i B;
    int * const ap = reinterpret_cast<int *>(& A);
    int * const bp = reinterpret_cast<int *>(& B);
    ap[0] = data[a0];
    ap[1] = data[a1];
    ap[2] = 0;
    ap[3] = 0;
    bp[0] = data[b0];
    bp[1] = data[b1];
    bp[2] = 0;
    bp[3] = 0;

    // Compare the vectors.
    __m128i AA = _mm_min_epi32(A, B);
    __m128i BB = _mm_max_epi32(A, B);

    // Store the values back into the source array.
    int * const aap = reinterpret_cast<int *>(& AA);
    int * const bbp = reinterpret_cast<int *>(& BB);
    data[a0] = aap[0];
    data[a1] = aap[1];
    data[b0] = bbp[0];
    data[b1] = bbp[1];
#else
    avx2_cas::cas<int, a0, b0>(data);
    avx2_cas::cas<int, a1, b1>(data);
#endif
}

template<>
template <size_t const a0, size_t const b0, size_t const a1, size_t const b1, size_t const a2, size_t const b2>
void
avx2_cas::cas3<double>::cas(double * const data)
{
#if AVX2_CAS_ENABLE_SIMD
    static_assert(a0 < b0, "Function avx2_cas::cas2<double>::cas requires a0 to be less than b0.");
    static_assert(a1 < b1, "Function avx2_cas::cas2<double>::cas requires a1 to be less than b1.");

    // Load the 4 values into two vectors.
    __m256d A;
    __m256d B;
    double * const ap = reinterpret_cast<double *>(& A);
    double * const bp = reinterpret_cast<double *>(& B);
    ap[0] = data[a0];
    ap[1] = data[a1];
    ap[2] = data[a2];
    ap[3] = 0.0;
    bp[0] = data[b0];
    bp[1] = data[b1];
    bp[2] = data[b2];
    bp[3] = 0.0;

    // Compare the vectors.
    __m256d AA = _mm256_min_pd(A, B);
    __m256d BB = _mm256_max_pd(A, B);

    // Store the values back into the source array.
    double * const aap = reinterpret_cast<double *>(& AA);
    double * const bbp = reinterpret_cast<double *>(& BB);
    data[a0] = aap[0];
    data[a1] = aap[1];
    data[a2] = aap[2];
    data[b0] = bbp[0];
    data[b1] = bbp[1];
    data[b2] = bbp[2];
#else
    avx2_cas::cas<double, a0, b0>(data);
    avx2_cas::cas<double, a1, b1>(data);
    avx2_cas::cas<double, a2, b2>(data);
#endif
}

template<>
template <size_t const a0, size_t const b0, size_t const a1, size_t const b1, size_t const a2, size_t const b2>
void
avx2_cas::cas3<float>::cas(float * const data)
{
#if AVX2_CAS_ENABLE_SIMD
    static_assert(a0 < b0, "Function avx2_cas::cas3<float>::cas requires a0 to be less than b0.");
    static_assert(a1 < b1, "Function avx2_cas::cas3<float>::cas requires a1 to be less than b1.");
    static_assert(a2 < b2, "Function avx2_cas::cas3<float>::cas requires a2 to be less than b2.");

    // Load the 4 values into two vectors.
    __m128 A;
    __m128 B;
    float * const ap = reinterpret_cast<float *>(& A);
    float * const bp = reinterpret_cast<float *>(& B);
    ap[0] = data[a0];
    ap[1] = data[a1];
    ap[2] = data[a2];
    ap[3] = 0.0F;
    bp[0] = data[b0];
    bp[1] = data[b1];
    bp[2] = data[b2];
    bp[3] = 0.0F;

    // Compare the vectors.
    __m128 AA = _mm_min_ps(A, B);
    __m128 BB = _mm_max_ps(A, B);

    // Store the values back into the source array.
    float * const aap = reinterpret_cast<float *>(& AA);
    float * const bbp = reinterpret_cast<float *>(& BB);
    data[a0] = aap[0];
    data[a1] = aap[1];
    data[a2] = aap[2];
    data[b0] = bbp[0];
    data[b1] = bbp[1];
    data[b2] = bbp[2];
#else
    avx2_cas::cas<float, a0, b0>(data);
    avx2_cas::cas<float, a1, b1>(data);
    avx2_cas::cas<float, a2, b2>(data);
#endif
}

template<>
template <size_t const a0, size_t const b0, size_t const a1, size_t const b1, size_t const a2, size_t const b2>
void
avx2_cas::cas3<int>::cas(int * const data)
{
#if AVX2_CAS_ENABLE_SIMD
    static_assert(a0 < b0, "Function avx2_cas::cas2<int>::cas requires a0 to be less than b0.");
    static_assert(a1 < b1, "Function avx2_cas::cas2<int>::cas requires a1 to be less than b1.");
    static_assert(a2 < b2, "Function avx2_cas::cas3<int>::cas requires a2 to be less than b2.");

    // Load the 4 values into two vectors.
    __m128i A;
    __m128i B;
    int * const ap = reinterpret_cast<int *>(& A);
    int * const bp = reinterpret_cast<int *>(& B);
    ap[0] = data[a0];
    ap[1] = data[a1];
    ap[2] = data[a2];
    ap[3] = 0;
    bp[0] = data[b0];
    bp[1] = data[b1];
    bp[2] = data[b2];
    bp[3] = 0;

    // Compare the vectors.
    __m128i AA = _mm_min_epi32(A, B);
    __m128i BB = _mm_max_epi32(A, B);

    // Store the values back into the source array.
    int * const aap = reinterpret_cast<int *>(& AA);
    int * const bbp = reinterpret_cast<int *>(& BB);
    data[a0] = aap[0];
    data[a1] = aap[1];
    data[a2] = aap[2];
    data[b0] = bbp[0];
    data[b1] = bbp[1];
    data[b2] = bbp[2];
#else
    avx2_cas::cas<int, a0, b0>(data);
    avx2_cas::cas<int, a1, b1>(data);
    avx2_cas::cas<int, a2, b2>(data);
#endif
}

template<>
template <size_t const a0, size_t const b0, size_t const a1, size_t const b1, size_t const a2, size_t const b2, size_t const a3, size_t const b3>
void
avx2_cas::cas4<double>::cas(double * const data)
{
#if AVX2_CAS_ENABLE_SIMD
    static_assert(a0 < b0, "Function avx2_cas::cas4<double>::cas requires a0 to be less than b0.");
    static_assert(a1 < b1, "Function avx2_cas::cas4<double>::cas requires a1 to be less than b1.");
    static_assert(a2 < b2, "Function avx2_cas::cas4<double>::cas requires a2 to be less than b2.");
    static_assert(a3 < b3, "Function avx2_cas::cas4<double>::cas requires a3 to be less than b3.");

    // Load the 4 values into two vectors.
    __m256d A;
    __m256d B;
    double * const ap = reinterpret_cast<double *>(& A);
    double * const bp = reinterpret_cast<double *>(& B);
    ap[0] = data[a0];
    ap[1] = data[a1];
    ap[2] = data[a2];
    ap[3] = data[a3];
    bp[0] = data[b0];
    bp[1] = data[b1];
    bp[2] = data[b2];
    bp[3] = data[b3];

    // Compare the vectors.
    __m256d AA = _mm256_min_pd(A, B);
    __m256d BB = _mm256_max_pd(A, B);

    // Store the values back into the source array.
    double * const aap = reinterpret_cast<double *>(& AA);
    double * const bbp = reinterpret_cast<double *>(& BB);
    data[a0] = aap[0];
    data[a1] = aap[1];
    data[a2] = aap[2];
    data[a3] = aap[3];
    data[b0] = bbp[0];
    data[b1] = bbp[1];
    data[b2] = bbp[2];
    data[b3] = bbp[3];
#else
    avx2_cas::cas<double, a0, b0>(data);
    avx2_cas::cas<double, a1, b1>(data);
    avx2_cas::cas<double, a2, b2>(data);
    avx2_cas::cas<double, a3, b3>(data);
#endif
}

template<>
template <size_t const a0, size_t const b0, size_t const a1, size_t const b1, size_t const a2, size_t const b2, size_t const a3, size_t const b3>
void
avx2_cas::cas4<float>::cas(float * const data)
{
#if AVX2_CAS_ENABLE_SIMD
    static_assert(a0 < b0, "Function avx2_cas::cas4<double>::cas requires a0 to be less than b0.");
    static_assert(a1 < b1, "Function avx2_cas::cas4<double>::cas requires a1 to be less than b1.");
    static_assert(a2 < b2, "Function avx2_cas::cas4<double>::cas requires a2 to be less than b2.");
    static_assert(a3 < b3, "Function avx2_cas::cas4<double>::cas requires a3 to be less than b3.");

    // Load the 4 values into two vectors.
    __m128 A;
    __m128 B;
    float * const ap = reinterpret_cast<float *>(& A);
    float * const bp = reinterpret_cast<float *>(& B);
    ap[0] = data[a0];
    ap[1] = data[a1];
    ap[2] = data[a2];
    ap[3] = data[a3];
    bp[0] = data[b0];
    bp[1] = data[b1];
    bp[2] = data[b2];
    bp[3] = data[b3];

    // Compare the vectors.
    __m128 AA = _mm_min_ps(A, B);
    __m128 BB = _mm_max_ps(A, B);

    // Store the values back into the source array.
    float * const aap = reinterpret_cast<float *>(& AA);
    float * const bbp = reinterpret_cast<float *>(& BB);
    data[a0] = aap[0];
    data[a1] = aap[1];
    data[a2] = aap[2];
    data[a3] = aap[3];
    data[b0] = bbp[0];
    data[b1] = bbp[1];
    data[b2] = bbp[2];
    data[b3] = bbp[3];
#else
    avx2_cas::cas<float, a0, b0>(data);
    avx2_cas::cas<float, a1, b1>(data);
    avx2_cas::cas<float, a2, b2>(data);
    avx2_cas::cas<float, a3, b3>(data);
#endif
}

template<>
template <size_t const a0, size_t const b0, size_t const a1, size_t const b1, size_t const a2, size_t const b2, size_t const a3, size_t const b3>
void
avx2_cas::cas4<int>::cas(int * const data)
{
#if AVX2_CAS_ENABLE_SIMD
    static_assert(a0 < b0, "Function avx2_cas::cas4<int>::cas requires a0 to be less than b0.");
    static_assert(a1 < b1, "Function avx2_cas::cas4<int>::cas requires a1 to be less than b1.");
    static_assert(a2 < b2, "Function avx2_cas::cas4<int>::cas requires a2 to be less than b2.");
    static_assert(a3 < b3, "Function avx2_cas::cas4<int>::cas requires a3 to be less than b3.");

    // Load the 4 values into two vectors.
    __m128i A;
    __m128i B;
    int * const ap = reinterpret_cast<int *>(& A);
    int * const bp = reinterpret_cast<int *>(& B);
    ap[0] = data[a0];
    ap[1] = data[a1];
    ap[2] = data[a2];
    ap[3] = data[a3];
    bp[0] = data[b0];
    bp[1] = data[b1];
    bp[2] = data[b2];
    bp[3] = data[b3];

    // Compare the vectors.
    __m128i AA = _mm_min_epi32(A, B);
    __m128i BB = _mm_max_epi32(A, B);

    // Store the values back into the source array.
    int * const aap = reinterpret_cast<int *>(& AA);
    int * const bbp = reinterpret_cast<int *>(& BB);
    data[a0] = aap[0];
    data[a1] = aap[1];
    data[a2] = aap[2];
    data[a3] = aap[3];
    data[b0] = bbp[0];
    data[b1] = bbp[1];
    data[b2] = bbp[2];
    data[b3] = bbp[3];
#else
    avx2_cas::cas<int, a0, b0>(data);
    avx2_cas::cas<int, a1, b1>(data);
    avx2_cas::cas<int, a2, b2>(data);
    avx2_cas::cas<int, a3, b3>(data);
#endif
}

#endif // AVX2_CAS_HPP
