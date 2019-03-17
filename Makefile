CC		:= gcc
C_FLAGS := -Wall -Wextra

BIN		:= bin
SRC		:= src
INCLUDE	:= include

ifeq ($(OS),Windows_NT)
EXECUTABLE	:= main.exe
DEBUG := debug.exe
MAKE_BIN := md $(BIN)
else
EXECUTABLE	:= main
DEBUG := debug
MAKE_BIN := mkdir -p $(BIN)
endif

all: $(BIN)/$(EXECUTABLE)

clean:
	-$(RM) $(BIN)/$(EXECUTABLE)

run: all
	./$(BIN)/$(EXECUTABLE)

$(BIN)/$(EXECUTABLE): $(SRC)/*
	$(MAKE_BIN)
	$(CC) $(C_FLAGS) -I$(INCLUDE) $^ -o $@ 