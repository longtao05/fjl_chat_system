
/*************************************************************************
	> File Name: data_pool.cpp
	> Author: fjl_57
	> Mail: 799619622@qq..com 
	> Created Time: Tue 22 Mar 2016 07:07:58 PM CST
 ************************************************************************/
#include "data_pool.h"

data_pool::data_pool()
	:pool(CAPACITY),
	start(0),
	end(0)
{
	sem_init(&put_sem, 0, CAPACITY);//0当前里程的局部信号量  
	sem_init(&get_sem, 0, 0);
}

void data_pool::put_msg(const std::string &_in_msg)
{
	sem_wait(&put_sem);//P操作 --
	pool[end] = _in_msg;
	++end;
	end %= CAPACITY;
	sem_post(&get_sem);//V操作 ++
}

void data_pool::get_msg(std::string &_out_msg)
{
	sem_wait(&get_sem);//P
	_out_msg = pool[start];
	++start;
	start %= CAPACITY;
	sem_post(&put_sem);//V
}

data_pool::~data_pool()
{}


