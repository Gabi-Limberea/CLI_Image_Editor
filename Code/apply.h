// Copyright 2021 - 2022: Limberea Gabriela 312CA
#pragma once

#include "macros.h"
#include "bit_manipulation.h"
#include "miscelanious_utils.h"

filters chk_filter(char *param);
void apply(image *img, status img_status, char *param,
		   selected_area selected, int count);
void apply_filter(image *img, selected_area selected,
				  const double kernel[DEFAULT][DEFAULT]);
double update_pixel(double **matrix, int i, int j,
					const double kernel[DEFAULT][DEFAULT]);
void chk_borders(selected_area *selected, int width, int height);
