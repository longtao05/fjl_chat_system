#include"udp_server.h"



static void print_log(std::string _log)
{
	std::cerr<<_log<<std::endl;
}

udp_server::udp_server(unsigned short _port):port(_port)
{
	sock=-1;
}


//
int udp_server::init_server()
{
	sock = socket(AF_INET, SOCK_DGRAM, 0);
	if( sock<0 ){
		print_log(strerror(errno));
		exit(1);
	}
	struct sockaddr_in local;
	local.sin_family = AF_INET;
	local.sin_port   = htons(port);
	local.sin_addr_s_addr = htonl(INADDR_ANY);
	if( bind(sock,(struct sockaddr *)&local, sizeof(local))<0 ){
		print_log(strerror(errno));
		exit(1);
	}
	return 0;
}
int udp_server::realiable_recv_msg()
{
	int ret = recv_msg(out_msg);
	pool.put_msg();
	return ret;
}
int udp_server::recv_msg()
{
	char buf[G_BLOCK_SIZE];
	int size=sizeof(buf);
	memset(buf, '\0',size);
	struct sockaddr_in client;
	socklen_t len = sizeof(client);
	ssize_t _size=recvfrom(sock,buf,size-1,0,(struct sockaddr* )&client,&len );
	if(_size<0){
		print_log(strerror(errno));
		_out_msg="";
		return 1;
	}else if(_size >= 0){
		_out_msg = buf;	
	}else{
		//nothings to do
	}
	return _size;
}
int udp_server::send_msg(const std::string &_in_msg,struct sockaddr_in * client,socklent_t len)
{
	ssize_t _size = sendto( sock, _in_msg.s_str(), _in_msg_size(), 0, client, len );
	if(_size<0){
		print_log(strerror(errno));
		return 1;
	}else{
		//	
	}
	return 0;
}
int udp_server::broadcast_msg()
{
	std::string msg = pool.get_msg();
	std::map<std::string, struct sockaddr_in>::iterator _iter = online_user.begin();
	for(; _iter != online_user.end(), _iter++ ){
		reliable_send_msg(msg, _iter->second, sizeof(_iter->second));
	}
}
~udp_server::udp_server()
{
	if(sock != 0){
		close(sock);
	}
}
