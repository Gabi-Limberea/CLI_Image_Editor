// Copyright 2021 - 2022: Limberea Gabriela 312CA
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <math.h>

#include "main_headers.h"

comm chk_command(char *input, char **params, int *count);

int main(void)
{
	char *input = calloc(BUFSIZ, sizeof(char));
	char **params = calloc(PARAMETERS_MAX, sizeof(char *));
	comm command = NOTHING;
	status img_status = {NOT_LOADED, NOTHING_SELECTED};
	image img = {0, 0, 0, DEFAULT, {NULL}, NO_TYPE};
	selected_area selected = {0, 0, 0, 0};

	while (command != EXIT) {
		int count = 0;

		fgets(input, BUFSIZ, stdin);
		while (!strcmp(input, "\n"))
			fgets(input, BUFSIZ, stdin);

		command = chk_command(input, params, &count);

		switch (command) {
		case LOAD:
			printf(load_img(&img_status, params[0], &img), params[0]);
			break;

		case SELECT:
			select_area(&img_status, params, count, &img, &selected);
			break;

		case SELECT_ALL:
			select_all(&img_status, &img, &selected);
			break;

		case ROTATE:
			rotate(&img_status, params[0], &img, &selected);
			break;

		case CROP:
			crop(&img, &selected, &img_status);
			break;

		case APPLY:
			apply(&img, img_status, params[0], selected);
			break;

		case SAVE:
			save_img(img_status, params, img, count);
			break;

		case EXIT:
			if (img_status.load == NOT_LOADED)
				printf(NO_IMG);
			else
				reset(&img, &img_status);
			break;

		default:
			printf(INVALID);
			break;
		}
	}

	free(params);
	free(input);
	return 0;
}

comm chk_command(char *input, char **params, int *count)
{
	char *dummy = strchr(input, '\n');
	char *command = NULL;

	if (dummy)
		*dummy = '\0';

	dummy = strtok(input, " ");
	while (dummy && *count < PARAMETERS_MAX) {
		if (!command) {
			command = dummy;
		} else {
			params[(*count)] = dummy;
			(*count)++;
		}

		dummy = strtok(NULL, " ");
	}

	if (!strcmp(command, "LOAD") && *count != 0)
		return LOAD;

	if (!strcmp(command, "SELECT") && *count != 0) {
		if (!strcmp(params[0], "ALL"))
			return SELECT_ALL;
		else
			return SELECT;
	}

	if (!strcmp(command, "ROTATE") && *count != 0)
		return ROTATE;

	if (!strcmp(command, "CROP") && *count == 0)
		return CROP;

	if (!strcmp(command, "APPLY") && *count != 0)
		return APPLY;

	if (!strcmp(command, "SAVE") && *count != 0)
		return SAVE;

	if (!strcmp(command, "EXIT"))
		return -1; //EXIT, checker is a bitch

	return NOTHING;
}
