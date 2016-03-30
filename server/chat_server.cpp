/*************************************************************************
	> File Name: chat_server.cpp
	> Author: fjl_57
	> Mail: 799619622@qq..com 
	> Created Time: Tue 22 Mar 2016 07:50:45 PM CST
 ************************************************************************/
#include <iostream>
#include <string>
#include <stdlib.h>
#include <unistd.h>
#include "udp_server.h"

void* collect_data(void* arg)
{
	udp_server *s = (udp_server*)arg;
	while(1){
		s->reliable_recv_msg();
	}
}

void *send_data(void *arg)
{
	udp_server *s = (udp_server*)arg;
	while(1){
		s->broadcast_msg();
	}
}

static void usage(std::string proc)
{
	std::cout<<"Usage : \033[31m"<<proc<<" [PORT]\033[0m"<<std::endl;
}

int main(int argc ,char *argv[])
{
	if(argc != 2){
		usage(argv[0]);
		exit(1);
	}

	int port = atoi(argv[1]);
	udp_server server(port);
	server.init_server();
	//daemon(0, 0);

	pthread_t id1, id2;
	pthread_create(&id1, NULL, collect_data, (void*)&server);
	pthread_create(&id2, NULL, send_data, (void*)&server);

	pthread_join(id1, NULL);
	pthread_join(id2, NULL);

//	server.reliable_recv_msg(_out_msg);
//	std::cout<<_out_msg<<std::endl;
//	sleep(1);
//	_out_msg = "";
//	server.reliable_recv_msg(_out_msg);
//	std::cout<<_out_msg<<std::endl;
//	sleep(1);
//	_out_msg = "";
//	server.reliable_recv_msg(_out_msg);
//	std::cout<<_out_msg<<std::endl;
//	sleep(1);
//	_out_msg = "";
//	std::string msg = "hello world";
//	server.reliable_send_msg(msg, struct sockaddr_in* client, socklen_t len);
	return 0;
}







