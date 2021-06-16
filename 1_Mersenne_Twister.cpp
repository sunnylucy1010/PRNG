// MT19937
#include <stdio.h>
#include <iostream>

using namespace std;
// Period parameters
#define N 624
#define M 397
#define MATRIX_A 0x9908b0df   // constant vector a
#define UPPER_MASK 0x80000000 // most significant w-r bits
#define LOWER_MASK 0x7fffffff // least significant r bits

// Tempering parameters
#define TEMPERING_MASK_B 0x9d2c5680
#define TEMPERING_MASK_C 0xefc60000
#define TEMPERING_SHIFT_U(y) (y >> 11)
#define TEMPERING_SHIFT_S(y) (y << 7)
#define TEMPERING_SHIFT_T(y) (y << 15)
#define TEMPERING_SHIFT_L(y) (y >> 18)

static unsigned long mt[N]; // the array for the state vector
static int mti = N + 1;     // mt[N] is not initialized

// initializing the array with NONZERO seed

void sgenrand(unsigned long long seed)
{
    mt[0] = seed & 0xffffffff;
    for (mti = 1; mti < N; mti++)
    {
        mt[mti] = (69069 * mt[mti - 1]) & 0xffffffff;
    }
}

double genrand()
{
    unsigned long y;
    static unsigned long mag01[2] = {0x0, MATRIX_A};
    // mag01[x] = x * MATRIX_A for x = 0,1

    if (mti >= N)
    { // generate N words at one time
        int kk;

        if (mti == N + 1)   // if sgenrand() has not been called
            sgenrand(4357); //a default initial seed is used

        for (kk = 0; kk < N - M; kk++)
        {
            y = (mt[kk] & UPPER_MASK) | (mt[kk + 1] & LOWER_MASK);
            mt[kk] = mt[kk + M] ^ (y >> 1) ^ mag01[y & 0x1];
        }
        for (; kk < N - 1; kk++)
        {
            y = (mt[kk] & UPPER_MASK) | (mt[kk + 1] & LOWER_MASK);
            mt[kk] = mt[kk + (M - N)] ^ (y >> 1) ^ mag01[y & 0x1];
        }
        y = (mt[N - 1] & UPPER_MASK) | (mt[0] & LOWER_MASK);
        mt[N - 1] = mt[M - 1] ^ (y >> 1) ^ mag01[y & 0x1];

        mti = 0;
    }

    y = mt[mti++];
    y ^= TEMPERING_SHIFT_U(y);
    y ^= TEMPERING_SHIFT_S(y) & TEMPERING_MASK_B;
    y ^= TEMPERING_SHIFT_T(y) & TEMPERING_MASK_C;
    y ^= TEMPERING_SHIFT_L(y);

    return ((double)y / (unsigned long)0xffffffff); //reals
    // return y; // for integer generation
}

// output 1000 generated numbers
int main()
{
    int j;

    sgenrand(4357); //any nonzero integer can be used as a seed
    for (j = 0; j < 20; j++)
    {
        cout << genrand() << endl;
    }
}