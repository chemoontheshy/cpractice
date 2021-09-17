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
	uint16_t layerId_1	: 5;
	uint16_t tid		: 3;
	uint16_t flag		: 1;
	uint16_t Type		: 6;
	uint16_t layerId_2	: 1;
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
	* hex : head1=0xc9
	* hex : head2=0xc0
	* bin : head1=11001001
	* bin :	head2=11000000
	* 理论值 ：00110010 00000001
	* 实际值 ：00000001 00110010
	* 
	*/

	NewHeader newHeader;
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
	* hex : head1=0xc9
	* hex : head2=0xc0
	* bin : head1=11001001
	* bin :	head2=11000000
	* 理论值 ：00110010 00000001
	* 实际值 ：00000001 00110010
	* 
	*/

	return 0;
}