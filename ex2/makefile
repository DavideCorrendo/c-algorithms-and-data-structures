# Variabili
CC = gcc
CFLAGS = -Wall -Wextra -g -I$(SRC_DIR)
SRC_DIR = src
TEST_DIR = tests
BIN_DIR = bin
UNITY_FILES = $(TEST_DIR)/unity.c

all: $(BIN_DIR)/main_ex2 $(BIN_DIR)/test_ex2

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(BIN_DIR)/main_ex2: $(SRC_DIR)/main.c $(SRC_DIR)/distance.c $(SRC_DIR)/distance.h | $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $(SRC_DIR)/main.c $(SRC_DIR)/distance.c

$(BIN_DIR)/test_ex2: $(TEST_DIR)/test_distance.c $(SRC_DIR)/distance.c $(SRC_DIR)/distance.h $(UNITY_FILES) | $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $(TEST_DIR)/test_distance.c $(SRC_DIR)/distance.c $(UNITY_FILES)

clean:
	rm -rf $(BIN_DIR)

test: $(BIN_DIR)/test_distance
	$(BIN_DIR)/test_distance
