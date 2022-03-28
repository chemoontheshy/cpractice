#include "test.h"
#include <Windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace vsnc::test;


void test(const Packet& input, Packet& output)
{
	std::vector<uint8_t> temp;
	for (size_t i = 0; i < 10; ++i) {
		temp.push_back(1);
	}
	memcpy(input.data, reinterpret_cast<uint8_t*>(&temp.at(0)), temp.size());
	output.data = input.data;
	output.length = 10;
}

using namespace vsnc::test;
int main()
{
	uint8_t atemp[10]{ 1 };
	Packet input;
	input.data = reinterpret_cast<uint8_t*>(&atemp);
	input.length = 10;
	Packet output;
	test(input, output);


	const char* filepath = "..\\..\\3rd\\bin\\h264.bin";
	std::ifstream file(filepath, std::ios::in | std::ios::binary);
	if (!file.is_open())
	{
		std::cout << "not open the file" << std::endl;
		return -1;
	}
	bool stop = true;
	char temp[100000];
	int64_t cur_len = 0;
	while (stop)
	{
		file.getline(temp,100000,'\n');
		int len = file.tellg() - cur_len;
		cur_len = file.tellg();
		std::cout << len-1 << std::endl;
	}

	return 0;
}