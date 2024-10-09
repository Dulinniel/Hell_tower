#!/usr/bin/env makefile
all: build

build:
	gcc -Wall -Werror ./src/index.c -o ./bin/hell_tower

clean:
	rm -rf ./bin/*