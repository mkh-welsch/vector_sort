#include <cstddef>
#include <iostream>
#include <vector>

using Swap = std::pair<size_t, size_t>;
using Swaps = std::vector<Swap>;

void P(Swaps &swaps, size_t i, size_t j)
{
    swaps.push_back(std::make_pair(i - 1, j - 1));
}

void Pbracket (Swaps &swaps,
               size_t i, /* value of first element in sequence 1 */
               size_t x, /* length of sequence 1 */
               size_t j, /* value of first element in sequence 2 */
               size_t y) /* length of sequence 2 */
{
    size_t a, b;

    if (x == 1 && y == 1)
    {
        P(swaps, i, j); /* 1 comparison sorts 2 items */
    }
    else if (x == 1 && y == 2)
    {
        /* 2 comparisons inserts an item into an
     * already sorted sequence of length 2. */
        P(swaps, i, (j + 1));
        P(swaps, i, j);
    }
    else if (x == 2 && y == 1)
    {
        /* As above, but inserting j */
        P(swaps, i, j);
        P(swaps, (i + 1), j);
    }
    else
    {
        /* Recurse on shorter sequences, attempting
     * to make the length of one subsequence odd
     * and the length of the other even. If we
     * can do this, we eventually merge the two. */
        a = x / 2;
        b = (x & 1) ? (y / 2) : ((y + 1) / 2);
        Pbracket(swaps, i, a, j, b);
        Pbracket(swaps, (i + a), (x - a), (j + b), (y - b));
        Pbracket(swaps, (i + a), (x - a), j, b);
    }
}

void Pstar (Swaps &swaps,
            size_t i, /* value of first element in sequence */
            size_t m) /* length of sequence */
{
    size_t a;

    if (m > 1)
    {
        /* Partition into 2 shorter sequences,
     * generate a sorting method for each,
     * and merge the two sub-networks. */
        a = m / 2;
        Pstar(swaps, i, a);
        Pstar(swaps, (i + a), (m - a));
        Pbracket(swaps, i, a, (i + a), (m - a));
    }
}

std::vector<std::pair<size_t, size_t>> bose_swaps(int n)
{
    std::vector<std::pair<size_t, size_t>> swaps;

    auto bose = [&](size_t n)
    {
        Pstar(swaps, 1, n); /* sort the sequence {X1,...,Xn} */
    };

    bose(n);

    return swaps;
}

int main()
{
    for (int i = 1; i <= 8; ++i)
    {
        std::vector<std::pair<size_t, size_t>> const s = bose_swaps(i);

        std::cout << "Bose Swaps " << i << std::endl;
        std::cout << "{";
        for (std::pair<size_t, size_t> p : s)
        {
            std::cout << "{" << p.first << ", " << p.second << "}, ";
        }
        std::cout << "}" << std::endl << std::endl;
    }
}
