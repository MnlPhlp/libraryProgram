CC		:= gcc
C_FLAGS := -Wall -Wextra

BIN		:= bin
SRC		:= src
INCLUDE	:= include

ifeq ($(OS),Windows_NT)
EXECUTABLE	:= main.exe
DEBUG := debug.exe
else
EXECUTABLE	:= main
DEBUG := debug
endif

all: $(BIN)/$(EXECUTABLE)

clean:
	-$(RM) $(BIN)/$(EXECUTABLE)

run: all
	./$(BIN)/$(EXECUTABLE)

debug:
	$(CC) $(C_FLAGS) --debug -I$(INCLUDE) -o $(BIN)/$(DEBUG) $(SRC)/*

$(BIN)/$(EXECUTABLE): $(SRC)/*
	$(CC) $(C_FLAGS) -I$(INCLUDE) $^ -o $@ 