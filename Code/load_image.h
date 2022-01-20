// Copyright 2021 - 2022: Limberea Gabriela 312CA

#include "macros.h"
#include "bit_manipulation.h"
#include "miscelanious_utils.h"

#ifndef __load__image__
#define __load__image__

// Main function for the load command
// Check if the given filename is valid, read the header and
// determine the image type
void load_img(status *img_status, char *filename, image *img,
			  selected_area *selected);

// Read the header
int read_header(char *filename, image *img, fpos_t *pos);

// Determine the image format
magic chk_type(char *input);

// Choose which color channel will be loaded for an ascii picture
load_status read_ascii(char *filename, image *img, fpos_t *pos);

// Alloc and read one of the monochrome channels in ascii
int read_channel_mono_ascii(FILE *file, image *img);

// Alloc and read the RGB channels in ascii
int read_channel_rgb_ascii(FILE *file, image *img);

// Choose which color channel will be loaded for a binary picture
load_status read_binary(char *filename, image *img, fpos_t *pos);

// Alloc and read one of the monochrome channels in binary
int read_channel_mono_binary(FILE *file, image *img);

// Alloc and read the RGB channels in binary
int read_channel_rgb_binary(FILE *file, image *img);

// Function to free the input and close the opened file
void clean_up(FILE *file, char *input);

#endif
