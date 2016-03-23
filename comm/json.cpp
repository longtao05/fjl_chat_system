/*************************************************************************
	> File Name: json.cpp
	> Author: fjl_57
	> Mail: 799619622@qq..com 
	> Created Time: Tue 22 Mar 2016 08:59:15 PM CST
 ************************************************************************/

#incluude"json.h"

my_json::my_json()
{
	Json::StyleWriter _write;
	//Json::FastWriter _write;
	_str_out = _write.write(_in_val);

}
my_json::~my_json()
{}
static int serialize(Json::Value &_in_val,std::string &_str_out)
{
	Json::StyleWriter _write;
	//Json::FastWriter _write;
	_str_out = _write.write(_in_val);
}
static int deserialize(Json::Value &_in_val,std::string &_str_out)
{
	Json::Reader _reader;
	if(_reader.parse(_in_val)){

		return 0;
	}else{
		return 1;
	}
}


int main()
{
	Json::Va
	my_json::serialize();
	return 0;
}
