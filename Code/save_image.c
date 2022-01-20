// Copyright 2021 - 2022: Limberea Gabriela 312CA
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <math.h>

#include "save_image.h"

void save_img(status img_status, char **params, image img, int count)
{
	// Check if the first parameter is valid (the filename)
	if (!params[0]) {
		printf(INVALID);
		return;
	}

	// Check if an image is loaded
	if (img_status.load == NOT_LOADED) {
		printf(NO_IMG);
		return;
	}

	int saved = NOTHING;

	// Check how many parameters the command got.
	// If there are two and the second is "ascii", save image as ascii.
	// If there is just one parameter (filename), save image as binary
	if (count == 2) {
		if (!strcmp(params[1], "ascii"))
			saved = save_ascii(params[0], img);
	} else {
		saved = save_binary(params[0], img);
	}

	if (saved == SAVE)
		printf(SAVE_OK, params[0]);
}

int save_ascii(char *filename, image img)
{
	FILE *file = fopen(filename, "w");

	// Check if file opened correctly
	if (!file)
		return ERROR;

	// Check the image format. If it was originally binary, change it to ascii
	magic tmp_type = img.type;
	if (tmp_type > P3)
		tmp_type -= 3;

	// Print header as ascii
	fprintf(file, "P%d\n", tmp_type + 1);
	fprintf(file, "%d %d\n", img.width, img.height);
	if (tmp_type > P1)
		fprintf(file, "%d\n", img.max_value);

	// Print pixels from the active channels
	for (int i = 0; i < img.height; i++) {
		for (int j = 0; j < img.width; j++) {
			switch (tmp_type) {
			case P1:
				// If a bit is set print "1", otherwise print "0" to file
				if (is_bit_set(img.pixels.bw, i, j))
					fprintf(file, "%u ", 1);
				else
					fprintf(file, "%u ", 0);
				break;
			case P2:
				fprintf(file, "%u ", (uint_fast8_t)img.pixels.gray[i][j]);
				break;
			case P3:
				fprintf(file, "%u ",
						(uint_fast8_t)round(img.pixels.red[i][j]));
				fprintf(file, "%u ",
						(uint_fast8_t)round(img.pixels.green[i][j]));
				fprintf(file, "%u ",
						(uint_fast8_t)round(img.pixels.blue[i][j]));
				break;
			default:
				return ERROR;
			}
		}
		fprintf(file, "\n");
	}

	fclose(file);
	return SAVE;
}

int save_binary(char *filename, image img)
{
	FILE *file = fopen(filename, "wb");
	uint_fast8_t gray, red, green, blue;

	// Check if file opened correctly
	if (!file)
		return ERROR;

	// Check the image format. If it was originally ascii, change it to binary
	magic tmp_type = img.type;
	if (tmp_type <= P3)
		tmp_type += 3;

	// Print header as ascii
	fprintf(file, "P%d\n", tmp_type + 1);
	fprintf(file, "%d %d\n", img.width, img.height);
	if (tmp_type > P4)
		fprintf(file, "%d\n", img.max_value);

	// Print pixels from active channels
	for (int i = 0; i < img.height; i++) {
		for (int j = 0; j < img.width; j++) {
			switch (tmp_type) {
			case P4:
				if (j % 8 == 0) {
					// Use a temporary variable to reverse one byte at a time.
					// It's reversed so it can print normally, otherwise it
					// would be mirrored
					uint_fast8_t tmp = 0;

					set_bits_reversed(img.pixels.bw[i][j / 8], &tmp);
					fwrite(&tmp, SIZE_CHAR, 1, file);
				}
				break;
			case P5:
				// Use a temporary byte-sized variable to print each pixel
				gray = (uint_fast8_t)img.pixels.gray[i][j];
				fwrite(&gray, SIZE_CHAR, 1, file);
				break;
			case P6:
				// Use temporary byte-sized variables to print each pixel in
				// all 3 channels
				red = (uint_fast8_t)round(img.pixels.red[i][j]);
				fwrite(&red, SIZE_CHAR, 1, file);

				green = (uint_fast8_t)round(img.pixels.green[i][j]);
				fwrite(&green, SIZE_CHAR, 1, file);

				blue = (uint_fast8_t)round(img.pixels.blue[i][j]);
				fwrite(&blue, SIZE_CHAR, 1, file);
				break;
			default:
				return ERROR;
			}
		}
	}

	fclose(file);
	return SAVE;
}
