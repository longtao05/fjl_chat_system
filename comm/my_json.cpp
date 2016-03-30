#include "my_json.h"

my_json::my_json()
{
}

//序列化
int my_json::serialize(Json::Value &_in_val, std::string &_str_out)
{
#ifdef _STYLE_
	//带格式的Json
	Json::StyledWriter _write;
#else
	//不带格式的Json
	Json::FastWriter _write;
#endif
	_str_out = _write.write(_in_val);
}

//反序列化
int my_json::deserialize(std::string &_in_str, Json::Value &_val_out)
{
	Json::Reader _reader;
	if(_reader.parse(_in_str, _val_out, false)){
		return 0;
	}else{
		return 1;
	}
}

my_json::~my_json()
{
}

//测试用例
//int main()
//{
//	
//	std::string _str_out;
//	Json::Value _val;
//	_val["nick_name"] = "fjl";
//	_val["school"]    = "XATU";
//	_val["msg"]       = "hello";
//	my_json::serialize(_val, _str_out);
//	std::cout<<_str_out<<std::endl;
//	
//
//	Json::Value _val_out;
//	my_json::deserialize(_str_out, _val_out);
//
//	std::cout<<_val_out["nick_name"].asString()<<std::endl;
//	std::cout<<_val_out["school"].asString()<<std::endl;
//	return 0;
//}










