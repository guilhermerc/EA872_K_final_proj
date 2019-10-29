CC=g++
CC_FLAGS=-std=c++11 -lncurses -lpthread
BIN=main

# Classes
KEYBOARD=keyboard
SCREEN=screen

# Functions
KEYBOARD_FUNC=keyboard_func

RM=rm
RM_FLAGS=--force

all: $(BIN)

run: all
	./$(BIN)

$(BIN): main.cpp $(KEYBOARD_FUNC) $(KEYBOARD) $(SCREEN)
	$(CC) $< $(KEYBOARD_FUNC).o $(KEYBOARD).o $(SCREEN).o $(CC_FLAGS) -o$@

## TODO: Check if it is possible to simplify something using an array

$(KEYBOARD_FUNC): $(KEYBOARD_FUNC).cpp $(KEYBOARD_FUNC).hpp
	$(CC) -c $< $(CC_FLAGS) -o$@.o

$(KEYBOARD): $(KEYBOARD).cpp $(KEYBOARD).hpp
	$(CC) -c $< $(CC_FLAGS) -o$@.o

$(SCREEN): $(SCREEN).cpp $(SCREEN).hpp
	$(CC) -c $< $(CC_FLAGS) -o$@.o

clean:
	$(RM) $(RM_FLAGS) $(BIN) $(KEYBOARD_FUNC).o $(KEYBOARD).o $(SCREEN).o
