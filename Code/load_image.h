// Copyright 2021 - 2022: Limberea Gabriela 312CA
#pragma once

#include "macros.h"
#include "outputs.h"
#include "bit_manipulation.h"
#include "miscelanious_utils.h"

void clean_up(FILE * file, char *input);
int read_header(char *filename, image *img, fpos_t *pos);
magic chk_type(char *input);
int read_channel_mono_ascii(FILE *file, image *img);
int read_channel_rgb_ascii(FILE *file, image *img);
load_status read_ascii(char *filename, image *img, fpos_t *pos);
int read_channel_mono_binary(FILE *file, image *img);
int read_channel_rgb_binary(FILE *file, image *img);
load_status read_binary(char *filename, image *img, fpos_t *pos);
char *load_img(status *img_status, char *filename, image *img);
