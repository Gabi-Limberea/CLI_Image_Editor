// Copyright 2021 - 2022: Limberea Gabriela 312CA

#include "macros.h"
#include "miscelanious_utils.h"

#ifndef __select__
#define __select__

int chk_select(char **params, image * img);
int chk_digits(char **params);
void select_area(status *img_status, char **params, int count,
				 image *img, selected_area *selected);
void select_all(status *img_status, image *img, selected_area *selected);

#endif
