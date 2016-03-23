/*************************************************************************
	> File Name: data_pool.h
	> Author: fjl_57
	> Mail: 799619622@qq..com 
	> Created Time: Tue 22 Mar 2016 07:08:06 PM CST
 ************************************************************************/
#pragma once
#include<iostream>
#include<string>
#include<semaphore.h>
#define CAPACITY 1024

class data_pool{

public:
	data_pool();
	void put_msg(const std::string &_msg);
	const std::string get_msg();
	~data_pool();
private:
	sem_t put_sem;
	sem_t get_sem;
	vector<std::string> pool; //
	//int capacity; //
	int size;
	int start;
	int end;

};
