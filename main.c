#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

#define ROTL(x,k)   (((x) << (k)) | ((x) >> (64 - (k))))
#define BITS(x,s,n) (((x) >> (64 - (s) - (n))) & ((1 << (n)) - 1))

static uint64_t
rnd(void)
{
    static uint64_t s0 = 0x5a6a1e0b57e250e6;
    static uint64_t s1 = 0x6b4328727d7058e5;
    uint64_t ret = s0 + s1;

    s1 ^= s0;
    s0 = ROTL(s0, 24) ^ s1 ^ (s1 << 16);
    s1 = ROTL(s1, 37);

    return ret;
}

int
main(int argc, char **argv)
{
    int K = 16;
    int N = 1 << K;
    uint64_t C = 100000;
    size_t R = 10000000;

    uint64_t *v = malloc(N * sizeof(uint64_t));

    if (!v)
        return 1;

    printf("# pop=%i init=%"PRIu64" round=%zu\n", N, C, R);

    for (int i = 0; i < N; i++)
        v[i] = C;

    size_t x = 0;

    for (int x = 0; x < 2500; x++) {
        for (size_t k = 0; k < R; k++) {
            uint64_t r = rnd();
            int i = BITS(r, 0, K);
            int j = BITS(r, K, K);
            int p = BITS(r, 2 * K, 5) + 1;
            uint64_t m = ((v[i] < v[j] ? v[i] : v[j]) * p) >> 9;
            v[i] += m;
            v[j] -= m;
        }

        int y = 0;
        uint64_t richer = 0;

        for (int i = 0; i < N; i++) {
            if (v[i] >= C) y++;
            if (v[i] > richer) richer = v[i];
        }

        printf("%i %i %f\n", x, y, (richer * 100.0) / (N * C));
    }

    return 0;
}
