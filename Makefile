CC = gcc
CFLAGS = -Wall -Wextra -O2 -Iinclude
LDFLAGS = 

SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj
BIN_DIR = bin
RES_DIR = results

# Automatically include all .c files in src/
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))
TARGET = $(BIN_DIR)/benchmark

.PHONY: all demo full test clean run dirs

all: dirs $(TARGET)

dirs:
	@mkdir -p $(OBJ_DIR) $(BIN_DIR) $(RES_DIR)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
	@echo "Build successful! Executable ready at $(TARGET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Fast interactive live demonstration (for the presentation)
demo: all
	@./$(TARGET) --demo

# Comprehensive benchmark suite generating CSV files
full: all
	@./$(TARGET) --full

# Unit correctness verification tests
test: all
	@./$(TARGET) --test

# Alias for demo
run: demo

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)
	@echo "Clean completed."
