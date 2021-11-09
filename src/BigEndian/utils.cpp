#include "utils.h"


vsnc::vweb::VPacket vsnc::vweb::unPack(uint8_t* const stream, const int size)
{
	VPacket packet;
	auto data = stream + 12;
	auto len = size-12;
	HEVCIndicator* hevcIndeicator = reinterpret_cast<HEVCIndicator*>(data);
	if (hevcIndeicator->type == 49)
	{
		HEVCFUHeader* hevcFUHeader = reinterpret_cast<HEVCFUHeader*>(data + 2);
		hevcIndeicator->type = hevcFUHeader->type;
		if (hevcFUHeader->s != 1)
		{
			packet.Head = data + 3;
			packet.Size = len - 3;
			return packet;
		}
		if (hevcFUHeader->type == 19)
		{
			data = data - 2;
			*data = 0;
			*(data + 1) = 0;
			*(data + 2) = 1;
			std::memcpy(data + 3, hevcIndeicator, 2);
			packet.Head = data;
			packet.Size = len + 2;
		}
		else
		{
			data = data - 3;
			*data = 0;
			*(data + 1) = 0;
			*(data + 2) = 1;
			*(data + 3) = 2;
			std::memcpy(data + 4, hevcIndeicator, 2);
			packet.Head = data;
			packet.Size= len + 3;
		}
		return packet;
	}
	return VPacket();
}
