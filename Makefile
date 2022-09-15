CXX		  := g++
CXX_FLAGS := -Wall -std=c++17 -ggdb


INCLUDE	:= include
SRC		:= src
LIB		:= lib

LIBRARIES	:= -lsfml-graphics -lsfml-window -lsfml-system
EXECUTABLE	:= main

MKDIR_P = mkdir -p

.PHONY: directories

all: directories $(EXECUTABLE)

run: clean all
	clear
	$(EXECUTABLE)

$(EXECUTABLE): $(SRC)/*.cpp main.cpp
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE) -L$(LIB) $^ -o $@ $(LIBRARIES)


