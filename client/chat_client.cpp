/*************************************************************************
	> File Name: chat_client.cpp
	> Author: fjl_57
	> Mail: 799619622@qq..com 
	> Created Time: Sat 19 Mar 2016 07:07:30 PM CST
 ************************************************************************/

#include"udp_client.h"

int  main()
{
	udp_client client;
	client.init_client();
	std::string msg;
	while(1){
		std::cout<<"Please Enter : ";
		fflush(stdout);
		std::cin>>msg;
		

	}

}
