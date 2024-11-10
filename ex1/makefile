CC = gcc
CFLAGS = -Wall -Wextra -g
LDFLAGS = -lm

# Directories
BIN_DIR = bin
SRC_DIR = src
TEST_DIR = tests

# Target executables
TARGET = $(BIN_DIR)/sort_program
TEST_TARGET = $(BIN_DIR)/run_tests

# Source files
SRCS = $(SRC_DIR)/main.c $(SRC_DIR)/sort.c
TEST_SRCS = $(TEST_DIR)/sortTest.c $(SRC_DIR)/sort.c
UNITY_SRCS = $(TEST_DIR)/unity.c

# Object files
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(BIN_DIR)/%.o)
TEST_OBJS = $(TEST_SRCS:$(SRC_DIR)/%.c=$(BIN_DIR)/%.o)
TEST_OBJS := $(TEST_OBJS:$(TEST_DIR)/%.c=$(BIN_DIR)/%.o)
UNITY_OBJ = $(UNITY_SRCS:$(TEST_DIR)/%.c=$(BIN_DIR)/%.o)

# Header files
INCLUDES = -I$(SRC_DIR) -I$(TEST_DIR)

.PHONY: all clean test directories

all: directories $(TARGET)

# Create bin directory
directories:
	@mkdir -p $(BIN_DIR)

# Main program
$(TARGET): $(OBJS)
	$(CC) $^ -o $@ $(LDFLAGS)

# Test program
$(TEST_TARGET): $(TEST_OBJS) $(UNITY_OBJ)
	$(CC) $^ -o $@ $(LDFLAGS)

# Compile source files
$(BIN_DIR)/%.o: $(SRC_DIR)/%.c | directories
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Compile test files
$(BIN_DIR)/%.o: $(TEST_DIR)/%.c | directories
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Build and run tests
test: directories $(TEST_TARGET)
	./$(TEST_TARGET)

# Clean build files
clean:
	rm -rf $(BIN_DIR)
