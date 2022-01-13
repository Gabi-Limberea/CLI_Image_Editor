// Copyright 2021 - 2022: Limberea Gabriela 312CA
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "rotate_image.h"

int exec_rotation_select_bw()
{
	return SUCCESS;
}

int exec_rotation_select()
{
	return SUCCESS;
}

int rotate_select(image *img, int angle_value, selected_area *selected)
{
	switch (img->type) {
	case P1:
	case P4:
		if (exec_rotation_select_bw() == ERROR)
			return ERROR;
		break;
	case P2:
	case P5:
		if (exec_rotation_select() == ERROR)
			return ERROR;
		break;
	case P3:
	case P6:
		if (exec_rotation_select() == ERROR ||
			exec_rotation_select() == ERROR ||
			exec_rotation_select() == ERROR)
			return ERROR;
		break;
	default:
		return ERROR;
	}

	return SUCCESS;
}

int rotate_all(image *img, int angle_value)
{
	switch (img->type) {
	case P1:
	case P4:
		if (exec_rotation__all_bw(&img->pixels.bw, angle_value,
								  &img->width, &img->height) == ERROR)
			return ERROR;
		break;
	case P2:
	case P5:
		if (exec_rotation_all(&img->pixels.gray, angle_value,
							  &img->width, &img->height) == ERROR)
			return ERROR;
		break;
	case P3:
	case P6:
		if (exec_rotation_all(&img->pixels.red, angle_value,
							  &img->width, &img->height) == ERROR ||
			exec_rotation_all(&img->pixels.green, angle_value,
							  &img->width, &img->height) == ERROR ||
			exec_rotation_all(&img->pixels.blue, angle_value,
							  &img->width, &img->height) == ERROR)
			return ERROR;
		break;
	default:
		return ERROR;
	}

	return SUCCESS;
}

int exec_rotation_all(uint_fast8_t ***matrix, int angle_value,
					  int *width, int *height)
{
	int rotations = angle_value / DEFAULT_ANGLE;
	if (rotations >= 0) {
		while (rotations) {
			uint_fast8_t **copy = *matrix;
			int width_new = *height, height_new = *width;

			*matrix = alloc_channel(width_new, height_new);
			if (!(*matrix))
				return ERROR;

			for (int i = 0; i < height_new; i++)
				for (int j = 0; j < width_new; j++)
					(*matrix)[i][j] = copy[*height - j - 1][i];

			free_channel(copy, *height);
			rotations--;
			*width = width_new;
			*height = height_new;
		}
	} else {
		while (rotations) {
			uint_fast8_t **copy = *matrix;
			int width_new = *height, height_new = *width;

			*matrix = alloc_channel(width_new, height_new);
			if (!(*matrix))
				return ERROR;

			for (int i = 0; i < height_new; i++)
				for (int j = 0; j < width_new; j++)
					(*matrix)[i][j] = copy[j][*width - i - 1];

			free_channel(copy, *height);
			rotations++;
			*width = width_new;
			*height = height_new;
		}
	}
	return SUCCESS;
}

int exec_rotation_all_bw(uint_fast8_t ***matrix, int angle_value,
						 int *width, int *height)
{
	return SUCCESS;
}

void rotate(status *img_status, char *angle, image *img,
			selected_area *selected)
{
	if (img_status->load == NOT_LOADED) {
		printf(NO_IMG);
		return;
	}

	int angle_value = atoi(angle);
	if (angle_value % DEFAULT_ANGLE != 0 || angle_value > DEFAULT_ANGLE * 4 ||
		angle_value < DEFAULT_ANGLE * (-4)) {
		printf(ROTATE_FAIL_ANGlE);
		return;
	}

	if (img_status->selection == SELECTED_ALL) {
		if (rotate_all(img, angle_value) == SUCCESS)
			printf(ROTATE_OK, angle);
		else
			fprintf(stderr, ERROR_MESSAGE);
		return;
	}

	if (selected->x2 - selected->x1 == selected->y2 - selected->y1) {
		if (rotate_select(img, angle_value, selected) == SUCCESS)
			printf(ROTATE_OK, angle);
		else
			fprintf(stderr, ERROR_MESSAGE);
		return;
	}

	printf(ROTATE_FAIL_SQUARE);
}
