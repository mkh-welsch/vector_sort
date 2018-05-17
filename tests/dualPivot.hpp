/*This Source Code Form is subject to the terms of the Mozilla Public
License, v. 2.0. If a copy of the MPL was not distributed with this
file, You can obtain one at http://mozilla.org/MPL/2.0/.
Michael Welsch (c) 2018
                                                                                                   
a dual pivot (quick)sort implementation for random access containers,
based on the Dart project (android) implementation, originally designed by 
Vladimir Yaroslavskiy. 
https://github.com/dart-lang/sdk/blob/master/sdk/lib/internal/sort.dart

*/

#pragma once

namespace dualPivot
{
template <typename ConType>
void sort(ConType &a, size_t lo = 0, size_t hi = -1);

namespace details
{
template <typename ConType>
void dualPivotSort_(ConType &a, size_t lo, size_t hi);

template <typename ConType>
void insertionSort_(ConType &a, size_t lo, size_t hi);

std::vector<std::pair<size_t, size_t>> bose_swaps(int n);

class sortNet;
} // end namespace details



namespace details
{

template <typename ConType>
void insertionSort_(ConType &a, size_t lo, size_t hi)
{
    typedef typename ConType::value_type T;
    T t, x;
    size_t i, j;
    for (i = lo + 1; i < hi; ++i)
    {
        for (j = i, t = a[i], x = t; j > lo && a[j - 1] > x; --j)
        {

            a[j] = a[j - 1];
        }
        a[j] = t;
    }
}

template <typename ConType>
void shell_sort_(ConType &arr, size_t left, size_t right)
{
    typedef typename ConType::value_type T;
    T tmp;
    size_t k = 1,
        len = (right-left) + 1,
        gap = (pow(3,k) - 1) / 2,
        cap = ceil(len/3);

    /* The outer loop uses the Knuth sequence. */
    while(gap < cap)
    {
        for(size_t i=gap; i<len; ++i)
        {
            tmp = arr[i];
            size_t j;
            for(j=1; j >= gap && arr[j-gap] > tmp; j -= gap)
            {
                arr[j]=arr[j-gap];
            }
            arr[j]=tmp;
        }
        gap = (pow(3, ++k) -1) / 2;
    }
}

//template< class RandomAccessIterator >
template <typename ConType>
void dualPivotSort_(ConType &a, size_t lo, size_t hi)
{
    //std::cout <<" dualPivotSort_ called with lo = "<<lo <<" and hi= "<<hi<< std::endl;
    typedef typename ConType::value_type T;
    // Compute the two pivots by looking at 5 elements.
    size_t sixth = (hi - lo) / 6 | 0,
           i1 = lo + sixth,
           i5 = hi - 1 - sixth,
           i3 = (lo + hi - 1) >> 1, // The midpoint.
        i2 = i3 - sixth,
           i4 = i3 + sixth;

    T e1 = a[i1], x1 = e1,
      e2 = a[i2], x2 = e2,
      e3 = a[i3], x3 = e3,
      e4 = a[i4], x4 = e4,
      e5 = a[i5], x5 = e5;

    T t;

    // sort the five elements
    if (x1 > x2)
        t = e1, e1 = e2, e2 = t, t = x1, x1 = x2, x2 = t;
    if (x4 > x5)
        t = e4, e4 = e5, e5 = t, t = x4, x4 = x5, x5 = t;
    if (x1 > x3)
        t = e1, e1 = e3, e3 = t, t = x1, x1 = x3, x3 = t;
    if (x2 > x3)
        t = e2, e2 = e3, e3 = t, t = x2, x2 = x3, x3 = t;
    if (x1 > x4)
        t = e1, e1 = e4, e4 = t, t = x1, x1 = x4, x4 = t;
    if (x3 > x4)
        t = e3, e3 = e4, e4 = t, t = x3, x3 = x4, x4 = t;
    if (x2 > x5)
        t = e2, e2 = e5, e5 = t, t = x2, x2 = x5, x5 = t;
    if (x2 > x3)
        t = e2, e2 = e3, e3 = t, t = x2, x2 = x3, x3 = t;
    if (x4 > x5)
        t = e4, e4 = e5, e5 = t, t = x4, x4 = x5, x5 = t;

    T pivot1 = e2, pivotValue1 = x2,
      pivot2 = e4, pivotValue2 = x4;

    a[i1] = e1;
    a[i2] = a[lo];
    a[i3] = e3;
    a[i4] = a[hi - 1];
    a[i5] = e5;

    size_t first = lo + 1, // First element in the middle partition.
        last = hi - 2;     // Last element in the middle partition.

    bool pivotsEqual = pivotValue1 <= pivotValue2 && pivotValue1 >= pivotValue2;
    if (pivotsEqual)
    {

        for (size_t k = first; k <= last; ++k)
        {
            if (a[k] < pivotValue1)
            {
                if (k != first)
                {
                    std::swap(a[k], a[first]);
                }
                ++first;
            }
            else if (a[k] > pivotValue1)
            {
                while (true)
                {
                    T lastValue = a[last];
                    if (lastValue > pivotValue1)
                    {
                        last--;
                        continue;
                    }
                    else if (lastValue < pivotValue1)
                    {
                        std::swap(a[first], a[k]);
                        std::swap(a[first++], a[last--]);
                        break;
                    }
                    else
                    {
                        std::swap(a[k], a[last--]);
                        break;
                    }
                }
            }
        }
    }
    else
    {
        for (size_t k = first; k <= last; k++)
        {
            if (a[k] < pivotValue1)
            {
                if (k != first)
                {
                    std::swap(a[k], a[first]);
                }
                ++first;
            }
            else
            {
                if (a[k] > pivotValue2)
                {
                    while (true)
                    {
                        T lastValue = a[last];
                        if (lastValue > pivotValue2)
                        {
                            last--;
                            if (last < k)
                                break;

                            continue;
                        }
                        else
                        {

                            if (lastValue < pivotValue1)
                            {
                                std::swap(a[first], a[k]);
                                std::swap(a[first++], a[last--]);
                            }
                            else
                            {
                                std::swap(a[k], a[last--]);
                            }
                            break;
                        }
                    }
                }
            }
        }
    }

    a[lo] = a[first - 1];
    a[first - 1] = pivot1;
    a[hi - 1] = a[last + 1];
    a[last + 1] = pivot2;

    sort(a, lo, first - 1);
    sort(a, last + 2, hi);

    if (pivotsEqual)
    {
        return;
    }

    if (first < i1 && last > i5)
    {

        T firstValue, lastValue;
        while ((firstValue = a[first]) <= pivotValue1 && firstValue >= pivotValue1)
            ++first;
        while ((lastValue = a[last]) <= pivotValue2 && lastValue >= pivotValue2)
            --last;

        for (size_t k = first; k <= last; k++)
        {
            if (a[k] <= pivotValue1 && a[k] >= pivotValue1)
            {
                if (k != first)
                {
                    std::swap(a[k], a[first]);
                }
                first++;
            }
            else
            {
                if (a[k] <= pivotValue2 && a[k] >= pivotValue2)
                {
                    while (true)
                    {
                        lastValue = a[last];
                        if (lastValue <= pivotValue2 && lastValue >= pivotValue2)
                        {
                            last--;
                            if (last < k)
                                break;
                            continue;
                        }
                        else
                        {
                            if (lastValue < pivotValue1)
                            {
                                std::swap(a[first], a[k]);
                                std::swap(a[first++], a[last--]);
                            }
                            else
                            {
                                std::swap(a[k], a[last--]);
                            }
                            break;
                        }
                    }
                }
            }
        }
    }

    sort(a, first, last + 1);
    return;
}

std::vector<std::pair<size_t, size_t>> bose_swaps(int n)
{
    std::vector<std::pair<size_t, size_t>> swaps;
    std::function<void(size_t, size_t)> P = [&](size_t i, size_t j) {
        /* print out in 0 based notation */
        swaps.push_back(std::make_pair(i - 1, j - 1));
        // printf("swap(%d, %d);\n", i - 1, j - 1);
    };

    std::function<void(size_t, size_t, size_t, size_t)> Pbracket = [&](size_t i, /* value of first element in sequence 1 */
                                                                       size_t x, /* length of sequence 1 */
                                                                       size_t j, /* value of first element in sequence 2 */
                                                                       size_t y) /* length of sequence 2 */
    {
        size_t a, b;

        if (x == 1 && y == 1)
            P(i, j); /* 1 comparison sorts 2 items */
        else if (x == 1 && y == 2)
        {
            /* 2 comparisons inserts an item into an
         * already sorted sequence of length 2. */
            P(i, (j + 1));
            P(i, j);
        }
        else if (x == 2 && y == 1)
        {
            /* As above, but inserting j */
            P(i, j);
            P((i + 1), j);
        }
        else
        {
            /* Recurse on shorter sequences, attempting
         * to make the length of one subsequence odd
         * and the length of the other even. If we
         * can do this, we eventually merge the two. */
            a = x / 2;
            b = (x & 1) ? (y / 2) : ((y + 1) / 2);
            Pbracket(i, a, j, b);
            Pbracket((i + a), (x - a), (j + b), (y - b));
            Pbracket((i + a), (x - a), j, b);
        }
    };

    std::function<void(size_t, size_t)> Pstar = [&](size_t i, /* value of first element in sequence */
                                                    size_t m) /* length of sequence */
    {
        size_t a;

        if (m > 1)
        {
            /* Partition into 2 shorter sequences,
         * generate a sorting method for each,
         * and merge the two sub-networks. */
            a = m / 2;
            Pstar(i, a);
            Pstar((i + a), (m - a));
            Pbracket(i, a, (i + a), (m - a));
        }
    };

    std::function<void(size_t)> bose = [&](size_t n) {
        Pstar(1, n); /* sort the sequence {X1,...,Xn} */
    };

    bose(n);
    return swaps;
}

class sortNet
{
  private:
    const size_t n;
    const std::vector<std::pair<size_t, size_t>> swaps;

  public:
    sortNet(size_t m) : n(m), swaps(bose_swaps(n)) {}

    template <typename ConType>
    const void operator()(ConType &a, size_t lo) const
    {
        for (int i = 0; i < swaps.size(); ++i)
        {
            if (a[lo + swaps[i].first] > a[lo + swaps[i].second])
            {
                std::swap(a[lo + swaps[i].first], a[lo + swaps[i].second]);
            }
        }
    }
};

} // end namespace details

static const details::sortNet staticSort_1(1);
static const details::sortNet staticSort_2(2);
static const details::sortNet staticSort_3(3);
static const details::sortNet staticSort_4(4);
static const details::sortNet staticSort_5(5);
static const details::sortNet staticSort_6(6);
static const details::sortNet staticSort_7(7);
static const details::sortNet staticSort_8(8);
static const details::sortNet staticSort_9(9);
static const details::sortNet staticSort_10(10);
static const details::sortNet staticSort_11(11);
static const details::sortNet staticSort_12(12);
static const details::sortNet staticSort_13(13);
static const details::sortNet staticSort_14(14);
static const details::sortNet staticSort_15(15);
static const details::sortNet staticSort_16(16);


template <typename ConType>
void sort(ConType &a, size_t lo, size_t hi)
{
    typedef typename ConType::value_type T;

    if (hi == size_t(-1))
    {
        hi = a.size();
    }

    if (hi - lo <= 8)
    {

        switch (hi - lo)
        {
        case 1:
            staticSort_1(a, lo);
            break;
        case 2:
            staticSort_2(a, lo);
            break;
        case 3:
            staticSort_3(a, lo);
            break;
        case 4:
            staticSort_4(a, lo);
            break;
        case 5:
            staticSort_5(a, lo);
            break;
        case 6:
            staticSort_6(a, lo);
            break;
        case 7:
            staticSort_7(a, lo);
            break;
        case 8:
            staticSort_8(a, lo);
            break;
        case 9:
            staticSort_9(a, lo);
            break;
        case 10:
            staticSort_10(a, lo);
            break;
        case 11:
            staticSort_11(a, lo);
            break;
        case 12:
            staticSort_12(a, lo);
            break;
        case 13:
            staticSort_13(a, lo);
            break;
        case 14:
            staticSort_14(a, lo);
            break;
        case 15:
            staticSort_15(a, lo);
            break;
        case 16:
            staticSort_16(a, lo);
    break;
        }
    }
    else if (hi-lo > 8 && hi - lo <= 32)
    {
        details::insertionSort_(a, lo, hi);
    }
    else
    {
        details::dualPivotSort_(a, lo, hi);
    }
}

} // end namespace
