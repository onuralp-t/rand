#ifndef RANDWRITE_H
#define RANDWRITE_H

// ======== USAGE ========
/* 
#define RANDWRITE_IMPLEMENTATION
#include "randwrite.h"

#include <stdio.h>
#include <time.h>

int main(void)
{
    xo_state rng = {0};
    srand_xo(&rng, time(0));

    printf("Random number: %lld \n", (int64_t)rand_xo(&rng));

    return 0;
}
*/

#include <stdint.h>

typedef struct xo_state { uint64_t s[4]; } xo_state;

uint64_t splitmix64(uint64_t *seed);

void srand_xo(xo_state *state, uint64_t seed);
uint64_t rand_xo(xo_state *state);

#endif // RANDWRITE_H

// ==========================================

#ifdef RANDWRITE_IMPLEMENTATION

uint64_t splitmix64(uint64_t *seed)
{
	uint64_t result = (*seed += 0x9E3779B97F4A7C15);
	result = (result ^ (result >> 30)) * 0xBF58476D1CE4E5B9;
	result = (result ^ (result >> 27)) * 0x94D049BB133111EB;
	return result ^ (result >> 31);
}

static inline uint64_t rol64(uint64_t x, int k)
{
	return (x << k) | (x >> (64 - k));
}

uint64_t rand_xo(xo_state *state)
{
	uint64_t *s = state->s;
	uint64_t const result = rol64(s[0] + s[3], 23) + s[0];
	uint64_t const t = s[1] << 17;

	s[2] ^= s[0];
	s[3] ^= s[1];
	s[1] ^= s[2];
	s[0] ^= s[3];

	s[2] ^= t;
	s[3] = rol64(s[3], 45);

	return result;
}

void srand_xo(xo_state *state, uint64_t seed)
{
	uint64_t smstate = seed;

	uint64_t tmp = splitmix64(&smstate);
	state->s[0] = (uint32_t)tmp;
	state->s[1] = (uint32_t)(tmp >> 32);

	tmp = splitmix64(&smstate);
	state->s[2] = (uint32_t)tmp;
	state->s[3] = (uint32_t)(tmp >> 32);
}

#endif // RANDWRITE_IMPLEMENTATION