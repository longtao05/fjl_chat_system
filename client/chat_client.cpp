
/*************************************************************************
	> File Name: chat_client.cpp
	> Author: fjl_57
	> Mail: 799619622@qq..com 
	> Created Time: Sat 19 Mar 2016 07:07:30 PM CST
 ************************************************************************/
#include <iostream>
#include <string>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <vector>
#include <signal.h>
#include "udp_client.h"
#include "window.h"

chat_window win;
udp_client *_sig_client = NULL;

std::vector<std::string> list;

void *client_header(void *arg)
{
	win.draw_header();
	std::string message = "Welcome To Linux Chat System";
	int step = 5;
	while(1){
		win.put_str_to_win(win.get_header(), 2, step++, message);
	    win.win_refresh(win.get_header());
		step %= (COLS-5);
		if(step == 0){
			step = 5;
		}
		sleep(1);
		win.clear_win_line(win.get_header(), 2, 1);
	}
}

void *client_output(void *arg)
{
	udp_client *client = (udp_client*)arg;
	udp_data _data;
	std::string _msg;

	std::string nick_name;
	std::string school;
	std::string info;
	std::string cmd;
	int total = 1;
	win.draw_output();
	win.win_refresh(win.get_output());
	while(1){
		client->reliable_recv_msg(_msg);
		_data.str_to_val(_msg);
		
		_data.get_nick_name(nick_name);
		_data.get_school(school);
		_data.get_msg(info);
		_data.get_cmd(cmd);

		if(cmd == "MESSAGE"){
			std::string show_msg = nick_name;
			show_msg += "-";
			show_msg += school;

			list.push_back(show_msg);

			show_msg += ": ";
			show_msg += info;
			win.put_str_to_win(win.get_output(), total++, 2, show_msg);
			win.win_refresh(win.get_output());

			total %= (LINES*3/5-1);
			if(total == 0){
				total = 1;
				win.clear_win_line(win.get_output(), 1, LINES*3/5-1);
				win.win_refresh(win.get_output());
			}
		}
		usleep(100000);
	}
}
void *client_list(void *arg)
{
	//list
	win.draw_friends_list();
	while(1){
		int i = 0;
		int total = list.size();

		for(; i < total; i++){
			win.put_str_to_win(win.get_friends_list(), i+1, 2, list[i]);
		}

	    win.win_refresh(win.get_friends_list());
		usleep(100000);
	}
}
void *client_input(void *arg)
{
	udp_client *client = (udp_client*)arg;
	
	std::string message = "Please Enter: ";

	std::string _client_msg;
	std::string name="dandan";
	std::string school = "qinghua";
	std::string cmd = "MESSAGE";

	std::string send_string;
	udp_data _data;

	win.draw_input();
	while(1){
		win.win_refresh(win.get_input());
		win.put_str_to_win(win.get_input(), 1, 2, message);
		win.get_str_from_win(win.get_input(), _client_msg);

		_data.set_nick_name(name);
		_data.set_school(school);
		_data.set_msg(_client_msg);
		_data.set_cmd(cmd);


        _data.val_to_str(send_string);
		client->reliable_send_msg(send_string);
		usleep(100000);
		win.clear_win_line(win.get_input(), 1, 1);
	}
}

//客户端退出处理机制
void handler(int sig)
{
	std::string name = "dandan";
	std::string school = "qinghua";
	std::string _client_msg = "None";
	std::string cmd = "CMD-QUIT";
	udp_data _data;
	std::string send_string;
	switch(sig){
		case SIGINT:
			{
		        _data.set_nick_name(name);
		        _data.set_school(school);
		        _data.set_msg(_client_msg);
		        _data.set_cmd(cmd);
				_data.val_to_str(send_string);

				_sig_client->reliable_send_msg(send_string);
				exit(0);
			}
			break;
		case SIGTERM:
			{
				exit(0);
			}
			break;
		default:
			break;
	}
}

int main()
{
	udp_client client;
	client.init_client();
	win.init();
	_sig_client = &client;
	signal(SIGINT, handler);//ctrl+c
	signal(SIGTERM, handler);//请求中止进程，kill命令缺省发送
	
	pthread_t header, output, list, input;
	pthread_create(&header, NULL, client_header, NULL);
	pthread_create(&output, NULL, client_output, (void*)&client);
	pthread_create(&list, NULL, client_list, NULL);
	pthread_create(&input, NULL, client_input, (void*)&client);

	pthread_join(header, NULL);
	pthread_join(output, NULL);
	pthread_join(list, NULL);
	pthread_join(input, NULL);
	return 0;
}
