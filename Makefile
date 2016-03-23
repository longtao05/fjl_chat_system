ROOT_PATH=$(shell pwd)

SERVER_BIN=server.cpp
CLIENT_BIN=client.cpp

CLIENT=$(POOT_PATH)/client
COMM=$(POOT_PATH)/comm
CONF=$(POOT_PATH)/sonf
LOG=$(POOT_PATH)/log
PLUGIN=$(POOT_PATH)/plugin
SERVER=$(POOT_PATH)/server
WINDOW=$(POOT_PATH)/window
LIB=$(POOT_PATH)/lib


INCLUDE=
LIB_A_SO=

CC=g++
FLAGS=-D_DEBUG_
LDFLAGS=

SRC=$(shell ls -R | grep '.cpp' |sed  's/libjsoncpp.a//g')
OBJ=$(SRC:.cpp=.o)
SER_OBJ=$(shell echo $(OBJ) | sed 's/chat_client.o\|udp_client.o\|window.o//g')
CLI_OBJ=$(shell echo $(OBJ) | sed 's/chat_server.o\|udp_server.o//g')

#.PHONG:debug

.PHONY:all
all:$(LCIENT_BIN) $(SERVER)

$()

%.o:$(CLIENT)/%.cpp
	$(CC) -c $<
%.o:$(SERVER)/%.cpp
	$(CC) -c $<
%.o:$(WINDOW)/%.cpp
	$(CC) -c $<


debug:
	@echo















