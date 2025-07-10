# Compiler and flags
CC = g++
CXXFLAGS = -std=c++11 -g -Wall

# Folders
INCLUDE_FOLDER = ./include/
BIN_FOLDER = ./bin/
OBJ_FOLDER = ./obj/
SRC_FOLDER = ./src/

# Target and sources
TARGET = pa4.out
SRC = $(wildcard $(SRC_FOLDER)*.cpp)
OBJ = $(patsubst $(SRC_FOLDER)%.cpp, $(OBJ_FOLDER)%.o, $(SRC))

# Object compilation
$(OBJ_FOLDER)%.o: $(SRC_FOLDER)%.cpp
	@mkdir -p $(OBJ_FOLDER)
	$(CC) $(CXXFLAGS) -c $< -o $@ -I$(INCLUDE_FOLDER)

# Link everything
all: $(OBJ)
	@mkdir -p $(BIN_FOLDER)
	$(CC) $(CXXFLAGS) -o $(BIN_FOLDER)$(TARGET) $(OBJ)

# Clean
clean:
	@rm -rf $(OBJ_FOLDER)* $(BIN_FOLDER)*

