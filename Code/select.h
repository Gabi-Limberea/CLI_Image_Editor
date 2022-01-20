// Copyright 2021 - 2022: Limberea Gabriela 312CA

#include "macros.h"
#include "miscelanious_utils.h"

#ifndef __select__
#define __select__

// Select the whole image
void select_all(status *img_status, image *img, selected_area *selected);

// Select the area determined by the given coordinates
void select_area(status *img_status, char **params, int count,
				 image *img, selected_area *selected);

// Check if the selection coordinates are valid
int chk_select(char **params, image * img);

// Check if the parameters are numbers
int chk_digits(char **params);

#endif
