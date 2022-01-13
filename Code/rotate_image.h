// Copyright 2021 - 2022: Limberea Gabriela 312CA
#pragma once

#include "macros.h"
#include "outputs.h"
#include "bit_manipulation.h"
#include "miscelanious_utils.h"

void rotate(status *img_status, char *angle, image *img,
				selected_area *selected);
int rotate_all(image *img, int angle_value);
int rotate_select(image *img, int angle_value, selected_area *selected);
int exec_rotation_select();
int exec_rotation_select_bw();
int exec_rotation_all(uint_fast8_t ***matrix, int angle_value,
					  int *width, int *height);
int exec_rotation_all_bw(uint_fast8_t ***matrix, int angle_value,
					  int *width, int *height);
