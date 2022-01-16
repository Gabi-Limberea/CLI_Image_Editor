// Copyright 2021 - 2022: Limberea Gabriela 312CA
#pragma once

#include "macros.h"
#include "outputs.h"
#include "bit_manipulation.h"
#include "miscelanious_utils.h"

void crop(image *img, selected_area *selected, status *img_status);
int exe_crop(uint_fast8_t ***matrix, selected_area *selected, int height);
int exe_crop_bw(uint_fast8_t ***matrix, selected_area *selected, int height);
