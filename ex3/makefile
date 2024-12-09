CC = gcc
CFLAGS = -Wall -Wextra -g -I./tests -I./src
LDFLAGS =

# Directories
SRC_DIR = src
TEST_DIR = tests
BIN_DIR = bin

# Source files
SRC_FILES = $(SRC_DIR)/main.c $(SRC_DIR)/hashtable.c $(SRC_DIR)/occurences.c
TEST_FILES = $(TEST_DIR)/test.c $(TEST_DIR)/unity.c

# Object files (in BIN_DIR)
MAIN_OBJ_FILES = $(patsubst $(SRC_DIR)/%.c,$(BIN_DIR)/%.o,$(SRC_FILES))
TEST_OBJ_FILES = $(patsubst $(TEST_DIR)/%.c,$(BIN_DIR)/%.o,$(TEST_FILES))

# Exclude main.o from test compilation
MAIN_OBJ_FOR_TEST = $(filter-out $(BIN_DIR)/main.o, $(MAIN_OBJ_FILES))

# Executable files
MAIN_EXEC = $(BIN_DIR)/program
TEST_EXEC = $(BIN_DIR)/tests

# Default target
all: $(BIN_DIR) $(MAIN_EXEC)

# Test target
test: $(BIN_DIR) $(TEST_EXEC)
	./$(TEST_EXEC)

# Create the bin directory
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Build the main program
$(MAIN_EXEC): $(MAIN_OBJ_FILES)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

# Build the test executable
$(TEST_EXEC): $(MAIN_OBJ_FOR_TEST) $(TEST_OBJ_FILES)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

# Compile source files to object files in bin directory
$(BIN_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Compile test files to object files in bin directory
$(BIN_DIR)/%.o: $(TEST_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up the build
clean:
	rm -rf $(BIN_DIR)