#pragma once

#include <iostream>
#include <string>
#include <json/json.h>
class my_json{
public:
	my_json();
	~my_json();
	static int serialize(Json::Value &_in_val, std::string &_str_out);
	static int deserialize(std::string &_in_str, Json::Value &_val_out);
};
