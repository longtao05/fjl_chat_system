#pragma once
#include<iostream>
#include<string>
#include<map>
#include<>
#include<>
#include<>
#define G_BLOCK_SIZE 1024

class udp_server{
public:
	udp_server(unsigned short _port=8080);
	int init_server();
	int recv_msg();
	int send_msg();
	int broadcast_msg();
	~udp_server();
private:
	unsigned short port;
	data_pool pool;
	std::map<std::string,struct sockaddr_in> online_user;
	
};
