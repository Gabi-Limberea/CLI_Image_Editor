// Copyright 2021 - 2022: Limberea Gabriela 312CA
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <math.h>

#include "apply.h"

// Main function for the apply command
// Check command validity and decide which filter is applied
void apply(image *img, status img_status, char *param,
		   selected_area selected, int count)
{
	// Check if an image is loaded
	if (img_status.load == NOT_LOADED) {
		printf(NO_IMG);
		return;
	}

	// Check if the command has the appropriate number of parameters
	if (count == 0) {
		printf(INVALID);
		return;
	}

	// Check if the image is the right type (P3 or P6)
	if (img->type != P3 && img->type != P6) {
		printf(APPLY_FAIL_GRAYSCALE);
		return;
	}

	// Check the parameter and get the filter
	filters filter = chk_filter(param);

	// Check if the filter is valid
	if (filter == INVALID_FILTER) {
		printf(APPLY_FAIL_PARAMETER);
		return;
	}

	switch (filter) {
	case EDGE:
		apply_filter(img, selected, edge);
		break;
	case SHARPEN:
		apply_filter(img, selected, sharpen);
		break;
	case BLUR:
		apply_filter(img, selected, blur);
		break;
	case GAUSSIAN_BLUR:
		apply_filter(img, selected, gauss_blur);
		break;
	default:
		return;
	}

	printf(APPLY_OK, param);
}

// Check if the given filter is available
filters chk_filter(char *param)
{
	if (!strcmp(param, "EDGE"))
		return -EDGE;

	if (!strcmp(param, "SHARPEN"))
		return SHARPEN;

	if (!strcmp(param, "BLUR"))
		return BLUR;

	if (!strcmp(param, "GAUSSIAN_BLUR"))
		return GAUSSIAN_BLUR;

	return INVALID_FILTER;
}

// Apply the given filter to the image
void apply_filter(image *img, selected_area selected,
				  const double kernel[DEFAULT][DEFAULT])
{
	// Check and updates selection coordinates accordingly
	chk_borders(&selected, img->width, img->height);

	double **red = NULL, **green = NULL, **blue = NULL;

	// Create a copy of each color channel
	red = copy_channel(img->pixels.red, img->width, img->height);
	green = copy_channel(img->pixels.green, img->width, img->height);
	blue = copy_channel(img->pixels.blue, img->width, img->height);

	// Check if the copies were created correctly
	if (!red || !green || !blue) {
		fprintf(stderr, ERROR_MESSAGE);
		return;
	}

	// Go through every pixel in the selection and updates it
	for (int i = selected.y1; i < selected.y2; i++) {
		for (int j = selected.x1; j < selected.x2; j++) {
			img->pixels.red[i][j] = update_pixel(red, i, j, kernel);
			img->pixels.green[i][j] = update_pixel(green, i, j, kernel);
			img->pixels.blue[i][j] = update_pixel(blue, i, j, kernel);

			clamp(&img->pixels.red[i][j], 0, img->max_value);
			clamp(&img->pixels.green[i][j], 0, img->max_value);
			clamp(&img->pixels.blue[i][j], 0, img->max_value);
		}
	}

	free_channel(red, img->height);
	free_channel(green, img->height);
	free_channel(blue, img->height);
}

// Check if the selection is within the borders of the image
void chk_borders(selected_area *selected, int width, int height)
{
	if (selected->x1 == 0)
		selected->x1++;
	else if (selected->x1 == width)
		selected->x1--;

	if (selected->y1 == 0)
		selected->y1++;
	else if (selected->y1 == height)
		selected->y1--;

	if (selected->x2 == width)
		selected->x2--;
	else if (selected->x2 == 0)
		selected->x2++;

	if (selected->y2 == height)
		selected->y2--;
	else if (selected->y2 == 0)
		selected->y2++;
}

// Apply the kernel to a pixel
double update_pixel(double **matrix, int i, int j,
					const double kernel[DEFAULT][DEFAULT])
{
	double sum = 0;

	for (int k = 0; k < DEFAULT; k++)
		for (int l = 0; l < DEFAULT; l++)
			sum += matrix[i - 1 + k][j - 1 + l] * kernel[k][l];

	return sum;
}
