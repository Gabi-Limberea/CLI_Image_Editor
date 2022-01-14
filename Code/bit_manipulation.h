// Copyright 2021 - 2022: Limberea Gabriela 312CA
#pragma once

#include "macros.h"
#include "outputs.h"

void set_bit(int tmp, uint_fast8_t **bw, int i, int j);
int is_bit_set(uint_fast8_t **bw, int i, int j);
void set_bit_reversed(uint_fast8_t tmp, uint_fast8_t *bw);