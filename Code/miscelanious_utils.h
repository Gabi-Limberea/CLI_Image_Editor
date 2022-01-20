// Copyright 2021 - 2022: Limberea Gabriela 312CA

#include "macros.h"

#ifndef __miscelanious__utils__
#define __miscelanious__utils__

void free_channel(double **matrix, int height);
void free_channel_bw(uint_fast8_t **matrix, int height);
double **alloc(int width, int height);
double **copy_channel(double **matrix, int width, int height);
uint_fast8_t **alloc_bw(int width, int height);
void reset(image *img, status *img_status);
void swap_int(int *a, int *b);
void swap(double *a, double *b);
void clamp(double *x, int min, int max);

#endif
