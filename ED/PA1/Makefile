CC = gcc
CFLAGS = --std=gnu11 -Wall -no-pie
SRC_DIR = src
INCLUDE_DIR = include
OBJ_DIR = obj
BIN_DIR = bin
EXEC = $(BIN_DIR)/pa1.out

all: $(EXEC)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(OBJ_DIR)/PA1.o: $(SRC_DIR)/PA1.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/PA1.c -o $(OBJ_DIR)/PA1.o

$(EXEC): $(OBJ_DIR)/PA1.o | $(BIN_DIR)
	$(CC) $(CFLAGS) $(OBJ_DIR)/PA1.o -o $(EXEC)

clean:
	rm -rf $(OBJ_DIR)/*.o $(EXEC)