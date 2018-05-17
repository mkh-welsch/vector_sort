// Copyright (c) S. D. Adams <s.d.adams.software@gmail.com>

#include <stdio.h>

int main (void)
{
    int i, j;
    for (i = 0; i < 256; ++i)
    {
        int k = 8;
        for (j = 0; j < 8; ++j)
        {
            if ((i >> j) & 0x1)
            {
                printf ("%d,", j);
                --k;
            }
        }
        while (k > 0)
        {
            printf ("0,");
            --k;
        }
        printf ("\n");
    }
    return 0;
}
