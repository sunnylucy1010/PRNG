/* A C-program for TT800 */
#include <stdio.h>
#include <iostream>
#define N 25
#define M 7
using namespace std;

double genrand()
{
    unsigned long y;
    static int k = 0;
    static unsigned long x[N] = {/* initial seeds: N=25 words */
                                 0x95f24dab, 0x0b685215, 0xe76ccae7, 0xaf3ec239, 0x715fad23,
                                 0x24a590ad, 0x69e4b5ef, 0xbf456141, 0x96bc1b7b, 0xa7bdf825,
                                 0xc1de75b7, 0x8858a9c9, 0x2da87693, 0xb657f9dd, 0xffdc8a9f,
                                 0x8121da71, 0x8b823ecb, 0x885d05f5, 0x4e20cd47, 0x5a9ad5d9,
                                 0x512c0c03, 0xea857ccd, 0x4cc1d30f, 0x8891a8a1, 0xa6b7aadb};
    if (k == N)
    { /* generate N words at one time */
        int kk;
        for (kk = 0; kk < N - M; kk++)
        {
            if (x[kk] % 2 == 0)
            {
                x[kk] = x[kk + M] ^ (x[kk] >> 1);
            }
            else
            {
                x[kk] = x[kk + M] ^ (x[kk] >> 1) ^ 0x8ebfd028;
            } /* a */
        }
        for (; kk < N; kk++)
        {
            if (x[kk] % 2 == 0)
            {
                x[kk] = x[kk + (M - N)] ^ (x[kk] >> 1);
            }
            else
            {
                x[kk] = x[kk + (M - N)] ^ (x[kk] >> 1) ^ 0x8ebfd028;
            } /* a */
        }
        k = 0;
    }
    y = x[k++];
    y ^= (y << 7) & 0x2b5b2500;  /* s and b */
    y ^= (y << 15) & 0xdb8b0000; /* t and c */
    return ((double)y / (unsigned long)0xffffffff);
}

int main()
{
    int i = 0;
    while (i < 20)
    {
        cout << genrand() << endl;
        i++;
    }
}