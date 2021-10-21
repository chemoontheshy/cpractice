/**
 * @file main.cpp
 * @brief 测试mjson的使用
 * @author xzf
 * @version v1
 * @date 2021-10-21
 */
#include "mjson/mjson.h"
#include <iostream>
#include <string>
#include <map>

static std::string __to_netmask(const size_t& cidr)
{
	auto bits = 32 - cidr;
	int mask = (bits == 32) ? 0 : 0xFFFFFFFF - ((1 << bits) - 1);
	return std::to_string(mask >> 24 & 0xFF) + "." + std::to_string(mask >> 16 & 0xFF) + "." + std::to_string(mask >> 8 & 0xFF) + "." + std::to_string(mask >> 0 & 0xFF);
}


static unsigned short toCidr(const std::string& ipAddress)
{
	unsigned short netmask_cidr;
	int ipbytes[4];

	netmask_cidr = 0;
	sscanf_s(ipAddress.c_str(), "%d.%d.%d.%d", &ipbytes[0], &ipbytes[1], &ipbytes[2], &ipbytes[3]);

	for (int i = 0; i < 4; i++)
	{
		switch (ipbytes[i])
		{
		case 0x80:
			netmask_cidr += 1;
			break;

		case 0xC0:
			netmask_cidr += 2;
			break;

		case 0xE0:
			netmask_cidr += 3;
			break;

		case 0xF0:
			netmask_cidr += 4;
			break;

		case 0xF8:
			netmask_cidr += 5;
			break;

		case 0xFC:
			netmask_cidr += 6;
			break;

		case 0xFE:
			netmask_cidr += 7;
			break;

		case 0xFF:
			netmask_cidr += 8;
			break;

		default:
			return netmask_cidr;
			break;
		}
	}

	return netmask_cidr;
}

std::string __get_string(const std::string& body,const std::string& key)
{
	char val[100];
	std::string result;
	std::string check_key = "$." + key;
	if (mjson_get_string(body.c_str(), strlen(body.c_str()), check_key.c_str(), val, sizeof(val)) >0)
	{
		return val;
	}
	return result;
}

std::string __add_double_quotes(const std::string& str)
{
	return "\"" + str + "\"";
}

std::string dump_json(const std::map<std::string, std::string>& mapList)
{
	std::string result;
	if (mapList.empty()) return result;
	std::cout << "2test" << std::endl;
	for (auto temp : mapList)
	{
		result = result + __add_double_quotes(temp.first) + ":" + __add_double_quotes(temp.second)+",";
	}
	result = result.substr(0, strlen(result.c_str()) - 1);
	return "{" + result + "}";
}


int main()
{
	std::string postdata = "{\"value\":\"true\"}";
	std::string checkKey = "2";
	auto a = __get_string(postdata, checkKey);
	if (a.empty())
	{
		std::cout << "test" << std::endl;
		std::cout << a << std::endl;
	}
	std::map<std::string, std::string> mapList;
	std::map<std::string, std::string> amapList;
	std::string local = "192.168.100.124/24";
	std::string adress = local.substr(0, strlen(local.c_str()) - 3);
	std::string netmask = local.substr(strlen(local.c_str())-2);
	std::string getway = "192.168.100.1";
	mapList["address"] = local.substr(0, strlen(local.c_str()) - 3);
	mapList["netmask"] = local.substr(strlen(local.c_str()) - 2);
	mapList["gatway"] = "192.168.100.1";
	auto reply = dump_json(mapList);
	std::cout << "reply: " << reply << std::endl;

	auto address = __get_string(reply, "address");
	if (!address.empty())
	{
		amapList["address"] = adress;
	}
	reply = dump_json(amapList);
	std::cout << "reply: " << reply << std::endl;

	auto id = toCidr("255.255.255.255");
	std::cout << "id: " << id << std::endl;

	auto sNetmask = __to_netmask(16);
	std::cout << "sNetmask: " << sNetmask << std::endl;
	return 0;
}