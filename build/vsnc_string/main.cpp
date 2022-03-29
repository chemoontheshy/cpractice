#include <iostream>

int main()
{
	auto __get_ip = [](const std::string& url, std::string& ip)->bool
	{
		std::string temp;
		if (url.find("rtsp://") == std::string::npos) return false;
		temp = url.substr(7);
		//有后缀的时候
		auto ret = temp.find("/");
		if (ret != std::string::npos)
		{
			temp = temp.substr(0, ret);
		}
		if (temp.find("@") != std::string::npos)
		{
			ret = temp.rfind("@");
			if (ret != std::string::npos)
			{
				temp = temp.substr(ret + 1);
			}
		}
		ip = temp;
		return true;
	};

	std::string rtsp = "rtsp://192.168.31.62/11";
	std::string ip;
	if (!__get_ip(rtsp, ip)) return -1;
	std::cout << ip << std::endl;
	return 0;
}