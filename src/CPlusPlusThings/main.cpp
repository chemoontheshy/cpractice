/**
 * @file main.h
 * @author xzf (xzfandzgx@gmal.com)
 * @brief 用于学习effective C++
 * @version 0.1
 * @date 2022-01-04
 *
 * @copyright Copyright (c) 2021
 *
 */
#include "effective.h"
#include "JT808Parser.h"
#include <string>
#include <vector>
#include<WinSock2.h>


 /// <summary>
		 /// 消息体属性为2字节
		 /// </summary>
typedef struct JT808Body
{

	/// <summary>长度前</summary>
	uint8_t   LengthFront;
	/// <summary>长度后</summary>
	uint8_t   LengthBack : 2;
	/// <summary>加密标识符：001为RSA加密，000不加密</summary>
	uint8_t   EncryptedBit : 3;
	/// <summary>分包标识符识符，为1为长消息，分包，为0不分包</summary>
	uint8_t   Subcontract : 1;
	/// <summary>保留位</summary>
	uint8_t   ReservedBit : 2;

}JT808Body;

/// <summary>
/// 消息头为12字节，（包含消息体属性2字节）
/// </summary>
typedef struct JT808Header
{
	/// <summary>消息ID</summary>
	uint16_t  Id;
	/// <summary>消息体属性</summary>
	JT808Body Body;
	/// <summary>设备号</summary>
	uint8_t   No[6];
	/// <summary>消息流水号</summary>
	uint16_t  Sequence;
}JT808Header;

/// <summary>
/// 消息包封装项，当分包标识符为1的时候，有消息包封装项，为0，则没有
/// </summary>
typedef struct JTPacketItem
{
	/// <summary>消息总包数</summary>
	uint16_t Total;
	/// <summary>包序号</summary>
	uint16_t PacketSequence;
}JTPacketItem;

uint8_t HexToBcd(uint8_t const& src) {
	uint8_t temp;
	temp = ((src / 10) << 4) + (src % 10);
	return temp;
}

uint8_t Check(const uint8_t* data, const size_t& length) noexcept
{
	uint8_t checkSum = 0;
	for (size_t i = 0; i < length; ++i) {
		checkSum = checkSum ^ *data;
		data++;
	}
	return checkSum;
}

int main(int argc, char const* argv[])
{
	uint8_t u8VehicleInfo[18];
	JT808Header jt808Header;
	jt808Header.Id = htons(35057);
	jt808Header.Body.EncryptedBit = 0;
	jt808Header.Body.LengthFront = 3;
	jt808Header.Body.LengthBack = 0;
	jt808Header.Body.ReservedBit = 0;
	jt808Header.Body.Subcontract = 0;
	jt808Header.No[0] = HexToBcd(0);
	jt808Header.No[1] = HexToBcd(0);
	jt808Header.No[2] = HexToBcd(4);
	jt808Header.No[3] = HexToBcd(3);
	jt808Header.No[4] = HexToBcd(5);
	jt808Header.No[5] = HexToBcd(9);
	jt808Header.Sequence = htons(2313);

	vsnc::vjt::VehicleInfo vehicleInfo;
	vehicleInfo.Speed = htons(60);
	vehicleInfo.Turnsignal = 0x00;
	auto a = sizeof(JT808Header);
	auto b = sizeof(vsnc::vjt::VehicleInfo);
	auto ptr = reinterpret_cast<uint8_t*>(u8VehicleInfo);
	memcpy(ptr + 1, &jt808Header, sizeof(JT808Header));
	memcpy(ptr + 1 + sizeof(JT808Header), &vehicleInfo, sizeof(vsnc::vjt::VehicleInfo));
	u8VehicleInfo[0] = 0x7E;
	u8VehicleInfo[16] = Check(ptr + 1, 15);
	u8VehicleInfo[17] = 0x7E;
	
    //std::string testStr = "7E0200003C064808354296023D0000000000080042021FD9340722758000110260013A17082514425701040004329202020000030200002504000000002B0400000000300111310114777E1C007E";
    //std::vector<uint8_t> testList;
    //for (size_t i = 0; i < testStr.size(); i += 2) {
    //    //std::cout << testStr.substr(i, 2) << std::endl;
    //    auto temp = "0x" + testStr.substr(i, 2);
    //    testList.push_back(static_cast<uint8_t>(std::stoul(temp, 0, 16)));
    //}
    vsnc::vjt::Packet inPacket;
	inPacket.Data = ptr;
    inPacket.Length = 18;
    vsnc::vjt::Packet outPacket;
    auto msg = vsnc::vjt::JTParser(inPacket, outPacket);
	switch (msg)
	{
	case vsnc::vjt::JTMessage::UNKNOWN:
	{
		//TODO
		break;
	}
	case vsnc::vjt::JTMessage::VEHICLEINFO:
	{
		auto pVehicleInfo = reinterpret_cast<vsnc::vjt::VehicleInfo*>(outPacket.Data);

		std::cout << "speed: " << ntohs(pVehicleInfo->Speed) << std::endl;
		std::cout << "pVehicleInfo->Turnsignal: " << pVehicleInfo->Turnsignal<< std::endl;
		break;
	}
	case vsnc::vjt::JTMessage::BRAKESYSTEM:
	{
		break;
	}
	default:
		break;
	}
    return 0;
}