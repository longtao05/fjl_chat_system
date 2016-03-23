/*************************************************************************
	> File Name: data_pool.cpp
	> Author: fjl_57
	> Mail: 799619622@qq..com 
	> Created Time: Tue 22 Mar 2016 07:07:58 PM CST
 ************************************************************************/

#include"data_pool.h"

data_pool::data_pool()
	:pool(CAPACITY),
	start(0),
	end(0)
{
	sem_init(&put_sem, 0, CAPACITY);
	sem_init(&get_sem, 0, 0);
}

void data_pool::put_msg(const std::string &_msg)
{	
	sem_wait(&put_sem);
	pool[end]=_msg;
	end++;
	end%=CAPACITY;
	sem_post(&get_sem);
}

const std::string& data_pool::get_msg()
{
	sem_wait(&get_sem);//P
	std::string data = pool[start];
	++start;
	start%=CAPACITY;
	sem_post(&put_sem);//V
}

data_pool::~data_pool()
{}
