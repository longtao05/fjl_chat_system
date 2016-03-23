/*************************************************************************
	> File Name: udp_client.h
	> Author: fjl_57
	> Mail: 799619622@qq..com 
	> Created Time: Sat 19 Mar 2016 07:08:04 PM CST
 ************************************************************************/
#pragma
#include<iostream>

class udp_client
{
public:
	udp_client(std::string _remote_ip = "127.0.0.1",unsigned short _port =8080);
	int client();
	int reliable_recv_msg();
	int reliable_send_msg();


	~udp_client();
private:
	std::string remote_ip;
	unsigned short remote_port;




};
