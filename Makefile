CC=gcc
CFLAGS=-Wall -Wextra -O2 -Iinclude
SRC_DIR=src
RES_DIR=results
SRCS=$(wildcard $(SRC_DIR)/*.c)
TARGET=benchmark

.PHONY: all demo full test clean run dirs random sorted reverse nearly duplicates

all: dirs $(TARGET)

dirs:
	@mkdir -p $(RES_DIR)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $@ $^
	@echo "Build successful! Executable ready at ./$(TARGET)"

# Demo rapide
demo: all
	@./$(TARGET) --demo random

# Tests unitaires
test: all
	@./$(TARGET) --test

# Benchmarks complets par type de donnees
random: all
	@./$(TARGET) --full random

sorted: all
	@./$(TARGET) --full sorted

reverse: all
	@./$(TARGET) --full reverse

nearly: all
	@./$(TARGET) --full nearly

duplicates: all
	@./$(TARGET) --full duplicates

# Benchmark de tous les types
full: all
	@./$(TARGET) --full all

run: demo

clean:
	rm -f $(TARGET)
	@echo "Clean completed."

