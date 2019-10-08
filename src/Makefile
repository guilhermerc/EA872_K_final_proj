CC=g++
CC_FLAGS=-std=c++11 -lncurses
BIN=main

GAME=game
ELEMENT=element
SCREEN=screen

RM=rm
RM_FLAGS=--force

all: $(BIN)

run: all
	./$(BIN)

$(BIN): main.cpp $(ELEMENT) $(GAME) $(SCREEN)
	$(CC) $< $(ELEMENT).o $(GAME).o $(SCREEN).o $(CC_FLAGS) -o$@

## TODO: Check if it is possible to simplify something using an array

$(ELEMENT): $(ELEMENT).cpp $(ELEMENT).hpp
	$(CC) -c $< $(CC_FLAGS) -o$@.o

$(GAME): $(GAME).cpp $(GAME).hpp element_type.hpp
	$(CC) -c $< $(CC_FLAGS) -o$@.o

$(SCREEN): screen.cpp screen.hpp
	$(CC) -c $< $(CC_FLAGS) -o$@.o

clean:
	$(RM) $(RM_FLAGS) $(BIN) $(ELEMENT).o $(GAME).o $(SCREEN).o
