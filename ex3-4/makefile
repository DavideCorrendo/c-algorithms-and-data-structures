# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -g

# Directories
SRC_DIR = src
TEST_DIR = tests
BIN_DIR = bin

# Include directories
INCLUDES = -I$(SRC_DIR) -I$(TEST_DIR)

# Source files
MAIN_SRCS = $(SRC_DIR)/main.c $(SRC_DIR)/graph.c $(SRC_DIR)/bfs.c $(SRC_DIR)/hashtable.c
TEST_SRCS = $(TEST_DIR)/test.c $(TEST_DIR)/unity.c $(SRC_DIR)/graph.c $(SRC_DIR)/bfs.c $(SRC_DIR)/hashtable.c

# Object files (moved to bin directory)
MAIN_OBJS = $(patsubst $(SRC_DIR)/%.c,$(BIN_DIR)/%.o,$(MAIN_SRCS))
TEST_OBJS = $(patsubst $(SRC_DIR)/%.c,$(BIN_DIR)/%.o,$(filter $(SRC_DIR)/%,$(TEST_SRCS))) \
            $(patsubst $(TEST_DIR)/%.c,$(BIN_DIR)/%.o,$(filter $(TEST_DIR)/%,$(TEST_SRCS)))

# Targets
MAIN_TARGET = $(BIN_DIR)/main_ex3-4
TEST_TARGET = $(BIN_DIR)/test_ex3-4

# Default target
all: $(BIN_DIR) $(MAIN_TARGET) $(TEST_TARGET)

# Create bin directory if it doesn't exist
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Compilation rule for object files (moving to bin directory)
$(BIN_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(BIN_DIR)/%.o: $(TEST_DIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Main executable
$(MAIN_TARGET): $(MAIN_OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Test executable
$(TEST_TARGET): $(TEST_OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Clean up
clean:
	rm -rf $(BIN_DIR)

# Phony targets
.PHONY: all clean