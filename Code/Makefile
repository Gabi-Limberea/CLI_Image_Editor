# Copyright 2021 - 2022: Limberea Gabriela 312CA
CC=gcc
CCFLAGS=-Wall -Wextra -g

HEADERS= load_image.c select.c save_image.c bit_manipulation.c

build:
	$(CC) $(CCFLAGS) main.c $(HEADERS) -o image_editor -ggdb3

run:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes \
	--verbose --log-file=valgrind-out.txt ./image_editor

clean:
	rm -f image_editor *.txt *.out

pack:
	make clean
	zip -FSr 312CA_GabrielaLimberea_Tema3.zip *.c *.h README Makefile

.PHONY: clean run pack
