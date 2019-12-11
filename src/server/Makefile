# VARIABLES
##########################################################################
BIN = 					main

COMMON_DIR = 			../common
##########################################################################

# MAKEFILE INCLUDES
##########################################################################
include $(COMMON_DIR)/Makefile
##########################################################################

# FUNCTIONS USED ONLY ON SERVER SIDE
##########################################################################
BOMB_EXPLOSION_FUNC = 	bomb_explosion_func
CONN_MGMT_FUNC = 		conn_mgmt_func
GAME_SEND_FUNC = 		game_send_func
KBOARD_RECV_FUNC =		kboard_recv_func
##########################################################################

# RULES
##########################################################################
all: $(BIN)

run-local: all
	./$(BIN) 127.0.0.1

$(BIN): main.cpp $(CONN_MGMT_FUNC) $(GAME_SEND_FUNC) \
	$(KBOARD_RECV_FUNC) common-all
	$(CC) $< $(COMMON_DIR)/$(ACTION).o $(COMMON_DIR)/$(ELEMENT).o \
	$(COMMON_DIR)/$(GAME).o $(COMMON_DIR)/$(KEYBOARD).o  \
	$(COMMON_DIR)/$(SCREEN).o $(COMMON_DIR)/$(KEYBOARD_FUNC).o \
	$(COMMON_DIR)/$(BOMB_EXPLOSION_FUNC).o $(CONN_MGMT_FUNC).o \
	$(GAME_SEND_FUNC).o $(KBOARD_RECV_FUNC).o $(CC_FLAGS) -I$(INCLUDE_DIR) -o$@

$(CONN_MGMT_FUNC): $(CONN_MGMT_FUNC).cpp $(INCLUDE_DIR)/$(CONN_MGMT_FUNC).hpp
	$(CC) -c $< $(CC_FLAGS) -I$(INCLUDE_DIR) -o$@.o

$(GAME_SEND_FUNC): $(GAME_SEND_FUNC).cpp $(INCLUDE_DIR)/$(GAME_SEND_FUNC).hpp
	$(CC) -c $< $(CC_FLAGS) -I$(INCLUDE_DIR) -o$@.o

$(KBOARD_RECV_FUNC): $(KBOARD_RECV_FUNC).cpp \
	$(INCLUDE_DIR)/$(KBOARD_RECV_FUNC).hpp
	$(CC) -c $< $(CC_FLAGS) -I$(INCLUDE_DIR) -o$@.o

clean: common-clean
	$(RM) $(RM_FLAGS) $(BIN) $(CONN_MGMT_FUNC).o \
	$(GAME_SEND_FUNC).o $(KBOARD_RECV_FUNC).o
##########################################################################
