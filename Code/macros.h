// Copyright 2021 - 2022: Limberea Gabriela 312CA
#pragma once

#define COMMAND_MAX 7
#define PARAMETERS_MAX 4
#define DEFAULT 3
#define ERROR -1
#define SUCCESS 1
#define SIZE sizeof(uint_fast8_t)
#define DEFAULT_ANGLE 90

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
	int x1, y1, x2, y2;
} selected_area;

typedef enum effects {
	INVALID_EFFECT = -1, EDGE, SHARPEN, BLUR, GAUSSIAN_BLUR
} effects;

static const double edge[DEFAULT][DEFAULT] = {{-1, -1, -1},
											  {-1, 8, -1},
											  {-1, -1, -1}};

static const double sharpen[DEFAULT][DEFAULT] = {{0, -1, 0},
												 {-1, 5, -1},
												 {0, -1, 0}};

static const double blur[DEFAULT][DEFAULT] = {{1 / 9, 1 / 9, 1 / 9},
											  {1 / 9, 1 / 9, 1 / 9},
											  {1 / 9, 1 / 9, 1 / 9}};

static const double gauss_blur[DEFAULT][DEFAULT] = {{1 / 16, 1 / 8, 1 / 16},
													{1 / 8, 1 / 4, 1 / 8},
													{1 / 16, 1 / 8, 1 / 16}};