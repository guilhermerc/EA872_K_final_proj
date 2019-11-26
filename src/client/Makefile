CC = g++
CC_FLAGS = -std=c++11 -lncurses -lpthread
BIN = main
COMMON_DIR = ../common
INCLUDE_DIR = ../include

# Classes
ELEMENT = $(COMMON_DIR)/element
GAME = $(COMMON_DIR)/game
KEYBOARD = $(COMMON_DIR)/keyboard
SCREEN = $(COMMON_DIR)/screen

# Headers without corresponding Classes
ELEMENT_TYPE_HPP = $(INCLUDE_DIR)/element_type.hpp

# Functions
BOMB_EXPLOSION_FUNC = $(COMMON_DIR)/bomb_explosion_func
GAME_RECV_FUNC = game_recv_func
KEYBOARD_FUNC = $(COMMON_DIR)/keyboard_func

RM = rm
RM_FLAGS = --force

all: $(BIN)

run: all
	./$(BIN)

$(BIN): main.cpp $(BOMB_EXPLOSION_FUNC) $(ELEMENT) $(GAME) $(GAME_RECV_FUNC) $(KEYBOARD_FUNC) $(KEYBOARD) $(SCREEN) $(ELEMENT_TYPE_HPP)
	$(CC) $< $(BOMB_EXPLOSION_FUNC).o $(ELEMENT).o $(GAME).o $(GAME_RECV_FUNC).o $(KEYBOARD_FUNC).o $(KEYBOARD).o $(SCREEN).o $(CC_FLAGS) -I$(INCLUDE_DIR) -o$@

## TODO: Check if it is possible to simplify something using an array

$(BOMB_EXPLOSION_FUNC): $(BOMB_EXPLOSION_FUNC).cpp ## $(BOMB_EXPLOSION_FUNC).hpp
	$(CC) -c $< $(CC_FLAGS) -I$(INCLUDE_DIR) -o$@.o

$(ELEMENT): $(ELEMENT).cpp ## $(ELEMENT).hpp
	$(CC) -c $< $(CC_FLAGS) -I$(INCLUDE_DIR) -o$@.o

$(GAME): $(GAME).cpp ## $(GAME).hpp
	$(CC) -c $< $(CC_FLAGS) -I$(INCLUDE_DIR) -o$@.o

$(GAME_RECV_FUNC): $(GAME_RECV_FUNC).cpp ## $(GAME_RECV_FUNC).hpp
	$(CC) -c $< $(CC_FLAGS) -I$(INCLUDE_DIR) -o$@.o

$(KEYBOARD_FUNC): $(KEYBOARD_FUNC).cpp ## $(KEYBOARD_FUNC).hpp
	$(CC) -c $< $(CC_FLAGS) -I$(INCLUDE_DIR) -o$@.o

$(KEYBOARD): $(KEYBOARD).cpp ## $(KEYBOARD).hpp
	$(CC) -c $< $(CC_FLAGS) -I$(INCLUDE_DIR) -o$@.o

$(SCREEN): $(SCREEN).cpp ## $(SCREEN).hpp
	$(CC) -c $< $(CC_FLAGS) -I$(INCLUDE_DIR) -o$@.o

clean:
	$(RM) $(RM_FLAGS) $(BIN) $(BOMB_EXPLOSION_FUNC).o $(ELEMENT).o $(GAME).o $(GAME_RECV_FUNC).o $(KEYBOARD_FUNC).o $(KEYBOARD).o $(SCREEN).o
