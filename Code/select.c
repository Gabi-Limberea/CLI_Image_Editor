// Copyright 2021 - 2022: Limberea Gabriela 312CA
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "select.h"

void select_area(status *img_status, char **params, int count,
				 image *img, selected_area *selected)
{
	if (img_status->load == NOT_LOADED) {
		printf(NO_IMG);
		return;
	}

	if (count < PARAMETERS_MAX) {
		printf(SELECT_ZONE_FAIL);
		return;
	}

	for (int i = 0; i < count; i++) {
		if (atoi(params[i]) > img->width ||
			atoi(params[i]) > img->height || atoi(params[i]) < 0) {
			printf(SELECT_ZONE_FAIL);
			return;
		}
	}

	selected->x1 = atoi(params[0]);
	selected->y1 = atoi(params[1]);
	selected->x2 = atoi(params[2]);
	selected->y2 = atoi(params[3]);

	printf(SELECT_ZONE_OK, selected->x1, selected->y1,
		   selected->x2, selected->y2);

	if (selected->x1 > selected->x2)
		swap_int(&selected->x1, &selected->x2);

	if (selected->y1 > selected->y2)
		swap_int(&selected->y1, &selected->y2);

	img_status->selection = SELECTED;
}

void select_all(status *img_status, image *img, selected_area *selected)
{
	if (img_status->load == NOT_LOADED) {
		printf(NO_IMG);
		return;
	}

	selected->x1 = 0;
	selected->y1 = 0;
	selected->x2 = img->width;
	selected->y2 = img->height;
	img_status->selection = SELECTED_ALL;
	printf(SELECT_ALL_OK);
}
