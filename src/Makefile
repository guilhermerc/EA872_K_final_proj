CC=g++
CC_FLAGS=-std=c++11 -lncurses
BIN=main

ELEMENT=element
SCREEN=screen

RM=rm
RM_FLAGS=--force

all: $(BIN)

run: all
	./$(BIN)

$(BIN): main.cpp $(ELEMENT) $(SCREEN)
	$(CC) $< $(ELEMENT).o $(SCREEN).o $(CC_FLAGS) -o$@


$(ELEMENT): $(ELEMENT).cpp $(ELEMENT).hpp
	$(CC) -c $< $(CC_FLAGS) -o$@.o

$(SCREEN): screen.cpp screen.hpp
	$(CC) -c $< $(CC_FLAGS) -o$@.o

clean:
	$(RM) $(RM_FLAGS) $(BIN) $(ELEMENT).o $(SCREEN).o
