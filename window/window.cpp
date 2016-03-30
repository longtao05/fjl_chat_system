
/*************************************************************************
	> File Name: window.cpp
	> Author: fjl_57
	> Mail: 799619622@qq..com 
	> Created Time: Sat 19 Mar 2016 07:13:39 PM CST
 ************************************************************************/
#include "window.h"



chat_window::chat_window()
{
	header = NULL;
	output = NULL;
	friends_list = NULL;
	input = NULL;
}

void chat_window::init()
{
	pthread_mutex_init(&lock, NULL);
	//
	initscr();
}

WINDOW* chat_window::create_win(const int &hei,\
							    const int &wth,\
								const int &y,\
								const int &x)
{
	WINDOW *_win = newwin(hei, wth, y, x);
	return _win;
}

void chat_window::win_refresh(WINDOW *_win)
{
	box(_win, 0, 0);
	pthread_mutex_lock(&lock);
	wrefresh(_win);
	pthread_mutex_unlock(&lock);
}

void chat_window::clear_win_line(WINDOW *_win, int begin, int num)
{
	while( num-- > 0 ){
		wmove(_win, begin++, 0);
		wclrtoeol(_win);
	}
}

void chat_window::put_str_to_win(WINDOW *_win, int y, int x, const std::string &_str)
{
	mvwaddstr(_win, y, x, _str.c_str());
}

void chat_window::get_str_from_win(WINDOW *_win, std::string &_out)
{
	char buf[G_BLOCK_SIZE];
	memset(buf, '\0', sizeof(buf));
	wgetnstr(_win, buf, sizeof(buf));

	_out = buf;
}

void chat_window::draw_header()
{
	int hei = LINES/5;
	int wth = COLS*3/4;
	int y = 0;
	int x = COLS/8;

	this->header = create_win(hei, wth, y, x);
}


void chat_window::draw_output()
{
	int hei = LINES*3/5;
	int wth = COLS*3/4;
	int y   = LINES/5;
	int x   = 0;
	this->output = create_win(hei, wth, y, x);
}

void chat_window::draw_friends_list()
{
	int hei = LINES*4/5;
	int wth = COLS/4;
	int y = LINES/5;
	int x = COLS*3/4;
	this->friends_list = create_win(hei, wth, y, x);
}

void chat_window::draw_input()
{
	int hei = LINES/5;
	int wth = COLS;
	int y = LINES*4/5;
	int x = 0;
	this->input = create_win(hei, wth, y, x);
}

chat_window::~chat_window()
{
	pthread_mutex_destroy(&lock);
	delwin(this->header);
	endwin();
}


