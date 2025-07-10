CC = g++
CFLAGS = -std=c++11 -Wall
SRC_DIR = src
INCLUDE_DIR = include
OBJ_DIR = obj
BIN_DIR = bin
EXEC = $(BIN_DIR)/pa2.out

all: $(BIN_DIR) $(OBJ_DIR) $(EXEC)

$(OBJ_DIR)/graph.o: $(SRC_DIR)/graph.cpp $(INCLUDE_DIR)/graph.hpp
	$(CC) $(CFLAGS) -c $(SRC_DIR)/graph.cpp -I$(INCLUDE_DIR) -o $(OBJ_DIR)/graph.o
$(OBJ_DIR)/listaadjacencia.o: $(SRC_DIR)/listaadjacencia.cpp $(INCLUDE_DIR)/listaadjacencia.hpp
	$(CC) $(CFLAGS) -c $(SRC_DIR)/listaadjacencia.cpp -I$(INCLUDE_DIR) -o $(OBJ_DIR)/listaadjacencia.o
$(OBJ_DIR)/listainteiros.o: $(SRC_DIR)/listainteiros.cpp $(INCLUDE_DIR)/listainteiros.hpp
	$(CC) $(CFLAGS) -c $(SRC_DIR)/listainteiros.cpp -I$(INCLUDE_DIR) -o $(OBJ_DIR)/listainteiros.o
$(OBJ_DIR)/main.o: $(SRC_DIR)/main.cpp
	$(CC) $(CFLAGS) -c $(SRC_DIR)/main.cpp -I$(INCLUDE_DIR) -o $(OBJ_DIR)/main.o
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)
$(BIN_DIR):
	mkdir -p $(BIN_DIR)
$(EXEC): $(OBJ_DIR)/main.o $(OBJ_DIR)/listainteiros.o $(OBJ_DIR)/listaadjacencia.o $(OBJ_DIR)/graph.o
	$(CC) $(CFLAGS) -o $(EXEC) $^

clean:
	rm -rf $(OBJ_DIR)/*.o $(EXEC)
