/*************************************************************************
	> File Name: udp_server.h
	> Author: fjl_57
	> Mail: 799619622@qq..com 
	> Created Time: Tue 22 Mar 2016 07:51:45 PM CST
************************************************************************/
#pragma once

//#include <iostream>
//#include <string>
//#include <map>
//#include <errno.h>
//#include <sys/socket.h>
//#include <sys/types.h>
//#include <arpa/inet.h>
//#include <netinet/in.h>
//#include <stdlib.h>
//#include <string.h>
#include "comm.h"
#include "data_pool.h"
#include "udp_data.h"

class udp_server{
private:
	int recv_msg(std::string &_out_msg);
	int send_msg(const std::string &_in_msg,\
			const struct sockaddr_in &client,\
			socklen_t len);
	bool register_user(const struct sockaddr_in &client, std::string&);

public:
	udp_server(unsigned short _port = 8080);
	int init_server();
	int reliable_send_msg(const std::string &_in_msg,\
			const struct sockaddr_in &client,\
			socklen_t len);
	int reliable_recv_msg();
	int broadcast_msg();
	~udp_server();

private:
	int sock;
	unsigned short port;
	data_pool pool;
	std::map<std::string, struct sockaddr_in> online_user;
};

