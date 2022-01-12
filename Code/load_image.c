// Copyright 2021 - 2022: Limberea Gabriela 312CA
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "load_image.h"

void clean_up(FILE *file, char *input)
{
	free(input);
	fclose(file);
}

void parse_comments(FILE *file, char *input, image *img)
{
	fgets(input, BUFSIZ, file);
		while (input[0] == '#') {
			img->start_line++;
			fgets(input, BUFSIZ, file);
		}
		if (strchr(input, '\n'))
			input[strlen(input) - 1] = '\0';
}

magic chk_type(char *filename, image *img, long *pos)
{
	FILE *file = fopen(filename, "r");
	char *input = calloc(BUFSIZ, sizeof(char));

	if (!input || !file) {
		free(input);
		return NO_TYPE;
	}

	parse_comments(file, input, img);

	*pos = ftell(file);
	if (strchr(input, '\n'))
		input[strlen(input) - 1] = '\0';

	if (!strcmp(input, "P1")) {
		clean_up(file, input);
		return P1;
	}

	if (!strcmp(input, "P2")) {
		clean_up(file, input);
		return P2;
	}

	if (!strcmp(input, "P3")) {
		clean_up(file, input);
		return P3;
	}

	if (!strcmp(input, "P4")) {
		clean_up(file, input);
		return P4;
	}

	if (!strcmp(input, "P5")) {
		clean_up(file, input);
		return P5;
	}
	if (!strcmp(input, "P6")) {
		clean_up(file, input);
		return P6;
	}

	clean_up(file, input);
	return NO_TYPE;
}

int get_size_max_value(char *filename, image *img, long *pos)
{
	FILE *file = fopen(filename, "r");
	char *input = calloc(BUFSIZ, sizeof(char));
	int attributes = 0;

	if (!file || !input) {
		fprintf(stderr, ERROR_MESSAGE);
		return ERROR;
	}

	fseek(file, *pos, SEEK_SET);
	for (int i = 0; i < DEFAULT - 1; i++) {
		parse_comments(file, input, img);

		if (attributes < 2) {
			char *token = strtok(input, " ");

			while (token && attributes < 2) {
				if (attributes == 0)
					img->width = atoi(token);
				else if (attributes == 1)
					img->height = atoi(token);

				token = strtok(NULL, " ");
				attributes++;
			}
		}
	}

	if (img->type != P1 && img->type != P4) {
		if (attributes == 2) {
			img->max_value = atoi(input);
			attributes++;
		}
		parse_comments(file, input, img);
	}

	*pos = ftell(file) - strlen(input) - 1;
	clean_up(file, input);
	return SUCCESS;
}

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

int read_channel_mono_ascii(FILE *file, image *img)
{
	switch (img->type) {
	case P1:
		img->pixels.bw = alloc_channel(img->width, img->height);
		for (int i = 0; i < img->height; i++) {
			for (int j = 0; j < img->width; j++) {
				int tmp;
				fscanf(file, "%d", &tmp);
				set_bit(tmp, img->pixels.bw, i, j);
			}
		}
		break;
	case P2:
		img->pixels.gray = alloc_channel(img->width, img->height);
		for (int i = 0; i < img->height; i++) {
			for (int j = 0; j < img->width; j++)
				fscanf(file, "%hhu", &img->pixels.gray[i][j]);
		}
		break;
	default:
		return ERROR;
		break;
	}

	return SUCCESS;
}

int read_channel_rgb_ascii(FILE *file, image *img)
{
	img->pixels.red = alloc_channel(img->width, img->height);
	img->pixels.green = alloc_channel(img->width, img->height);
	img->pixels.blue = alloc_channel(img->width, img->height);

	if (!img->pixels.red || !img->pixels.green || !img->pixels.blue)
		return ERROR;

	for (int i = 0; i < img->height; i++) {
		for (int j = 0; j < img->width; j++) {
			fscanf(file, "%hhu", &img->pixels.red[i][j]);
			fscanf(file, "%hhu", &img->pixels.green[i][j]);
			fscanf(file, "%hhu", &img->pixels.blue[i][j]);
		}
	}

	return SUCCESS;
}

load_status read_ascii(char *filename, image *img, long pos)
{
	FILE *file = fopen(filename, "r");

	if (!file) {
		fprintf(stderr, ERROR_MESSAGE);
		return NOT_LOADED;
	}

	fseek(file, pos, SEEK_SET);
	switch (img->type) {
	case P1:
		if (read_channel_mono_ascii(file, img) == ERROR)
			return NOT_LOADED;
		break;
	case P2:
		if (read_channel_mono_ascii(file, img) == ERROR)
			return NOT_LOADED;
		break;
	case P3:
		if (read_channel_rgb_ascii(file, img) == ERROR)
			return NOT_LOADED;
		break;
	default:
		break;
	}

	fclose(file);
	return LOADED;
}

int read_channel_mono_binary(FILE *file, image *img)
{
	switch (img->type) {
	case P4:
		img->pixels.bw = alloc_channel(img->width, img->height);
		for (int i = 0; i < img->height; i++) {
			for (int j = 0; j < img->width; j++) {
				if (j % 8 == 0) {
					uint_fast8_t tmp;
					fread(&tmp, SIZE, 1, file);
					set_bit_reversed(tmp, &img->pixels.bw[i][j / 8]);
				}
			}
		}
		break;
	case P5:
		img->pixels.gray = alloc_channel(img->width, img->height);
		for (int i = 0; i < img->height; i++) {
			for (int j = 0; j < img->width; j++)
				fread(&img->pixels.gray[i][j], SIZE, 1, file);
		}
		break;
	default:
		return ERROR;
		break;
	}

	return SUCCESS;
}

int read_channel_rgb_binary(FILE *file, image *img)
{
	img->pixels.red = alloc_channel(img->width, img->height);
	img->pixels.green = alloc_channel(img->width, img->height);
	img->pixels.blue = alloc_channel(img->width, img->height);

	if (!img->pixels.red || !img->pixels.green || !img->pixels.blue)
		return ERROR;

	for (int i = 0; i < img->height; i++) {
		for (int j = 0; j < img->width; j++) {
			fread(&img->pixels.red[i][j], SIZE, 1, file);
			fread(&img->pixels.green[i][j], SIZE, 1, file);
			fread(&img->pixels.blue[i][j], SIZE, 1, file);
		}
	}

	return SUCCESS;
}

load_status read_binary(char *filename, image *img, long pos)
{
	FILE *file = fopen(filename, "rb");

	if (!file) {
		fprintf(stderr, ERROR_MESSAGE);
		return NOT_LOADED;
	}

	fseek(file, pos, SEEK_SET);
	switch (img->type) {
	case P4:
		if (read_channel_mono_binary(file, img) == ERROR)
			return NOT_LOADED;
		break;
	case P5:
		if (read_channel_mono_binary(file, img) == ERROR)
			return NOT_LOADED;
		break;
	case P6:
		if (read_channel_rgb_binary(file, img) == ERROR)
			return NOT_LOADED;
		break;
	default:
		break;
	}

	fclose(file);
	return LOADED;
}

char *load_img(status *img_status, char *filename, image *img)
{
	long pos = 0;

	if (img_status->load == LOADED)
		reset(img, img_status);

	img->type = chk_type(filename, img, &pos);
	if (img->type == NO_TYPE)
		return LOAD_FAIL;

	if (get_size_max_value(filename, img, &pos) == ERROR)
		return LOAD_FAIL;

	if (img->type > P3)
		img_status->load = read_binary(filename, img, pos);
	else
		img_status->load = read_ascii(filename, img, pos);

	if (img_status->load == LOADED) {
		img_status->selection = SELECTED_ALL;
		return LOAD_OK;
	}

	return LOAD_FAIL;
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
