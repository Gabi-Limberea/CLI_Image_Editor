// Copyright 2021 - 2022: Limberea Gabriela 312CA
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "miscelanious_utils.h"

uint_fast8_t **alloc_channel(int width, int height)
{
	uint_fast8_t **matrix = calloc(height, sizeof(uint_fast8_t *));
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

void free_channel(uint_fast8_t **matrix, int height)
{
	for (int i = 0; i < height; i++)
		free(matrix[i]);
	free(matrix);
}

void reset(image *img, status *img_status)
{
	if (img->type == P1 || img->type == P4) {
		free_channel(img->pixels.bw, img->height);
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

void swap_values(int *a, int *b)
{
	int t = *a;
	*a = *b;
	*b = t;
}