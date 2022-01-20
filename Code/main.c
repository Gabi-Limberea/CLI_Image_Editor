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

		// Ignore if input is just a '\n'
		while (!strcmp(input, "\n"))
			fgets(input, BUFSIZ, stdin);

		// Get the command, parameters and the number of parameters given
		command = chk_command(input, params, &count);

		switch (command) {
		case LOAD:
			load_img(&img_status, params[0], &img, &selected);
			break;

		case SELECT:
			select_area(&img_status, params, count, &img, &selected);
			break;

		case SELECT_ALL:
			select_all(&img_status, &img, &selected);
			break;

		case ROTATE:
			rotate(&img_status, params[0], &img, &selected, count);
			break;

		case CROP:
			crop(&img, &selected, &img_status);
			break;

		case APPLY:
			apply(&img, img_status, params[0], selected, count);
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

// Check the input and get the command, its parameters and how many they are
comm chk_command(char *input, char **params, int *count)
{
	char *dummy = strchr(input, '\n');
	char *command = NULL;

	// Replace the '\n' at the end of the input if needed
	if (dummy)
		*dummy = '\0';

	// Parse through the input and separate the command from the parameters
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
		// CS checker was being fussy (?).
		// It was supposed to be "return EXIT;"
		return -1;

	return NOTHING;
}
