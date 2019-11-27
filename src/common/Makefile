# VARIABLES
##########################################################################
CC = 					g++
CC_FLAGS = 				-std=c++11 -lncurses -lpthread

RM = 					rm
RM_FLAGS = 				--force

COMMON_DIR = 			../common
INCLUDE_DIR = 			../../include
##########################################################################

# COMMON CLASSES CPP
##########################################################################
ACTION 	=				action
ELEMENT =				element
GAME 	= 				game
KEYBOARD =				keyboard
SCREEN =				screen
##########################################################################

# COMMON HEADERS NONASSOCIATED WITH CLASSES
##########################################################################
ACTION_TYPE_HPP = 		$(INCLUDE_DIR)/action_type.hpp
ELEMENT_TYPE_HPP = 		$(INCLUDE_DIR)/element_type.hpp
##########################################################################

# COMMON FUNCTIONS
##########################################################################
BOMB_EXPLOSION_FUNC = 	bomb_explosion_func
KEYBOARD_FUNC = 		keyboard_func
##########################################################################

# RULES
##########################################################################
common-all: $(ACTION) $(ELEMENT) $(GAME) $(KEYBOARD) $(SCREEN) \
	$(ACTION_TYPE_HPP) $(ELEMENT_TYPE_HPP) $(KEYBOARD_FUNC) \
	$(BOMB_EXPLOSION_FUNC)

$(ACTION): $(COMMON_DIR)/$(ACTION).cpp $(INCLUDE_DIR)/$(ACTION).hpp
	$(CC) -c $< $(CC_FLAGS) -I$(INCLUDE_DIR) -o$(COMMON_DIR)/$@.o

$(ELEMENT): $(COMMON_DIR)/$(ELEMENT).cpp $(INCLUDE_DIR)/$(ELEMENT).hpp
	$(CC) -c $< $(CC_FLAGS) -I$(INCLUDE_DIR) -o$(COMMON_DIR)/$@.o

$(GAME): $(COMMON_DIR)/$(GAME).cpp $(INCLUDE_DIR)/$(GAME).hpp
	$(CC) -c $< $(CC_FLAGS) -I$(INCLUDE_DIR) -o$(COMMON_DIR)/$@.o

$(KEYBOARD): $(COMMON_DIR)/$(KEYBOARD).cpp $(INCLUDE_DIR)/$(KEYBOARD).hpp
	$(CC) -c $< $(CC_FLAGS) -I$(INCLUDE_DIR) -o$(COMMON_DIR)/$@.o

$(SCREEN): $(COMMON_DIR)/$(SCREEN).cpp $(INCLUDE_DIR)/$(SCREEN).hpp
	$(CC) -c $< $(CC_FLAGS) -I$(INCLUDE_DIR) -o$(COMMON_DIR)/$@.o

$(KEYBOARD_FUNC): $(COMMON_DIR)/$(KEYBOARD_FUNC).cpp \
	$(INCLUDE_DIR)/$(KEYBOARD_FUNC).hpp
	$(CC) -c $< $(CC_FLAGS) -I$(INCLUDE_DIR) -o$(COMMON_DIR)/$@.o

$(BOMB_EXPLOSION_FUNC): $(COMMON_DIR)/$(BOMB_EXPLOSION_FUNC).cpp \
	$(INCLUDE_DIR)/$(BOMB_EXPLOSION_FUNC).hpp
	$(CC) -c $< $(CC_FLAGS) -I$(INCLUDE_DIR) -o$(COMMON_DIR)/$@.o

common-clean:
	$(RM) $(RM_FLAGS) $(COMMON_DIR)/$(ACTION).o $(COMMON_DIR)/$(ELEMENT).o \
	$(COMMON_DIR)/$(GAME).o $(COMMON_DIR)/$(KEYBOARD).o \
	$(COMMON_DIR)/$(SCREEN).o $(COMMON_DIR)/$(KEYBOARD_FUNC).o \
	$(COMMON_DIR)/$(BOMB_EXPLOSION_FUNC).o
##########################################################################
