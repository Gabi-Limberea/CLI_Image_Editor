// Copyright 2021 - 2022: Limberea Gabriela 312CA
#pragma once

#include "macros.h"
#include "outputs.h"
#include "bit_manipulation.h"

void free_channel(uint_fast8_t **matrix, int height);
void reset(image *img, status *img_status);
void clean_up(FILE *file, char *input);
int get_size_max_value(char *filename, image *img, long *current_position);
magic chk_type(char *filename, image *img, long *current_position);
uint_fast8_t **alloc_channel(int width, int height);
int read_channel_mono_ascii(FILE *file, image *img);
int read_channel_rgb_ascii(FILE *file, image *img);
load_status read_ascii(char *filename, image *img, long pos);
int read_channel_mono_binary(FILE *file, image *img);
int read_channel_rgb_binary(FILE *file, image *img);
load_status read_binary(char *filename, image *img, long pos);
char *load_img(status *img_status, char *filename, image *img);
