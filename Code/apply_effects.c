// Copyright 2021 - 2022: Limberea Gabriela 312CA
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "apply_effects.h"

effects chk_effect(char *param)
{
	if (!strcmp(param, "EDGE"))
		return EDGE;

	if (!strcmp(param, "SHARPEN"))
		return SHARPEN;

	if (!strcmp(param, "BLUR"))
		return BLUR;

	if (!strcmp(param, "GAUSSIAN_BLUR"))
		return GAUSSIAN_BLUR;

	return INVALID_EFFECT;
}

void apply(image *img, status img_status, char *param, selected_area selected)
{
	if (img_status.load == NOT_LOADED) {
		printf(NO_IMG);
		return;
	}

	if (img->type != P3 && img->type != P6) {
		printf(APPLY_FAIL_GRAYSCALE);
		return;
	}

	effects effect = chk_effect(param);

	if (effect == INVALID_EFFECT) {
		printf(APPLY_FAIL_PARAMETER);
		return;
	}

	switch (effect) {
	case EDGE:
		break;
	case SHARPEN:
		break;
	case BLUR:
		break;
	case GAUSSIAN_BLUR:
		break;
	default:
		return;
	}
}