# Compiler
CC := gcc

# Compiler flags
CFLAGS := -std=c99 -Wall -Wextra -I/usr/include/libdrm

# Library directories
LDFLAGS := 

# Libraries
LIBS := -ldrm

# Source files directory
SRC_DIR := ./src

# Binary files directory
BIN_DIR := ./bin

# Source files
SRCS := $(wildcard $(SRC_DIR)/*.c)

# Object files
OBJS := $(patsubst $(SRC_DIR)/%.c, $(BIN_DIR)/%.o, $(SRCS))

# Executable name
TARGET := $(BIN_DIR)/iovinfo

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) $^ -o $@ $(LIBS)

$(BIN_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BIN_DIR)/*

.PHONY: all clean
