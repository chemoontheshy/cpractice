#include <iostream>

#ifdef TEST
int a = 3;
#else
int a = 4;
#endif // TEST


struct RTPHeader
{
#ifdef  RTP_BIG_ENDIAN
	uint8_t version : 2;
	uint8_t padding : 1;
	uint8_t extension : 1;
	uint8_t csrccount : 4;

	uint8_t marker : 1;
	uint8_t payloadtype : 7;
#else// little endian
	uint8_t csrccount : 4;
	uint8_t extension : 1;
	uint8_t padding : 1;
	uint8_t version : 2;

	uint8_t payloadtype : 7;
	uint8_t marker : 1;
#endif //  RTP_BIG_ENDIAN
	uint16_t sequencenumber;
	uint32_t timestamp;
	uint32_t ssrc;

};

bool IsBigEndian()
{
	int a = 0x1234;
	char b = *(char*)&a;  //通过将int强制类型转换成char单字节，通过判断起始存储位置。即等于 取b等于a的低地址部分  
	if (b == 0x12)
	{
		std::cout << "BigEndian" << std::endl;
		return true;
	}
	std::cout << "littleEndian" << std::endl;
	return false;
}

int main()
{
	std::cout << a << std::endl;
}