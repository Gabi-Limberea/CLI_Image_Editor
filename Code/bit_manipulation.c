// Copyright 2021 - 2022: Limberea Gabriela 312CA
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <math.h>

#include "bit_manipulation.h"

void set_bit(int tmp, uint_fast8_t **bw, int i, int j)
{
	if (tmp)
		bw[i][j / 8] |= (1 << (j % 8));
}

int is_bit_set(uint_fast8_t **bw, int i, int j)
{
	return bw[i][j / 8] & (1 << (j % 8));
}

void set_bits_reversed(uint_fast8_t tmp, uint_fast8_t *bw)
{
	*bw = 0;
	for (u_long i = 0; i < 8 * SIZE_CHAR; i++)
		if (tmp & (1 << i))
			*bw |= 1 << (8 * SIZE_CHAR - i - 1);
}

void reset_bit(uint_fast8_t **bw, int i, int j)
{
	if (bw[i][j / 8] & (1 << (j % 8)))
		bw[i][j / 8] ^= (1 << (j % 8));
}
