CC=g++
CC_FLAGS=-std=c++11 -lncurses -lpthread
BIN=main

# Classes
ACTION=action
ELEMENT=element
GAME=game
SCREEN=screen

# Headers without corresponding Classes
ACTION_TYPE_HPP=action_type.hpp
ELEMENT_TYPE_HPP=element_type.hpp

# Functions
BOMB_EXPLOSION_FUNC=bomb_explosion_func

RM=rm
RM_FLAGS=--force

all: $(BIN)

run: all
	./$(BIN)

$(BIN): main.cpp $(ACTION) $(BOMB_EXPLOSION_FUNC) $(ELEMENT) $(GAME) $(SCREEN) $(ACTION_TYPE_HPP) $(ELEMENT_TYPE_HPP)
	$(CC) $< $(ACTION).o $(BOMB_EXPLOSION_FUNC).o $(ELEMENT).o $(GAME).o $(SCREEN).o $(CC_FLAGS) -o$@

## TODO: Check if it is possible to simplify something using an array

$(ACTION): $(ACTION).cpp $(ACTION).hpp
	$(CC) -c $< $(CC_FLAGS) -o$@.o

$(BOMB_EXPLOSION_FUNC): $(BOMB_EXPLOSION_FUNC).cpp $(BOMB_EXPLOSION_FUNC).hpp
	$(CC) -c $< $(CC_FLAGS) -o$@.o

$(ELEMENT): $(ELEMENT).cpp $(ELEMENT).hpp
	$(CC) -c $< $(CC_FLAGS) -o$@.o

$(GAME): $(GAME).cpp $(GAME).hpp
	$(CC) -c $< $(CC_FLAGS) -o$@.o

$(SCREEN): $(SCREEN).cpp $(SCREEN).hpp
	$(CC) -c $< $(CC_FLAGS) -o$@.o

clean:
	$(RM) $(RM_FLAGS) $(BIN) $(ACTION).o $(BOMB_EXPLOSION_FUNC).o $(ELEMENT).o $(GAME).o $(SCREEN).o
