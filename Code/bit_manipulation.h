// Copyright 2021 - 2022: Limberea Gabriela 312CA
#pragma once

#include "macros.h"

#ifndef __bit__manipulation__
#define __bit__manipulation__

// Set a bit at a given index
void set_bit(int tmp, uint_fast8_t **bw, int i, int j);

// Check if a given bit is set
int is_bit_set(uint_fast8_t **bw, int i, int j);

// Take a binary input and save it reversed
void set_bits_reversed(uint_fast8_t tmp, uint_fast8_t *bw);

// Reset a bit to 0
void reset_bit(uint_fast8_t **bw, int i, int j);

#endif
