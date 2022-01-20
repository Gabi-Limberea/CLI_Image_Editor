// Copyright 2021 - 2022: Limberea Gabriela 312CA

#include "macros.h"

#ifndef __miscelanious__utils__
#define __miscelanious__utils__

// Alloc a color channel (except the black & white)
double **alloc(int width, int height);

// Copy a color channel
double **copy_channel(double **matrix, int width, int height);

// Alloc the black & white channel
uint_fast8_t **alloc_bw(int width, int height);

// Free a color channel (except the black & white)
void free_channel(double **matrix, int height);

// Free the black & white channel
void free_channel_bw(uint_fast8_t **matrix, int height);

// Reset all the channels and image info to default,
// as if no image has ever been loaded
void reset(image *img, status *img_status);

// Swap 2 ints
void swap_int(int *a, int *b);

// Swap 2 doubles
void swap(double *a, double *b);

// Clamp a double value between the min and max values
void clamp(double *x, int min, int max);

#endif
