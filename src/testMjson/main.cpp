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
#include <unordered_map>

#define __VSNC_IN     // 输入参数
#define __VSNC_OUT    // 输出参数
#define __VSNC_IN_OUT // 输入输出参数

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

bool __parse_json(const std::string& __VSNC_IN body, std::unordered_map<std::string, std::string>& __VSNC_OUT replyList) noexcept
{
	int koff, klen, voff, vlen, vtype, off;
	auto bodyPtr = body.c_str();
	for (off = 0; (off = mjson_next(bodyPtr, body.size(), off, &koff, &klen, &voff, &vlen, &vtype)) != 0;)
	{
		//std::cout << "key: " << std::string(bodyPtr + koff+1, klen-2) << " value:" << std::string(bodyPtr + voff, vlen)<<std::endl;
		replyList.emplace(std::string(bodyPtr + koff + 1, klen - 2), std::string(bodyPtr + voff, vlen));
		
	}
	return true;
}
bool __parse_array(const std::string& __VSNC_IN body, std::unordered_map<std::string, std::string>& __VSNC_OUT replyList) noexcept
{
	int koff, klen, voff, vlen, vtype, off;
	auto bodyTemp = "[" + body + "]";
	auto bodyPtr = bodyTemp.c_str();
	for (off = 0; (off = mjson_next(bodyPtr, body.size(), off, &koff, &klen, &voff, &vlen, &vtype)) != 0;)
	{
		std::cout<< " value:" << std::string(bodyPtr + voff+1, vlen-2)<<std::endl;
		//replyList.emplace(std::string(bodyPtr + koff + 1, klen - 2), std::string(bodyPtr + voff, vlen));

	}
	return true;
}

int main()
{

	//std::string body = ""\"1\",\"2\";
	std::string body = "\"1\",\"2\",\"3\"";
	std::unordered_map<std::string, std::string> replyList;
	__parse_array(body, replyList);
	return 0;
	__parse_json(body, replyList);
	if (__parse_json(body, replyList))
	{
		for (auto& reply : replyList)
		{
			std::cout << reply.first <<":" <<reply.second<< std::endl;
		}
	}
	return 0;
}