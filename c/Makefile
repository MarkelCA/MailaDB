CC = gcc
CFLAGS = -Wall -Wextra
SRC_DIR = src
BIN_DIR = ./bin

all: compile run

compile: $(BIN_DIR)/main

$(BIN_DIR)/main: $(SRC_DIR)/main.c $(SRC_DIR)/utils.c $(SRC_DIR)/utils.h
	$(CC) $(CFLAGS) -o $@ $(SRC_DIR)/main.c $(SRC_DIR)/utils.c

run:
	$(BIN_DIR)/main

clean:
	rm -f $(BIN_DIR)/main
