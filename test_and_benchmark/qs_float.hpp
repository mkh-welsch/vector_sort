//#include <bits/stdc++.h>
#include <bitset>
#include <immintrin.h>
#include <vector>
#include <limits>
//using namespace std;

//typedef int T;
namespace quickfloat{

// Chooses the middle of three values.
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

// Same as selsort but writes to 'out' instead of the input.
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
__m256 shuf[256];
int adv[256];
__m128 shuf2[16];

template <typename Tint>
int part(Tint *data, Tint *out, int len, Tint pivot)
{
    int i = 0;
    int lefti = 0, righti = len;
    __m256 pivots = _mm256_set1_ps(pivot); //Broadcast single-precision (32-bit) floating-point value a to all elements of dst.
    righti -= 8;
    while (i + 16 <= len)
    {
        __m256 vals = _mm256_loadu_ps((float *)(data +i)); // Load 256-bits (composed of 8 packed single-precision (32-bit) floating-point elements) from memory into dst
        __m256 cm = _mm256_cmp_ps(pivots, vals,14); // Compare packed 32-bit integers in a and b for greater-than, and store the results in dst.
        int mask = _mm256_movemask_ps((__m256)cm); //Set each bit of mask dst based on the most significant bit of the corresponding packed single-precision (32-bit) floating-point element in a.
        vals = _mm256_permutevar8x32_ps(vals, (__m256i)shuf[mask]); // Shuffle 32-bit integers in a across lanes using the corresponding index in idx, and store the results in dst.
        int ad = adv[mask];
        _mm256_storeu_ps((float *)(out + lefti), vals); // Store 256-bits (composed of 8 packed single-precision (32-bit) floating-point elements) from a into memory.
        _mm256_storeu_ps((float *)(out + righti), vals);
        lefti += ad;
        righti -= 8 - ad;
        i += 8;
    }

    if (i + 8 < len)
    {
        __m128 pivots2 = _mm256_castps256_ps128(pivots); //Casts vector of type __m256i to type __m128i.
        do
        {
            __m128 vals = _mm_loadu_ps((float *)(data + i));
            __m128 cm = _mm_cmpgt_ps(pivots2, vals); //Compare packed 32-bit integers in a and b for greater-than, and store the results in dst.
            int mask = _mm_movemask_ps((__m128)cm); //Set each bit of mask dst based on the most significant bit of the corresponding packed single-precision (32-bit) floating-point element in a.
            vals = (__m128)_mm_permutevar_ps((__m128)vals, (__m128i)shuf2[mask]); //Shuffle single-precision (32-bit) floating-point elements in a using the control in b, and store the results in dst.
            int ad = adv[mask];
            _mm_storeu_ps((float *)(out + lefti), vals); // Store 128-bits of integer data from a into memory. 
            _mm_storeu_ps((float *)(out + righti + 4), vals);
            lefti += ad;
            righti -= 4 - ad;
            i += 4;
        } while (i + 8 < len);
    }

    int pos = lefti + len - 8 - i;

    if (pos >= 0)
    {
        __m256 vals = _mm256_loadu_ps((float *)(data + len - 8)); //Load 256-bits of integer data from unaligned memory into dst.
        __m256 vals2 = _mm256_loadu_ps((float *)(out + pos));
        switch (len - i)
        {
        case 0:
            vals = _mm256_blend_ps(vals2, vals, 0x00); // Blend packed 32-bit integers from a and b using control mask imm8, and store the results in dst.
            break;
        case 1:
            vals = _mm256_blend_ps(vals2, vals, 0x80);
            break;
        case 2:
            vals = _mm256_blend_ps(vals2, vals, 0xC0);
            break;
        case 3:
            vals = _mm256_blend_ps(vals2, vals, 0xE0);
            break;
        case 4:
            vals = _mm256_blend_ps(vals2, vals, 0xF0);
            break;
        case 5:
            vals = _mm256_blend_ps(vals2, vals, 0xF8);
            break;
        case 6:
            vals = _mm256_blend_ps(vals2, vals, 0xFC);
            break;
        case 7:
            vals = _mm256_blend_ps(vals2, vals, 0xFE);
            break;
        case 8:
            vals = _mm256_blend_ps(vals2, vals, 0xFF);
            break;
        }

        __m256 cm = _mm256_cmp_ps(pivots, vals,14); //Compare packed 32-bit integers in a and b for greater-than, and store the results in dst.
        int mask = _mm256_movemask_ps((__m256)cm);
        vals = _mm256_permutevar8x32_ps(vals, (__m256i)shuf[mask]);
        _mm256_storeu_ps((float *)(out + pos), vals);
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
        if (!rev)
            return selsort(data, len);
        else
            return selsortr(data, temp, len);
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
        shuf[b] = _mm256_loadu_ps((float *)order);
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
        shuf2[b] = _mm_loadu_ps((float *)order);
    }
}

template <typename Tint>
void qs_float(std::vector<Tint> &vec)
{
    Tint *data = &vec[0];
    int len = vec.size();
    init();

    std::vector<Tint> temp(len);
    qs<false, Tint>(data, temp.data(), len, std::numeric_limits<Tint>::min());
}
} // namespace end
