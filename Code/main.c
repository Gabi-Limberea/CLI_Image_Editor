// Copyright 2021 - 2022: Limberea Gabriela 312CA
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "outputs.h"
#include "macros.h"
#include "load_image.h"
#include "select.h"
#include "save_image.h"

comm chk_command(char *input, char **params, int *count);

int main(void)
{
	char *input = calloc(BUFSIZ, sizeof(char));
	char **params = calloc(PARAMETERS_MAX, sizeof(char *));
	comm command = NOTHING;
	status img_status = {NOT_LOADED, NOTHING_SELECTED};
	image img = {0, 0, 0, DEFAULT, {NULL}, NO_TYPE};
	selected_area selected;

	while (command != EXIT) {
		int count = 0;

		fgets(input, BUFSIZ, stdin);
		while(!strcmp(input, "\n"))
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
			break;

		case CROP:
			break;

		case APPLY:
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

	if (!strcmp(command, "LOAD"))
		return LOAD;

	if (!strcmp(command, "SELECT")) {
		if (!strcmp(params[0], "ALL"))
			return SELECT_ALL;
		else
			return SELECT;
	}

	if (!strcmp(command, "ROTATE"))
		return ROTATE;

	if (!strcmp(command, "CROP"))
		return CROP;

	if (!strcmp(command, "APPLY"))
		return APPLY;

	if (!strcmp(command, "SAVE"))
		return SAVE;

	if (!strcmp(command, "EXIT"))
		return -1; //EXIT, checker is a bitch

	return NOTHING;
}
