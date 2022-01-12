// Copyright 2021 - 2022: Limberea Gabriela 312CA
#pragma once

#include "macros.h"
#include "outputs.h"
#include "bit_manipulation.h"

void save_img(status img_status, char **params, image img, int count);
int save_binary(char *filename, image img);
int save_ascii(char *filename, image img);

