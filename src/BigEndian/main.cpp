#include "utils.h"
int main()
{
	vsnc::vweb::HEVCIndicator hevcIndicator;
	hevcIndicator.flag = 0;
	hevcIndicator.layerId1 = 0;
	hevcIndicator.layerId2 = 0;
	hevcIndicator.tid = 1;
	hevcIndicator.type = 49;
	vsnc::vweb::HEVCFUHeader hevcFUHeader;
	hevcFUHeader.type = 29;
	hevcFUHeader.s = 1;
	hevcFUHeader.e = 0;
	char data[22] = { '0' };
	memcpy(data + 12, &hevcIndicator, 2);
	memcpy(data + 14, &hevcFUHeader, 1);

	uint8_t* stream = reinterpret_cast<uint8_t*>(data);
	auto packet = vsnc::vweb::unPack(stream,22);
	std::cout << packet.Size<<std::endl;
	return 0;
}