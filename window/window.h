
/************************************************************************
	> File Name: window.h
	> Author: fjl_57
	> Mail: 799619622@qq..com 
	> Created Time: Sat 19 Mar 2016 07:13:48 PM CST
 ************************************************************************/
#pragma once

#include <iostream>
#include <ncurses.h>//
#include <string>
#include <string.h>
#include <comm.h>
#include <pthread.h>

class chat_window{
public:
	chat_window();
	void init();
	WINDOW* create_win(const int &hei, const int &wth, const int &y, const int &x);
	//刷新窗口
	void win_refresh(WINDOW *_win);
	//
	void put_str_to_win(WINDOW *_win, int y, int x, const std::string &_str);
	void get_str_from_win(WINDOW *_win, std::string &_out);
	void clear_win_line(WINDOW *_win, int begin, int num);
	~chat_window();

	void draw_header();
	void draw_output();
	void draw_friends_list();
	void draw_input();

	WINDOW *get_header()
	{
		return this->header; 
	}

	WINDOW *get_output()
	{
		return this->output; 
	}

	WINDOW *get_friends_list()
	{ 
		return this->friends_list;
	}

	WINDOW *get_input()
	{
		return this->input; 
	}

private:

	pthread_mutex_t lock;
	WINDOW *header;
	WINDOW *output;
	WINDOW *friends_list;
	WINDOW *input;
};
