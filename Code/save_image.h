// Copyright 2021 - 2022: Limberea Gabriela 312CA

#include "macros.h"
#include "bit_manipulation.h"

#ifndef __save__image__
#define __save__image__

// Main function for the save command.
// Check validity of command and decide how to save the file
void save_img(status img_status, char **params, image img, int count);

// Save image as an ascii file
int save_ascii(char *filename, image img);

// Save image as a binary file
int save_binary(char *filename, image img);

#endif
