// Copyright 2021 - 2022: Limberea Gabriela 312CA
#pragma once

#include "macros.h"
#include "outputs.h"
#include "bit_manipulation.h"
#include "miscelanious_utils.h"

void rotate(status *img_status, char *angle, image *img,
				selected_area *selected);
int rotate_all(image *img, int angle_val);
int rotate_select(image *img, int angle_val, selected_area selected);
int exe_rotation(uint_fast8_t ***matrix, int angle_val,
				 selected_area selected);
int exe_rotation_bw();
int exe_rotation_all(uint_fast8_t ***matrix, int angle_val,
					  int *width, int *height);
int exe_rotation_all_bw(uint_fast8_t ***matrix, int angle_val,
					  int *width, int *height);
