# Always build target 'all' by default
.DEFAULT_GOAL := all

# Compiler and flags
CC = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -Wpedantic -Wformat-security -Wconversion -Werror 
#CXXFLAGS = -std=c++11 -O3 -Wall

# Folders
INCLUDE_FOLDER = ./include/
OBJ_FOLDER = ./obj/
SRC_FOLDER = ./src/

TARGET = tp3.out
SRC = $(wildcard $(SRC_FOLDER)*.cpp)
OBJ = $(patsubst $(SRC_FOLDER)%.cpp, $(OBJ_FOLDER)%.o, $(SRC))

# Compile each .cpp -> .o
$(OBJ_FOLDER)%.o: $(SRC_FOLDER)%.cpp | $(OBJ_FOLDER)
	$(CC) $(CXXFLAGS) -c $< -o $@ -I$(INCLUDE_FOLDER)

# Link all object files into final executable
all: $(OBJ)
	$(CC) $(CXXFLAGS) -o $(TARGET) $(OBJ)

# Ensure obj folder exists
$(OBJ_FOLDER):
	mkdir -p $(OBJ_FOLDER)

# Clean compiled files
clean:
	@rm -rf $(OBJ_FOLDER)* $(TARGET)