// Copyright 2021 - 2022: Limberea Gabriela 312CA
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <math.h>

#include "load_image.h"

void load_img(status *img_status, char *filename, image *img,
			  selected_area *selected)
{
	fpos_t pos = {};

	// Check if filename is valid
	if (!filename) {
		printf(INVALID);
		return;
	}

	// Check if an image was already previously loaded, case in which
	// it free the resources to make room for the new one
	if (img_status->load == LOADED)
		reset(img, img_status);

	// read the header to Determine image type, size and color
	// intensity (if needed)
	if (read_header(filename, img, &pos) == ERROR) {
		printf(LOAD_FAIL, filename);
		return;
	}

	// Check image type
	if (img->type == NO_TYPE) {
		printf(LOAD_FAIL, filename);
		return;
	}

	// Determine how the image needs to be read
	if (img->type > P3)
		img_status->load = read_binary(filename, img, &pos);
	else
		img_status->load = read_ascii(filename, img, &pos);

	if (img_status->load == LOADED) {
		img_status->selection = SELECTED_ALL;
		selected->x1 = 0;
		selected->x2 = img->width;
		selected->y1 = 0;
		selected->y2 = img->height;

		printf(LOAD_OK, filename);
		return;
	}

	printf(LOAD_FAIL, filename);
}

int read_header(char *filename, image *img, fpos_t *pos)
{
	FILE *file = fopen(filename, "r");
	char *input = calloc(BUFSIZ, sizeof(char));
	int attributes = 0, keywords = DEFAULT + 1;

	// Check if the file has been opened correctly
	// and if the input string has been alloc'd right
	if (!file || !input) {
		free(input);
		return ERROR;
	}

	// Parse through the header and save the necessary info,
	// skipping comments
	for (int i = 0; i < keywords; i++) {
		fscanf(file, "%s", input);

		if (input[0] == '#') {
			fgets(input, BUFSIZ, file);
			keywords++;
		} else {
			switch (attributes) {
			case 0:
				img->type = chk_type(input);
				attributes++;
				break;
			case 1:
				img->width = atoi(input);
				attributes++;
				break;
			case 2:
				img->height = atoi(input);
				if (img->type == P1 || img->type == P4)
					keywords--;
				else
					attributes++;
				break;
			case 3:
				img->max_value = atoi(input);
				break;
			default:
				break;
			}
		}
	}

	// Get the position of the cursor in the file and free all
	// temporary resources
	fgetpos(file, pos);
	clean_up(file, input);
	return SUCCESS;
}

magic chk_type(char *input)
{
	if (!strcmp(input, "P1"))
		return P1;

	if (!strcmp(input, "P2"))
		return P2;

	if (!strcmp(input, "P3"))
		return P3;

	if (!strcmp(input, "P4"))
		return P4;

	if (!strcmp(input, "P5"))
		return P5;

	if (!strcmp(input, "P6"))
		return P6;

	return NO_TYPE;
}

load_status read_ascii(char *filename, image *img, fpos_t *pos)
{
	FILE *file = fopen(filename, "r");

	// Check if the file opened correctly
	if (!file) {
		fprintf(stderr, ERROR_MESSAGE);
		return NOT_LOADED;
	}

	// Jump to the previous position in the file
	fsetpos(file, pos);

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
		return NOT_LOADED;
	}

	fclose(file);
	return LOADED;
}

int read_channel_mono_ascii(FILE *file, image *img)
{
	switch (img->type) {
	case P1:
		img->pixels.bw = alloc_bw(img->width, img->height);

		// Check if channel was alloc'd correctly
		if (!img->pixels.bw) {
			free_channel_bw(img->pixels.bw, img->height);
			return ERROR;
		}

		for (int i = 0; i < img->height; i++) {
			for (int j = 0; j < img->width; j++) {
				// For each black pixel in the black & white image read, sets
				// the corresponding bit in the channel
				int tmp = 0;

				fscanf(file, "%d", &tmp);
				set_bit(tmp, img->pixels.bw, i, j);
			}
		}
		break;
	case P2:
		img->pixels.gray = alloc(img->width, img->height);

		// Check if channel was alloc'd correctly
		if (!img->pixels.gray) {
			free_channel(img->pixels.gray, img->height);
			return ERROR;
		}

		for (int i = 0; i < img->height; i++) {
			for (int j = 0; j < img->width; j++)
				fscanf(file, "%lf", &img->pixels.gray[i][j]);
		}
		break;
	default:
		return ERROR;
	}

	return SUCCESS;
}

int read_channel_rgb_ascii(FILE *file, image *img)
{
	img->pixels.red = alloc(img->width, img->height);
	img->pixels.green = alloc(img->width, img->height);
	img->pixels.blue = alloc(img->width, img->height);

	// Check if all channels were alloc'd correctly
	if (!img->pixels.red || !img->pixels.green || !img->pixels.blue) {
		free_channel(img->pixels.red, img->height);
		free_channel(img->pixels.green, img->height);
		free_channel(img->pixels.blue, img->height);
		return ERROR;
	}

	for (int i = 0; i < img->height; i++) {
		for (int j = 0; j < img->width; j++) {
			fscanf(file, "%lf", &img->pixels.red[i][j]);
			fscanf(file, "%lf", &img->pixels.green[i][j]);
			fscanf(file, "%lf", &img->pixels.blue[i][j]);
		}
	}

	return SUCCESS;
}

load_status read_binary(char *filename, image *img, fpos_t *pos)
{
	FILE *file = fopen(filename, "rb");

	if (!file) {
		fprintf(stderr, ERROR_MESSAGE);
		return NOT_LOADED;
	}

	// Jump to the previous position in the file and offset by 1
	fsetpos(file, pos);
	fseek(file, 1, SEEK_CUR);

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
		return NOT_LOADED;
	}

	fclose(file);
	return LOADED;
}

int read_channel_mono_binary(FILE *file, image *img)
{
	switch (img->type) {
	case P4:
		img->pixels.bw = alloc_bw(img->width, img->height);

		// Check if channel was alloc'd correctly
		if (!img->pixels.bw) {
			free_channel_bw(img->pixels.bw, img->height);
			return ERROR;
		}

		for (int i = 0; i < img->height; i++) {
			for (int j = 0; j < img->width; j++) {
				if (j % 8 == 0) {
					// Read a byte worth of data (a pixel) from the file and
					// set the bits reversed in the channel
					// Otherwise, they would be saved mirrored
					uint_fast8_t tmp = 0;

					fread(&tmp, SIZE_CHAR, 1, file);
					set_bits_reversed(tmp, &img->pixels.bw[i][j / 8]);
				}
			}
		}
		break;
	case P5:
		img->pixels.gray = alloc(img->width, img->height);

		// Check if channel was alloc'd correctly
		if (!img->pixels.gray) {
			free_channel(img->pixels.gray, img->height);
			return ERROR;
		}

		for (int i = 0; i < img->height; i++) {
			for (int j = 0; j < img->width; j++) {
				uint_fast8_t tmp = 0;

				fread(&tmp,  SIZE_CHAR, 1, file);
				img->pixels.gray[i][j] = (double)tmp;
			}
		}
		break;
	default:
		return ERROR;
	}

	return SUCCESS;
}

int read_channel_rgb_binary(FILE *file, image *img)
{
	img->pixels.red = alloc(img->width, img->height);
	img->pixels.green = alloc(img->width, img->height);
	img->pixels.blue = alloc(img->width, img->height);

	// Check if all channels were alloc'd correctly
	if (!img->pixels.red || !img->pixels.green || !img->pixels.blue) {
		free_channel(img->pixels.red, img->height);
		free_channel(img->pixels.green, img->height);
		free_channel(img->pixels.blue, img->height);
		return ERROR;
	}

	for (int i = 0; i < img->height; i++) {
		for (int j = 0; j < img->width; j++) {
			uint_fast8_t red = 0, green = 0, blue = 0;

			fread(&red, SIZE_CHAR, 1, file);
			fread(&green, SIZE_CHAR, 1, file);
			fread(&blue, SIZE_CHAR, 1, file);

			img->pixels.red[i][j] = (double)red;
			img->pixels.green[i][j] = (double)green;
			img->pixels.blue[i][j] = (double)blue;
		}
	}

	return SUCCESS;
}

void clean_up(FILE *file, char *input)
{
	free(input);
	fclose(file);
}
