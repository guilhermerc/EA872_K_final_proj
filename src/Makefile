CC=g++
CC_FLAGS=-std=c++11 -lncurses
BIN=main

SCREEN=screen

RM=rm
RM_FLAGS=--force

all: $(BIN)

run: all
	./$(BIN)

$(BIN): main.cpp $(SCREEN)
	$(CC) $< $(SCREEN).o $(CC_FLAGS) -o$@ 


$(SCREEN): screen.cpp screen.hpp
	$(CC) -c $< -o$@.o

clean:
	$(RM) $(RM_FLAGS) $(BIN) $(SCREEN).o
