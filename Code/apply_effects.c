// Copyright 2021 - 2022: Limberea Gabriela 312CA
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <math.h>

#include "apply_effects.h"

effects chk_effect(char *param)
{
	if (!strcmp(param, "EDGE"))
		return -EDGE;

	if (!strcmp(param, "SHARPEN"))
		return SHARPEN;

	if (!strcmp(param, "BLUR"))
		return BLUR;

	if (!strcmp(param, "GAUSSIAN_BLUR"))
		return GAUSSIAN_BLUR;

	return INVALID_EFFECT;
}

void apply(image *img, status img_status, char *param,
		   selected_area selected, int count)
{
	if (img_status.load == NOT_LOADED) {
		printf(NO_IMG);
		return;
	}

	if (count == 0) {
		printf(INVALID);
		return;
	}

	if (img->type != P3 && img->type != P6) {
		printf(APPLY_FAIL_GRAYSCALE);
		return;
	}

	effects effect = chk_effect(param);

	if (effect == INVALID_EFFECT) {
		printf(APPLY_FAIL_PARAMETER);
		return;
	}

	switch (effect) {
	case EDGE:
		apply_effect(img, selected, edge);
		break;
	case SHARPEN:
		apply_effect(img, selected, sharpen);
		break;
	case BLUR:
		apply_effect(img, selected, blur);
		break;
	case GAUSSIAN_BLUR:
		apply_effect(img, selected, gauss_blur);
		break;
	default:
		return;
	}

	printf(APPLY_OK, param);
}

void apply_effect(image *img, selected_area selected,
				  const double kernel[DEFAULT][DEFAULT])
{
	chk_borders(&selected, img->width, img->height);

	double **red = NULL, **green = NULL, **blue = NULL;

	red = copy_channel(img->pixels.red, img->width, img->height);
	green = copy_channel(img->pixels.green, img->width, img->height);
	blue = copy_channel(img->pixels.blue, img->width, img->height);

	if (!red || !green || !blue) {
		fprintf(stderr, ERROR_MESSAGE);
		return;
	}

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

double update_pixel(double **matrix, int i, int j,
					const double kernel[DEFAULT][DEFAULT])
{
	double sum = 0;

	for (int k = 0; k < DEFAULT; k++)
		for (int l = 0; l < DEFAULT; l++)
			sum += matrix[i - 1 + k][j - 1 + l] * kernel[k][l];

	return sum;
}

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
