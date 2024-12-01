# Variabili
CC = gcc
CFLAGS = -Wall -Wextra -g -I$(SRC_DIR)
SRC_DIR = src
TEST_DIR = tests
BIN_DIR = bin
UNITY_FILES = $(TEST_DIR)/unity.c

# Obiettivi
all: $(BIN_DIR)/main $(BIN_DIR)/test_distance

# Crea la cartella bin
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Compila il programma principale
$(BIN_DIR)/main: $(SRC_DIR)/main.c $(SRC_DIR)/distance.c $(SRC_DIR)/distance.h | $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $(SRC_DIR)/main.c $(SRC_DIR)/distance.c

# Compila i test
$(BIN_DIR)/test_distance: $(TEST_DIR)/test_distance.c $(SRC_DIR)/distance.c $(SRC_DIR)/distance.h $(UNITY_FILES) | $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $(TEST_DIR)/test_distance.c $(SRC_DIR)/distance.c $(UNITY_FILES)

# Pulisce i file compilati
clean:
	rm -rf $(BIN_DIR)

# Esegue i test
test: $(BIN_DIR)/test_distance
	$(BIN_DIR)/test_distance
