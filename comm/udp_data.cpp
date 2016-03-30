#include "udp_data.h"

udp_data::udp_data()
{}

//
bool udp_data::val_to_str(std::string &_out_msg)
{
	Json::Value _val;
	//key => value
	_val["nick_name"] = nick_name;
	_val["school"]    = school;
	_val["msg"]       = msg;
	_val["cmd"]       = cmd;

	my_json::serialize(_val, _out_msg);
}

bool udp_data::str_to_val(std::string &_in_msg)
{
	Json::Value _val_out;
	my_json::deserialize(_in_msg, _val_out);

	nick_name = _val_out["nick_name"].asString();
	school    = _val_out["school"].asString();
	msg       = _val_out["msg"].asString();
	cmd       = _val_out["cmd"].asString();
}

udp_data::~udp_data()
{}





