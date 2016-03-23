/*************************************************************************
	> File Name: chat_server.cpp
	> Author: fjl_57
	> Mail: 799619622@qq..com 
	> Created Time: Tue 22 Mar 2016 07:50:45 PM CST
 ************************************************************************/

#include"udp_server.h"

//static udp_server server;
void * collect_data(void *arg)
{
	udp_server *s = (udp_server*)arg;
	while(1)
	s->reliable_msg();

}
void * send_data(void *arg)
{
	udp_server *s = (udp_server*)arg;
	while(1)
	s->broadcast_msg();
}
static void usage(void * proc)
{
	std::cout<<"Usage : "<<proc<<"[PORT]"<<std::endl;
}

int main(int argc ,char *argv[])
{
	if(argc != 2){
		usage(argv[0]);
		exit(1);
	}

	int port =aoti(argv[1]);
	udp_server server(port);
	server.init_server();

	pthread_t id1,id2;
	pthreat_create(&id1,NULL,collect_data,NULL);
	pthreat_create(&id2,NULL,send_data,NULL);

	pthread_join(id1,NULL);
	pthread_join(id2,NULL);
}
