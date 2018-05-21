//#include <bits/stdc++.h>
#include <bitset>
#include <immintrin.h>
#include <vector>
#include <limits>
//#include "intsort.hpp"

// this is the version that should be the fastest
const __m128i pass1_add4 = _mm_setr_epi32(1, 1, 3, 3);
const __m128i pass2_add4 = _mm_setr_epi32(2, 3, 2, 3);
const __m128i pass3_add4 = _mm_setr_epi32(0, 2, 2, 3);
void simdsort4(int* __restrict v) {
	__m128i b, a = _mm_loadu_si128(reinterpret_cast<const __m128i*>(v));

	b = _mm_shuffle_epi32(a, 177);
	b = _mm_cmpgt_epi32(b, a);
	b = _mm_add_epi32(b, pass1_add4);
	a = _mm_castps_si128(_mm_permutevar_ps(_mm_castsi128_ps(a), b));

	b = _mm_shuffle_epi32(a, 78);
	b = _mm_cmpgt_epi32(b, a);
	b = _mm_add_epi32(b, b);
	b = _mm_add_epi32(b, pass2_add4);
	a = _mm_castps_si128(_mm_permutevar_ps(_mm_castsi128_ps(a), b));

	b = _mm_shuffle_epi32(a, 216);
	b = _mm_cmpgt_epi32(b, a);
	b = _mm_add_epi32(b, pass3_add4);
	__m128 ret = _mm_permutevar_ps(_mm_castsi128_ps(a), b);

	_mm_storeu_ps(reinterpret_cast<float*>(v), ret);
}

//using namespace std;
void sort2(int *__restrict v)
{
#define __kmin(a, b) (a < b ? a : b)
#define __kmax(a, b) (a < b ? b : a)
#define __kswap(x, y)               \
	{                               \
		int a = __kmin(v[x], v[y]); \
		int b = __kmax(v[x], v[y]); \
		v[x] = a;                   \
		v[y] = b;                   \
	}
	__kswap(0, 1);
#undef __kswap
#undef __kmax
#undef __kmin
}

void sort3(int *__restrict v)
{
#define __kmin(a, b) (a < b ? a : b)
#define __kmax(a, b) (a < b ? b : a)
#define __kswap(x, y)               \
	{                               \
		int a = __kmin(v[x], v[y]); \
		int b = __kmax(v[x], v[y]); \
		v[x] = a;                   \
		v[y] = b;                   \
	}
	__kswap(1, 2);
	__kswap(0, 2);
	__kswap(0, 1);
#undef __kswap
#undef __kmax
#undef __kmin
}

void sort4(int *__restrict v)
{
#define __kmin(a, b) (a < b ? a : b)
#define __kmax(a, b) (a < b ? b : a)
#define __kswap(x, y)               \
	{                               \
		int a = __kmin(v[x], v[y]); \
		int b = __kmax(v[x], v[y]); \
		v[x] = a;                   \
		v[y] = b;                   \
	}
	__kswap(0, 1);
	__kswap(2, 3);
	__kswap(0, 2);
	__kswap(1, 3);
	__kswap(1, 2);
#undef __kswap
#undef __kmax
#undef __kmin
}


void sort5(int *__restrict v)
{
#define __kmin(a, b) (a < b ? a : b)
#define __kmax(a, b) (a < b ? b : a)
#define __kswap(x, y)               \
	{                               \
		int a = __kmin(v[x], v[y]); \
		int b = __kmax(v[x], v[y]); \
		v[x] = a;                   \
		v[y] = b;                   \
	}
	__kswap(0, 1);
	__kswap(3, 4);
	__kswap(2, 4);
	__kswap(2, 3);
	__kswap(0, 3);
	__kswap(0, 2);
	__kswap(1, 4);
	__kswap(1, 3);
	__kswap(1, 2);
#undef __kswap
#undef __kmax
#undef __kmin
}


void sort6(int *__restrict v)
{
#define __kmin(a, b) (a < b ? a : b)
#define __kmax(a, b) (a < b ? b : a)
#define __kswap(x, y)               \
	{                               \
		int a = __kmin(v[x], v[y]); \
		int b = __kmax(v[x], v[y]); \
		v[x] = a;                   \
		v[y] = b;                   \
	}
	__kswap(1, 2);
	__kswap(0, 2);
	__kswap(0, 1);
	__kswap(4, 5);
	__kswap(3, 5);
	__kswap(3, 4);
	__kswap(0, 3);
	__kswap(1, 4);
	__kswap(2, 5);
	__kswap(2, 4);
	__kswap(1, 3);
	__kswap(2, 3);
#undef __kswap
#undef __kmax
#undef __kmin
}

void sort7(int *__restrict v)
{
#define __kmin(a, b) (a < b ? a : b)
#define __kmax(a, b) (a < b ? b : a)
#define __kswap(x, y)               \
	{                               \
		int a = __kmin(v[x], v[y]); \
		int b = __kmax(v[x], v[y]); \
		v[x] = a;                   \
		v[y] = b;                   \
	}
	__kswap(1, 2);
	__kswap(0, 2);
	__kswap(0, 1);
	__kswap(3, 4);
	__kswap(5, 6);
	__kswap(3, 5);
	__kswap(4, 6);
	__kswap(4, 5);
	__kswap(0, 4);
	__kswap(0, 3);
	__kswap(1, 5);
	__kswap(2, 6);
	__kswap(2, 5);
	__kswap(1, 3);
	__kswap(2, 4);
	__kswap(2, 3);
#undef __kswap
#undef __kmax
#undef __kmin
}

void sort8(int *__restrict v)
{
#define __kmin(a, b) (a < b ? a : b)
#define __kmax(a, b) (a < b ? b : a)
#define __kswap(x, y)               \
	{                               \
		int a = __kmin(v[x], v[y]); \
		int b = __kmax(v[x], v[y]); \
		v[x] = a;                   \
		v[y] = b;                   \
	}
	__kswap(0, 1);
	__kswap(2, 3);
	__kswap(0, 2);
	__kswap(1, 3);
	__kswap(1, 2);
	__kswap(4, 5);
	__kswap(6, 7);
	__kswap(4, 6);
	__kswap(5, 7);
	__kswap(5, 6);
	__kswap(0, 4);
	__kswap(1, 5);
	__kswap(1, 4);
	__kswap(2, 6);
	__kswap(3, 7);
	__kswap(3, 6);
	__kswap(2, 4);
	__kswap(3, 5);
	__kswap(3, 4);
#undef __kswap
#undef __kmax
#undef __kmin
}

//typedef int T;

namespace quickint{

template <typename Tint>
Tint med3(Tint a, Tint b, Tint c)
{
    if (a < b)
    {
        if (b < c)
            return b;
        return a < c ? c : a;
    }
    else
    {
        if (b > c)
            return b;
        return a > c ? c : a;
    }
}

template <typename Tint>
void selsort(Tint *data, int len)
{
    for (int i = 1; i < len; ++i)
    {
        int j = i;
        Tint val = data[i];
        if (val < data[0])
            j = 0;
        else
            while (val < data[j - 1])
                --j;
        for (int k = i - 1; k >= j; --k)
            data[k + 1] = data[k];
        data[j] = val;
    }
}

template <typename Tint>
void selsortr(Tint *data, Tint *out, int len)
{
    if (!len)
        return;
    out[0] = data[0];
    for (int i = 1; i < len; ++i)
    {
        int j = i;
        Tint val = data[i];
        if (val < out[0])
            j = 0;
        else
            while (val < out[j - 1])
                --j;
        for (int k = i - 1; k >= j; --k)
            out[k + 1] = out[k];
        out[j] = val;
    }
}

//typedef __m256i mi;
__m256i shuf[256];
int adv[256];
__m128i shuf2[16];

template <typename Tint>
int part(Tint *data, Tint *out, int len, Tint pivot)
{
    int i = 0;
    int lefti = 0, righti = len;
    __m256i pivots = _mm256_set1_epi32(pivot); //Broadcast 32-bit integer a to all elements of dst.
    righti -= 8;
    while (i + 16 <= len)
    {
        __m256i vals = _mm256_loadu_si256((__m256i *)(data + i)); // Load 256-bits of integer data from unaligned memory into dst.
        __m256i cm = _mm256_cmpgt_epi32(pivots, vals); // Compare packed 32-bit integers in a and b for greater-than, and store the results in dst.
        int mask = _mm256_movemask_ps((__m256)cm); //Set each bit of mask dst based on the most significant bit of the corresponding packed single-precision (32-bit) floating-point element in a.
        vals = _mm256_permutevar8x32_epi32(vals, shuf[mask]); // Shuffle 32-bit integers in a across lanes using the corresponding index in idx, and store the results in dst.
        int ad = adv[mask];
        _mm256_storeu_si256((__m256i *)(out + lefti), vals); // Store 256-bits of integer data from a into memory
        _mm256_storeu_si256((__m256i *)(out + righti), vals);
        lefti += ad;
        righti -= 8 - ad;
        i += 8;
    }

    if (i + 8 < len)
    {
        __m128i pivots2 = _mm256_castsi256_si128(pivots); //Casts vector of type __m256i to type __m128i.
        do
        {
            __m128i vals = _mm_loadu_si128((__m128i *)(data + i));
            __m128i cm = _mm_cmpgt_epi32(pivots2, vals); //Compare packed 32-bit integers in a and b for greater-than, and store the results in dst.
            int mask = _mm_movemask_ps((__m128)cm); //Set each bit of mask dst based on the most significant bit of the corresponding packed single-precision (32-bit) floating-point element in a.
            vals = (__m128i)_mm_permutevar_ps((__m128)vals, shuf2[mask]); //Shuffle single-precision (32-bit) floating-point elements in a using the control in b, and store the results in dst.
            int ad = adv[mask];
            _mm_storeu_si128((__m128i *)(out + lefti), vals); // Store 128-bits of integer data from a into memory. 
            _mm_storeu_si128((__m128i *)(out + righti + 4), vals);
            lefti += ad;
            righti -= 4 - ad;
            i += 4;
        } while (i + 8 < len);
    }

    int pos = lefti + len - 8 - i;

    if (pos >= 0)
    {
        __m256i vals = _mm256_loadu_si256((__m256i *)(data + len - 8)); //Load 256-bits of integer data from unaligned memory into dst.
        __m256i vals2 = _mm256_loadu_si256((__m256i *)(out + pos));
        switch (len - i)
        {
        case 0:
            vals = _mm256_blend_epi32(vals2, vals, 0x00); // Blend packed 32-bit integers from a and b using control mask imm8, and store the results in dst.
            break;
        case 1:
            vals = _mm256_blend_epi32(vals2, vals, 0x80);
            break;
        case 2:
            vals = _mm256_blend_epi32(vals2, vals, 0xC0);
            break;
        case 3:
            vals = _mm256_blend_epi32(vals2, vals, 0xE0);
            break;
        case 4:
            vals = _mm256_blend_epi32(vals2, vals, 0xF0);
            break;
        case 5:
            vals = _mm256_blend_epi32(vals2, vals, 0xF8);
            break;
        case 6:
            vals = _mm256_blend_epi32(vals2, vals, 0xFC);
            break;
        case 7:
            vals = _mm256_blend_epi32(vals2, vals, 0xFE);
            break;
        case 8:
            vals = _mm256_blend_epi32(vals2, vals, 0xFF);
            break;
        }

        __m256i cm = _mm256_cmpgt_epi32(pivots, vals); //Compare packed 32-bit integers in a and b for greater-than, and store the results in dst.
        int mask = _mm256_movemask_ps((__m256)cm);
        vals = _mm256_permutevar8x32_epi32(vals, shuf[mask]);
        _mm256_storeu_si256((__m256i *)(out + pos), vals);
        return pos + adv[mask];
    }

    righti += 8;
    while (i < len)
    {
        Tint val = data[i];
        if (val < pivot)
        {
            out[lefti++] = val;
        }
        else
        {
            out[--righti] = val;
        }
        i++;
    }
    return lefti;
}

// if rev, final result should go in temp
template <bool rev, typename Tint>
void qs(Tint *data, Tint *temp, int len, Tint minv)
{
    if (len <= 20)
    {
        if (!rev){
            if(len==2)
                return sort2(data);
            else if(len ==3)
                return sort3(data);
            else if(len ==4)
                return simdsort4(data);
            else if(len ==5)
                return sort5(data);
            else if(len ==6)
                return sort6(data);
            else if(len ==7)
                return sort7(data);
            else if(len ==8)
                return sort8(data);

                
            else
                return selsort(data, len);
        }
        else
            {return selsortr(data, temp, len);}
    }
    Tint pivot = med3(data[len / 4], data[len / 2], data[len * 3 / 4]);
    if (pivot == minv)
    {
        if (minv == std::numeric_limits<Tint>::max())
        {
            if (rev)
                memcpy(temp, data, len * sizeof(Tint));
            return;
        }
        pivot++;
    }
    int mid = part(data, temp, len, pivot);
    if (pivot == minv + 1)
    {
        if (!rev)
            memcpy(data, temp, mid * sizeof(Tint));
    }
    else
    {
        qs<!rev>(temp, data, mid, minv);
    }
    qs<!rev>(temp + mid, data + mid, len - mid, pivot);
}

void init()
{
    for (int b = 0; b < 256; ++b)
    {
        adv[b] = (int)std::bitset<32>(b).count();
        int order[8];
        int lefti = 0, righti = 8;
        for (int i = 0; i < 8; ++i)
        {
            if (b & (1 << i))
                order[lefti++] = i;
            else
                order[--righti] = i;
        }
        shuf[b] = _mm256_loadu_si256((__m256i *)order);
    }
    for (int b = 0; b < 16; ++b)
    {
        int order[4];
        int lefti = 0, righti = 4;
        for (int i = 0; i < 4; ++i)
        {
            if (b & (1 << i))
                order[lefti++] = i;
            else
                order[--righti] = i;
        }
        shuf2[b] = _mm_loadu_si128((__m128i *)order);
    }
}

template <typename Tint>
void qs_int(std::vector<Tint> &vec)
{
    Tint *data = &vec[0];
    int len = vec.size();
    init();

    std::vector<Tint> temp(len);
    qs<false, Tint>(data, temp.data(), len, std::numeric_limits<Tint>::min());
}

} // namespace end
