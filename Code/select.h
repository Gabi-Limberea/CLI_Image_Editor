// Copyright 2021 - 2022: Limberea Gabriela 312CA
#pragma once

#include "macros.h"
#include "outputs.h"

void swap_values(uint_fast8_t *a, uint_fast8_t *b);
void select_area(status *img_status, char **parames, int count,
				 image *img, selected_area *selected);
void select_all(status *img_status, image *img, selected_area *selected);
