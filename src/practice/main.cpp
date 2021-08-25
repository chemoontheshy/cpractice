#include <iostream>

using namespace std;

struct RTSP_header
{
	unsigned char dollar_sign = 0x24;
	unsigned char channel_identifier = 1;
	unsigned short data_length = 1000;
	//unsigned char stop_bit = 10;
};

int main() {
	char test[10] = "0123456789";
	cout << "test:" << +test[0] << endl;
	cout << "test:" << &test << endl;
	cout << "test:" << &test+1 << endl;
	cout << "test" << +test << endl;
	auto a = &test;
	return 0;
}