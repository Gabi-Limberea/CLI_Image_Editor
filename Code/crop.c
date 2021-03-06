// Copyright 2021 - 2022: Limberea Gabriela 312CA
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "crop.h"

void crop(image *img, selected_area *selected, status *img_status)
{
	// Check if an image is loaded
	if (img_status->load == NOT_LOADED) {
		printf(NO_IMG);
		return;
	}

	// Check if the whole image is selected, in which case it does nothing
	if (img_status->selection == SELECTED_ALL) {
		printf(CROP_OK);
		return;
	}

	// Select the channel that will be cropped
	switch (img->type) {
	case P1:
	case P4:
		if (exe_crop_bw(&img->pixels.bw, selected, img->height) == ERROR)
			return;
		break;
	case P2:
	case P5:
		if (exe_crop(&img->pixels.gray, selected, img->height) == ERROR)
			return;
		break;
	case P3:
	case P6:
		if (exe_crop(&img->pixels.red, selected, img->height) == ERROR ||
			exe_crop(&img->pixels.green, selected, img->height) == ERROR ||
			exe_crop(&img->pixels.blue, selected, img->height) == ERROR)
			return;
		break;
	default:
		return;
	}

	// Update image dimensions and selection status
	img->width = selected->x2 - selected->x1;
	img->height = selected->y2 - selected->y1;

	selected->x1 = 0;
	selected->x2 = img->width;
	selected->y1 = 0;
	selected->y2 = img->height;

	img_status->selection = SELECTED_ALL;
	printf(CROP_OK);
}

int exe_crop_bw(uint_fast8_t ***matrix, selected_area *selected, int height)
{
	int width_new = selected->x2 - selected->x1;
	int height_new = selected->y2 - selected->y1;
	uint_fast8_t **copy = *matrix;

	// Alloc a new matrix for the channel
	*matrix = alloc_bw(width_new, height_new);
	if (!(*matrix))
		return ERROR;

	// Copy the set bits within the selection to the new matrix
	for (int i = 0; i < height_new; i++)
		for (int j = 0; j < width_new; j++)
			if (is_bit_set(copy, i, j))
				set_bit(1, (*matrix), i - selected->y1, j - selected->x1);

	free_channel_bw(copy, height);
	return SUCCESS;
}

int exe_crop(double ***matrix, selected_area *selected, int height)
{
	int width_new = selected->x2 - selected->x1;
	int height_new = selected->y2 - selected->y1;
	double **copy = *matrix;

	// Alloc a new matrix for the channel
	*matrix = alloc(width_new, height_new);
	if (!(*matrix))
		return ERROR;

	// Copy the pixels within the selection to the new matrix
	for (int i = selected->y1; i < selected->y2; i++)
		for (int j = selected->x1; j < selected->x2; j++)
			(*matrix)[i - selected->y1][j - selected->x1] = copy[i][j];

	free_channel(copy, height);
	return SUCCESS;
}
