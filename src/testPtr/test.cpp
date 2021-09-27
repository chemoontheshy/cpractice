#include "test.h"

#include <random>
#include <ctime>

uint16_t vsnc::test::GetRandomU16()
{
	std::default_random_engine e;
	uint16_t temp=0;
	int shift = 0;
	for (int i = 0; i < 2; i++, shift += 8)
	{
		e.seed(temp);
		temp ^= (static_cast<uint16_t>(e()) << shift);
	}
	return temp;
}

uint32_t vsnc::test::GetRandomU32()
{
	std::default_random_engine e;
	uint32_t temp = 0;
	int shift = 0;
	for (int i = 0; i < 4; i++, shift += 8)
	{
		e.seed(time(0));
		temp ^= (static_cast<uint16_t>(e()) << shift);
	}
	return temp;
}

int vsnc::test::CheckFrameHeader(const Packet& packet)
{
	auto temp = reinterpret_cast<uint32_t*>(packet.data);
	if ((*reinterpret_cast<uint32_t*>(packet.data) & 0xFF01FFFF) == 0x00010000) return 3;
	if (*reinterpret_cast<uint32_t*>(packet.data)  == 0x01000000) return 4;
	return -1;
}


