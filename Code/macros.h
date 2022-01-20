// Copyright 2021 - 2022: Limberea Gabriela 312CA
#pragma once

#define NO_IMG "No image loaded\n"
#define LOAD_OK "Loaded %s\n"
#define LOAD_FAIL "Failed to load %s\n"
#define SELECT_ZONE_OK "Selected %d %d %d %d\n"
#define SELECT_ZONE_FAIL "Invalid set of coordinates\n"
#define SELECT_ALL_OK "Selected ALL\n"
#define ROTATE_OK "Rotated %s\n"
#define ROTATE_FAIL_SQUARE "The selection must be square\n"
#define ROTATE_FAIL_ANGlE "Unsupported rotation angle\n"
#define CROP_OK "Image cropped\n"
#define APPLY_OK "APPLY %s done\n"
#define APPLY_FAIL_GRAYSCALE "Easy, Charlie Chaplin\n"
#define APPLY_FAIL_PARAMETER "APPLY parameter invalid\n"
#define SAVE_OK "Saved %s\n"
#define INVALID "Invalid command\n"
#define ERROR_MESSAGE "Something went wrong, aborting\n"

#define COMMAND_MAX 7
#define PARAMETERS_MAX 4
#define DEFAULT 3
#define ERROR -1
#define SUCCESS 1
#define SIZE sizeof(double)
#define SIZE_PTR sizeof(double *)
#define SIZE_CHAR sizeof(uint_fast8_t)
#define SIZE_PTR_CHAR sizeof(uint_fast8_t *)
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
	double **gray;
	double **red, **green, **blue;
} channels;

typedef struct image {
	int width, height, max_value, start_line;
	channels pixels;
	magic type;
} image;

typedef struct selected_area {
	int x1, y1, x2, y2;
} selected_area;

typedef enum filters {
	INVALID_FILTER = -1, EDGE, SHARPEN, BLUR, GAUSSIAN_BLUR
} filters;

static const double edge[DEFAULT][DEFAULT] = {
	{-1.0, -1.0, -1.0},
	{-1.0, 8.0, -1.0},
	{-1.0, -1.0, -1.0}};

static const double sharpen[DEFAULT][DEFAULT] = {
	{0.0, -1.0, 0.0},
	{-1.0, 5.0, -1.0},
	{0.0, -1.0, 0.0}};

static const double blur[DEFAULT][DEFAULT] = {
	{1.0 / 9, 1.0 / 9, 1.0 / 9},
	{1.0 / 9, 1.0 / 9, 1.0 / 9},
	{1.0 / 9, 1.0 / 9, 1.0 / 9}};

static const double gauss_blur[DEFAULT][DEFAULT] = {
	{1.0 / 16, 1.0 / 8, 1.0 / 16},
	{1.0 / 8, 1.0 / 4, 1.0 / 8},
	{1.0 / 16, 1.0 / 8, 1.0 / 16}};
