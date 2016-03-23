/*************************************************************************
	> File Name: json.h
	> Author: fjl_57
	> Mail: 799619622@qq..com 
	> Created Time: Tue 22 Mar 2016 08:58:53 PM CST
 ************************************************************************/
#pragma once
#include<iostream>


class my_json{
public:
	my_json();
	~my_json();
	static int serialize(Json::Value &_in_val,std::string &_str_out);
	static int deserialize(Json::Value &_in_val,std::string &_str_out);
};


