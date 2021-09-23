#include <iostream>

using namespace std;

struct HEVCHeader
{
#ifdef RTP_BIG_ENDIAN
	uint16_t flag : 1;
	uint16_t type : 6;
	uint16_t layerId : 6;
	uint16_t tid : 3;
#else
	uint16_t tid : 3;
	uint16_t layerId : 6;
	uint16_t type : 6;
	uint16_t flag : 1;
#endif // RTP_BIG_ENDIAN
};

struct NewHeader
{
#ifdef RTP_BIG_ENDIAN
	uint16_t layerId_2 : 5;
	uint16_t tid : 3;

	uint16_t flag : 1;
	uint16_t Type : 6;
	uint16_t layerId_1 : 1;
#else
	uint16_t layerId_1	: 1;
	uint16_t Type		: 6;
	uint16_t flag		: 1;

	uint16_t tid		: 3;
	uint16_t layerId_2	: 5;
#endif // RTP_BIG_ENDIAN
};


struct HEVCHeader_uint8_t
{
#ifdef RTP_BIG_ENDIAN
	uint8_t layerId_2 : 5;
	uint8_t tid : 3;

	uint8_t flag : 1;
	uint8_t Type : 6;
	uint8_t layerId_1 : 1;
#else
	uint8_t layerId_1 : 1;
	uint8_t Type : 6;
	uint8_t flag : 1;

	uint8_t tid : 3;
	uint8_t layerId_2 : 5;
#endif // RTP_BIG_ENDIAN
};

int main()
{
	HEVCHeader hevcHeader;
	hevcHeader.flag = 0;
	hevcHeader.type = 25;
	hevcHeader.layerId = 0;
	hevcHeader.tid = 1;
	//获取hevcHeader的头指针
	//uint8_t* head = (uint8_t*)&hevcHeader;
	uint8_t* head = reinterpret_cast<uint8_t*>(&hevcHeader);
	uint8_t head1 = *head;
	uint8_t head2 = *(head+1);
	printf("head1=0x%x\n", head1);
	printf("head2=0x%x\n", head2);
	/*
	* printf
	* hex : head1=0x01
	* hex : head2=0x32
	* bin : head1=00000001
	* bin :	head2=00110010
	* 理论值 ：00110010 00000001
	* 实际值 ：00000001 00110010
	* 
	*/

	HEVCHeader_uint8_t newHeader;
	newHeader.flag = 0;
	newHeader.Type = 25;
	newHeader.layerId_1 = 0;
	newHeader.layerId_2 = 0;
	newHeader.tid = 1;
	uint8_t* newhead = reinterpret_cast<uint8_t*>(&newHeader);
	uint8_t newhead1 = *newhead;
	uint8_t newhead2 = *(newhead + 1);
	printf("newhead1=0x%x\n", newhead1);
	printf("newhead2=0x%x\n", newhead2);
	/*
	* printf
	* hex : head1=0x32
	* hex : head2=0x01
	* bin : head1=00110010
	* bin :	head2=00000001
	* 理论值 ：00110010 00000001
	* 实际值 ：00110010 00000001
	* 
	*/

	return 0;
}