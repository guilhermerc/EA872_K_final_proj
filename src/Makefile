CC=g++
CC_FLAGS=-std=c++11 -lncurses -lpthread
BIN=main

ELEMENT=element
GAME=game
KEYBOARD_FUNC=keyboard_func
KEYBOARD=keyboard
SCREEN=screen

RM=rm
RM_FLAGS=--force

all: $(BIN)

run: all
	./$(BIN)

$(BIN): main.cpp $(ELEMENT) $(GAME) $(KEYBOARD_FUNC) $(KEYBOARD) $(SCREEN)
	$(CC) $< $(ELEMENT).o $(GAME).o $(KEYBOARD_FUNC).o $(KEYBOARD).o $(SCREEN).o $(CC_FLAGS) -o$@

## TODO: Check if it is possible to simplify something using an array

$(ELEMENT): $(ELEMENT).cpp $(ELEMENT).hpp
	$(CC) -c $< $(CC_FLAGS) -o$@.o

$(GAME): $(GAME).cpp $(GAME).hpp element_type.hpp
	$(CC) -c $< $(CC_FLAGS) -o$@.o

$(KEYBOARD_FUNC): $(KEYBOARD_FUNC).cpp $(KEYBOARD_FUNC).hpp
	$(CC) -c $< $(CC_FLAGS) -o$@.o

$(KEYBOARD): 	$(KEYBOARD).cpp $(KEYBOARD).hpp
	$(CC) -c $< $(CC_FLAGS) -o$@.o

$(SCREEN): screen.cpp screen.hpp
	$(CC) -c $< $(CC_FLAGS) -o$@.o

clean:
	$(RM) $(RM_FLAGS) $(BIN) $(ELEMENT).o $(GAME).o $(KEYBOARD_FUNC).o $(KEYBOARD).o $(SCREEN).o
