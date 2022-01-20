// Copyright 2021 - 2022: Limberea Gabriela 312CA

#include "macros.h"
#include "bit_manipulation.h"
#include "miscelanious_utils.h"

#ifndef __apply__
#define __apply__

// Main function for the apply command
// Check command validity and decide which filter is applied
void apply(image *img, status img_status, char *param,
		   selected_area selected, int count);

// Check if the given filter is available
filters chk_filter(char *param);

// Apply the filter to the image
void apply_filter(image *img, selected_area selected,
				  const double kernel[DEFAULT][DEFAULT]);

// Check if the selection is within the borders of the image
void chk_borders(selected_area *selected, int width, int height);

// Apply the kernel to a pixel
double update_pixel(double **matrix, int i, int j,
					const double kernel[DEFAULT][DEFAULT]);


#endif
