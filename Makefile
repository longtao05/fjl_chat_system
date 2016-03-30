ROOT_PATH=$(shell pwd)

SERVER_BIN=chat_server
CLIENT_BIN=chat_client

CLIENT=$(ROOT_PATH)/client
COMM=$(ROOT_PATH)/comm
CONF=$(ROOT_PATH)/conf
LIB=$(ROOT_PATH)/lib
LOG=$(ROOT_PATH)/log
PLUGIN=$(ROOT_PATH)/plugin
SERVER=$(ROOT_PATH)/server
WINDOW=$(ROOT_PATH)/window
DATA_POOL=$(ROOT_PATH)/data_pool

INCLUDE= -I$(COMM) -I$(DATA_POOL) -I$(WINDOW) -I$(LIB)/include
LIB_A_SO=-L$(LIB)/lib 

CC=g++
FLAGS=$(INCLUDE)  -D_DEBUG_ -D_STYLE_
LDFLAGS=$(LIB_A_SO) -lpthread -ljsoncpp -lncurses

SRC=$(shell ls -R | grep '.cpp'| sed 's/libjsoncpp.a//g')
OBJ=$(SRC:.cpp=.o)
SER_OBJ=$(shell echo $(OBJ) | sed 's/chat_client.o\|udp_client.o\|window.o//g')
CLI_OBJ=$(shell echo $(OBJ) | sed 's/chat_server.o\|udp_server.o\|data_pool.o//g')

.PHONY:all
all:$(SERVER_BIN) $(CLIENT_BIN)


$(SERVER_BIN):$(SER_OBJ)
	echo "Building [$^] to [$@]"
	$(CC) -o $@ $^ $(LDFLAGS) 
	echo "Building Done..."
$(CLIENT_BIN):$(CLI_OBJ)
	echo "Building [$^] to [$@]"
	$(CC) -o $@ $^ $(LDFLAGS)
	echo "Building Done..."
%.o:$(CLIENT)/%.cpp
	echo "Compling [$<] to [$@]"
	$(CC) -c $< $(FLAGS)
	echo "Compling Done..."
%.o:$(SERVER)/%.cpp
	echo "Compling [$<] to [$@]"
	$(CC) -c $< $(FLAGS)
	echo "Compling Done..."
%.o:$(WINDOW)/%.cpp
	echo "Compling [$<] to [$@]"
	$(CC) -c $< $(FLAGS)
	echo "Compling Done..."
%.o:$(COMM)/%.cpp
	echo "Compling [$<] to [$@]"
	$(CC) -c $< $(FLAGS)
	echo "Compling Done..."
%.o:$(DATA_POOL)/%.cpp
	echo "Compling [$<] to [$@]"
	$(CC) -c $< $(FLAGS)
	echo "Compling Done..."

.PHONY:clean
clean:
	rm -rf *.o $(SERVER_BIN) $(CLIENT_BIN) output

.PHONY:output
output:
	mkdir -p output/server/conf
	mkdir -p output/server/log
	mkdir -p output/client
	cp $(SERVER_BIN) output/server
	cp $(CLIENT_BIN) output/client
	cp $(PLUGIN)/ctrl_server.sh output/server
	cp $(CONF)/server.conf output/server/conf

