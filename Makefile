CC = gcc
CFLAGS = -Wall -Wextra
SRC_DIR = src
BIN_DIR = ./bin

.PHONY: all compile-cli compile-main clean run-cli

all: compile-main compile-cli

compile-main: $(BIN_DIR)/main

$(BIN_DIR)/main: $(SRC_DIR)/main.c $(SRC_DIR)/storage.c $(SRC_DIR)/storage.h $(SRC_DIR)/controller.h $(SRC_DIR)/controller.c
	$(CC) $(CFLAGS) -o $@ $(SRC_DIR)/main.c $(SRC_DIR)/utils.c $(SRC_DIR)/storage.c $(SRC_DIR)/controller.c

compile-cli: $(BIN_DIR)/cli

$(BIN_DIR)/cli: $(SRC_DIR)/cli.c $(SRC_DIR)/utils.c $(SRC_DIR)/utils.h $(SRC_DIR)/storage.c $(SRC_DIR)/storage.h $(SRC_DIR)/controller.h $(SRC_DIR)/controller.c
	$(CC) $(CFLAGS) -o $@ $(SRC_DIR)/cli.c $(SRC_DIR)/utils.c $(SRC_DIR)/storage.c $(SRC_DIR)/controller.c

clean:
	rm -f $(BIN_DIR)/main

run-cli: compile-cli
	$(BIN_DIR)/cli $(cmd)

