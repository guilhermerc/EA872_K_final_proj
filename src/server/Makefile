CC=g++
CC_FLAGS=-std=c++11 -lncurses -lpthread
BIN=main

# Classes
ACTION=action
ELEMENT=element
GAME=game
KEYBOARD=keyboard
SCREEN=screen

# Headers without corresponding Classes
ACTION_TYPE_HPP=action_type.hpp
ELEMENT_TYPE_HPP=element_type.hpp

# Functions
BOMB_EXPLOSION_FUNC=bomb_explosion_func
KEYBOARD_FUNC=keyboard_func

RM=rm
RM_FLAGS=--force

all: $(BIN)

run: all
	./$(BIN)

$(BIN): main.cpp $(ACTION) $(BOMB_EXPLOSION_FUNC) $(ELEMENT) $(GAME) $(KEYBOARD_FUNC) $(KEYBOARD) $(SCREEN) $(ACTION_TYPE_HPP) $(ELEMENT_TYPE_HPP)
	$(CC) $< $(ACTION).o $(BOMB_EXPLOSION_FUNC).o $(ELEMENT).o $(GAME).o $(KEYBOARD_FUNC).o $(KEYBOARD).o $(SCREEN).o $(CC_FLAGS) -o$@

## TODO: Check if it is possible to simplify something using an array

$(ACTION): $(ACTION).cpp $(ACTION).hpp
	$(CC) -c $< $(CC_FLAGS) -o$@.o

$(BOMB_EXPLOSION_FUNC): $(BOMB_EXPLOSION_FUNC).cpp $(BOMB_EXPLOSION_FUNC).hpp
	$(CC) -c $< $(CC_FLAGS) -o$@.o

$(ELEMENT): $(ELEMENT).cpp $(ELEMENT).hpp
	$(CC) -c $< $(CC_FLAGS) -o$@.o

$(GAME): $(GAME).cpp $(GAME).hpp
	$(CC) -c $< $(CC_FLAGS) -o$@.o

$(KEYBOARD_FUNC): $(KEYBOARD_FUNC).cpp $(KEYBOARD_FUNC).hpp
	$(CC) -c $< $(CC_FLAGS) -o$@.o

$(KEYBOARD): $(KEYBOARD).cpp $(KEYBOARD).hpp
	$(CC) -c $< $(CC_FLAGS) -o$@.o

$(SCREEN): $(SCREEN).cpp $(SCREEN).hpp
	$(CC) -c $< $(CC_FLAGS) -o$@.o

clean:
	$(RM) $(RM_FLAGS) $(BIN) $(ACTION).o $(BOMB_EXPLOSION_FUNC).o $(ELEMENT).o $(GAME).o $(KEYBOARD_FUNC).o $(KEYBOARD).o $(SCREEN).o
