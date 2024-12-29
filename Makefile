#!/usr/bin/env makefile

# Directories
BUILD_DIR = ./build
SRC_DIR = ./src
OBJECT_DIR = $(BUILD_DIR)/objs
BINARY_DIR = $(BUILD_DIR)/bin
BUILD_TEST_DIR = $(BUILD_DIR)/test

# Binary and Entry File
BINARY = $(BINARY_DIR)/hell_tower
ENTRY_FILE = index.c
ENTRY_POINT = $(SRC_DIR)/$(ENTRY_FILE)

# Compiler and Flags
CC = gcc
CFLAGS = -Wall -Werror -I$(SRC_DIR)
LDFLAGS = -lSDL2main -lSDL2

# Sources and Objects
C_SOURCES = $(shell find $(SRC_DIR) -name '*.c')
C_OBJECTS = $(patsubst $(SRC_DIR)/%.c, $(OBJECT_DIR)/%.o, $(C_SOURCES))

# Targets
.PHONY: all build clean execute

all: build

build: $(BINARY)

$(BINARY): $(C_OBJECTS) | $(BINARY_DIR)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

$(OBJECT_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJECT_DIR)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

$(BINARY_DIR):
	@mkdir -p $@

$(OBJECT_DIR):
	@mkdir -p $@

clean:
	rm -rf $(BUILD_DIR)

execute: $(BINARY)
	$(BINARY)

$(BUILD_DIR):
	@mkdir -p $@
