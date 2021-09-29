#include "test.h"
#include <Windows.h>
#include <iostream>
#include <fstream>
#include <string>

using namespace vsnc::test;
int main()
{
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