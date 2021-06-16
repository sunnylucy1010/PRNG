// file:///E:/20202/Project1/xorshift.pdf

#include <bits/stdc++.h>
using namespace std;

unsigned long xorshift32()
{
    static unsigned long y = 2463534242;
    y ^= (y << 13);
    y = (y >> 17);
    return (y ^= (y << 5));
}

unsigned long long xor64()
{
    static unsigned long long x = 88172645463325252LL;
    x ^= (x << 13);
    x ^= (x >> 7);
    return (x ^= (x << 17));
}

unsigned long xor128()
{
    static unsigned long x = 123456789, y = 362436069, z = 521288629, w = 88675123;
    unsigned long t;
    t = (x ^ (x << 11));
    x = y;
    y = z;
    z = w;
    return (w = (w ^ (w >> 19)) ^ (t ^ (t >> 8)));
}

unsigned long xorwow()
{
    static unsigned long x = 123456789, y = 362436069, z = 521288629,
                         w = 88675123, v = 5783321, d = 6615241;
    unsigned long t;
    t = (x ^ (x >> 2));
    x = y;
    y = z;
    z = w;
    w = v;
    v = (v ^ (v << 4)) ^ (t ^ (t << 1));
    return (d += 362437) + v;
}

unsigned long mwc() //multiply-with-carry
{
    static unsigned long x = 123456789, y = 362436069, z = 77465321, c = 13579;
    unsigned long long t;
    t = 916905990LL * x + c;
    x = y;
    y = z;
    c = (t >> 32);
    return z = (t & 0xffffffff);
}

int main()
{
    cout << xorshift32() << endl;
    cout << xor64() << endl;
    cout << xor128() << endl;
    cout << xorwow() << endl;
    cout << mwc() << endl;
}