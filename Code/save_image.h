// Copyright 2021 - 2022: Limberea Gabriela 312CA

#include "macros.h"
#include "bit_manipulation.h"

#ifndef __save__image__
#define __save__image__

void save_img(status img_status, char **params, image img, int count);
int save_binary(char *filename, image img);
int save_ascii(char *filename, image img);

#endif
