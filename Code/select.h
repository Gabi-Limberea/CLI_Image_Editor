// Copyright 2021 - 2022: Limberea Gabriela 312CA
#pragma once

#include "macros.h"
#include "outputs.h"
#include "miscelanious_utils.h"

int chk_select(char **params, image * img);
int chk_digits(char **params);
void select_area(status *img_status, char **params, int count,
				 image *img, selected_area *selected);
void select_all(status *img_status, image *img, selected_area *selected);
