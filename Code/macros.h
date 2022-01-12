// Copyright 2021 - 2022: Limberea Gabriela 312CA
#pragma once

#define COMMAND_MAX 7
#define PARAMETERS_MAX 4
#define DEFAULT 3
#define ERROR -1
#define SUCCESS 1
#define SIZE sizeof(uint_fast8_t)

typedef enum comm {
	EXIT = -1, NOTHING, LOAD, SELECT, SELECT_ALL, ROTATE, CROP, APPLY, SAVE
} comm;

typedef enum magic_words {
	NO_TYPE = -1, P1, P2, P3, P4, P5, P6
} magic;

typedef enum load_status {
	NOT_LOADED, LOADED
} load_status;

typedef enum selection_status {
	INVALID_SELECT = -1, NOTHING_SELECTED, SELECTED, SELECTED_ALL
} selection_status;

typedef struct img_status {
	load_status load;
	selection_status selection;
} status;

typedef struct color_channels {
	uint_fast8_t **bw;
	uint_fast8_t **gray;
	uint_fast8_t **red, **green, **blue;
} channels;

typedef struct image {
	int width, height, max_value, start_line;
	channels pixels;
	magic type;
} image;

typedef struct selected_area {
	uint_fast8_t x1, y1, x2, y2;
} selected_area;
