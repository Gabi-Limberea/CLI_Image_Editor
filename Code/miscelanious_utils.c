// Copyright 2021 - 2022: Limberea Gabriela 312CA
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <math.h>

#include "miscelanious_utils.h"

double **alloc(int width, int height)
{
	double **matrix = calloc(height, SIZE_PTR);
	if (!matrix) {
		free(matrix);
		fprintf(stderr, ERROR_MESSAGE);
		return NULL;
	}

	for (int i = 0; i < height; i++) {
		matrix[i] = calloc(width, SIZE);

		if (!matrix[i]) {
			free_channel(matrix, i);
			fprintf(stderr, ERROR_MESSAGE);
			return NULL;
		}
	}

	return matrix;
}

double **copy_channel(double **matrix, int width, int height)
{
	double **copy = alloc(width, height);

	if (!copy) {
		free(copy);
		return NULL;
	}

	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			copy[i][j] = matrix[i][j];

	return copy;
}

uint_fast8_t **alloc_bw(int width, int height)
{
	uint_fast8_t **matrix = calloc(height, SIZE_PTR_CHAR);
	if (!matrix) {
		free(matrix);
		fprintf(stderr, ERROR_MESSAGE);
		return NULL;
	}

	for (int i = 0; i < height; i++) {
		matrix[i] = calloc(width, SIZE_CHAR);

		if (!matrix[i]) {
			free_channel_bw(matrix, i);
			fprintf(stderr, ERROR_MESSAGE);
			return NULL;
		}
	}

	return matrix;
}

void free_channel(double **matrix, int height)
{
	for (int i = 0; i < height; i++)
		free(matrix[i]);
	free(matrix);
}

void free_channel_bw(uint_fast8_t **matrix, int height)
{
	for (int i = 0; i < height; i++)
		free(matrix[i]);
	free(matrix);
}

void reset(image *img, status *img_status)
{
	if (img->type == P1 || img->type == P4) {
		free_channel_bw(img->pixels.bw, img->height);
	} else if (img->type == P2 || img->type == P5) {
		free_channel(img->pixels.gray, img->height);
	} else if (img->type == P3 || img->type == P6) {
		free_channel(img->pixels.red, img->height);
		free_channel(img->pixels.green, img->height);
		free_channel(img->pixels.blue, img->height);
	}

	img->width = 0;
	img->height = 0;
	img->start_line = DEFAULT;
	img->pixels.bw = NULL;
	img->pixels.gray = NULL;
	img->pixels.red = NULL;
	img->pixels.green = NULL;
	img->pixels.blue = NULL;
	img->type = NO_TYPE;
	img_status->load = NOT_LOADED;
	img_status->selection = NOTHING_SELECTED;
}

void swap_int(int *a, int *b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

void swap(double *a, double *b)
{
	double tmp = *a;
	*a = *b;
	*b = tmp;
}

void swap_double_ptr(double ***a, double ***b)
{
	double **tmp = *a;
	*a = *b;
	*b = tmp;
}

void swap_uint_ptr(uint_fast8_t ***a, uint_fast8_t ***b)
{
	uint_fast8_t **tmp = *a;
	*a = *b;
	*b = tmp;
}

void clamp(double *x, int min, int max)
{
	if (*x > max) {
		*x = (double)max;
		return;
	}

	if (*x < min) {
		*x = (double)min;
		return;
	}
}
