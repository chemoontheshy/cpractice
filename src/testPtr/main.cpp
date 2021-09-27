#include "test.h"
#include <Windows.h>
#include <iostream>
#include <fstream>
#include <string>

using namespace vsnc::test;
int main()
{
	const char* filepath = "..\\..\\3rd\\bin\\h264.txt";
	std::ifstream file(filepath, std::ios::in | std::ios::binary);
	if (!file.is_open())
	{
		std::cout << "not open the file" << std::endl;
		return -1;
	}
	bool stop = true;
	char temp[1000];
	while (stop)
	{
		file.getline(temp,1000);
		if (line.empty()) stop = !stop;
		std::cout << line.size() << std::endl;
	}

	return 0;
}