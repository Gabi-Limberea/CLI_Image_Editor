// Copyright 2021 - 2022: Limberea Gabriela 312CA

#include "macros.h"
#include "bit_manipulation.h"
#include "miscelanious_utils.h"

#ifndef __rotate__
#define __rotate__

// Main function for the rotate command
// Check command validity and how the image will be rotated
void rotate(status * img_status, char *angle, image * img,
			selected_area * selected, int count);

// Determine which channel will be rotated
int rotate_all(image *img, int angle_val);

// Rotate the whole black & white channel
int exe_rotation_all_bw(uint_fast8_t ***matrix, int angle_val,
						int *width, int *height);

// Rotate any other channel
int exe_rotation_all(double ***matrix, int angle_val,
					 int *width, int *height);

// Check that the selection is square and determine which
// channel will be rotated
int rotate_select(image *img, int angle_val, selected_area selected);

// Rotate the selection for the black & white channel
int exe_rotation_bw(uint_fast8_t ***matrix, int angle_val,
					selected_area selected);


// Rotate the selection for any other channel
int exe_rotation(double ***matrix, int angle_val,
				 selected_area selected);

#endif
