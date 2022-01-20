// Copyright 2021 - 2022: Limberea Gabriela 312CA

#include "macros.h"
#include "bit_manipulation.h"
#include "miscelanious_utils.h"

#ifndef __crop__
#define __crop__

// Main function for the crop command
// Check the type of image loaded and how it needs to be cropped
void crop(image * img, selected_area * selected, status * img_status);

// Crop the black & white, bit based channel
int exe_crop_bw(uint_fast8_t ***matrix, selected_area *selected, int height);

// Crops all other image formats (grayscale and RGB)
int exe_crop(double ***matrix, selected_area *selected, int height);

#endif
