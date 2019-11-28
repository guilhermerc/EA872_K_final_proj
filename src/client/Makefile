# VARIABLES
##########################################################################
BIN = 				main

COMMON_DIR = 		../common
##########################################################################

# MAKEFILE INCLUDES
##########################################################################
include $(COMMON_DIR)/Makefile
##########################################################################

# FUNCTIONS USED ONLY ON CLIENT SIDE
##########################################################################
GAME_RECV_FUNC =	game_recv_func
##########################################################################

# RULES
##########################################################################
all: $(BIN)

run-local: all
	./$(BIN) 127.0.0.1

$(BIN): main.cpp $(GAME_RECV_FUNC) common-all
	$(CC) $< $(COMMON_DIR)/$(ACTION).o $(COMMON_DIR)/$(ELEMENT).o \
	$(COMMON_DIR)/$(GAME).o $(COMMON_DIR)/$(KEYBOARD).o \
	$(COMMON_DIR)/$(SCREEN).o $(COMMON_DIR)/$(KEYBOARD_FUNC).o \
	$(COMMON_DIR)/$(BOMB_EXPLOSION_FUNC).o $(GAME_RECV_FUNC).o $(CC_FLAGS) \
	-I$(INCLUDE_DIR) -o$@

$(GAME_RECV_FUNC): $(GAME_RECV_FUNC).cpp $(INCLUDE_DIR)/$(GAME_RECV_FUNC).hpp
	$(CC) -c $< $(CC_FLAGS) -I$(INCLUDE_DIR) -o$@.o

clean: common-clean
	$(RM) $(RM_FLAGS) $(BIN) $(GAME_RECV_FUNC).o
##########################################################################
