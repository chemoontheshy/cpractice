#include "JT808Parser.h"
#include <vector>
#include<WinSock2.h>

using namespace vsnc::vjt;

namespace vsnc
{
	namespace vjt
	{

		//转义相关标识符protocolEscapeFlag
		/// <summary> 标识位 </summary>
		static constexpr uint8_t PROTOCOL_SIGN = 0x7E;
		/// <summary> 转义标识位 </summary>
		static constexpr uint8_t PROTOCOL_ESCAPE = 0x7D;
		/// <summary> 0x7E<-->0x7D后紧跟一个0x02 </summary>
		static constexpr uint8_t PROTOCOL_ESCAPE_SIGN = 0x02;
		/// <summary> 0x7D<-->0x7D后紧跟一个0x01 </summary>
		static constexpr uint8_t PROTOCOL_ESCAPE_ESCAPE = 0x01;

		/// <summary> 上位机下发车辆信息 </summary>
		static constexpr uint16_t VEHICLEINFO = 0x88F1;
		/// <summary> 上位机下发车辆信息 </summary>
		static constexpr uint16_t BRAKESYSTEM = 0x08B1;

		/// <summary>
		/// 消息体属性为2字节
		/// </summary>
		typedef struct JT808Body
		{
#ifdef __BIGENDIAN_
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
#else
			/// <summary>长度前</summary>
			uint8_t   LengthFront;

			/// <summary>保留位</summary>
			uint8_t   ReservedBit : 2;
			/// <summary>分包标识符识符，为1为长消息，分包，为0不分包</summary>
			uint8_t   Subcontract : 1;
			/// <summary>加密标识符：001为RSA加密，000不加密</summary>
			uint8_t   EncryptedBit : 3;
			/// <summary>长度后</summary>
			uint8_t   LengthBack : 2;

#endif // !__BIGENDIAN_
		}JT808Body;

		/// <summary>
		/// 消息头为12字节，（包含消息体属性2字节）
		/// </summary>
		typedef struct JT808Header
		{
			/// <summary>消息ID</summary>
			uint16_t  Id;
			/// <summary>消息体属性ID</summary>
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




		/// <summary>
		/// 转义还原
		/// </summary>
		/// <param name="data">去掉标识位的数据包头指针</param>
		/// <param name="length">去掉标识位的数据包长度</param>
		/// <returns>以vector数组的形式返回转义还原后的数据包</returns>
		static std::vector<uint8_t> __escape(const uint8_t* data, const size_t& length) noexcept;

		/// <summary>
		/// 计算校验码
		/// </summary>
		/// <param name="data">转义后的数据包头指针</param>
		/// <param name="length">转义后的数据包长度</param>
		/// <returns>异或得到的校验码</returns>
		static uint8_t __check(const uint8_t* data, const size_t& length) noexcept;

		/// <summary>
		/// BCD码转16进制
		/// </summary>
		/// <param name="src">BCD码</param>
		/// <returns>16进制</returns>
		static uint8_t __bcd_to_hex(uint8_t const& src);

	}
}

uint8_t vsnc::vjt::__bcd_to_hex(uint8_t const& src)
{
	uint8_t temp;
	temp = (src >> 4) * 10 + (src & 0x0f);
	return uint8_t();
}

std::vector<uint8_t> vsnc::vjt::__escape(const uint8_t* data, const size_t& length) noexcept
{
	std::vector<uint8_t> escapeList;
	for (size_t i = 0; i < length; ++i) {
		if (*data == PROTOCOL_ESCAPE) {
			if (*(data + 1) == PROTOCOL_ESCAPE_ESCAPE) {
				escapeList.push_back(PROTOCOL_ESCAPE);
			}
			else if (*(data + 1) == PROTOCOL_ESCAPE_SIGN) {
				escapeList.push_back(PROTOCOL_SIGN);
			}
			i++;
			data++;
		}
		else {
			escapeList.push_back(*data);
		}
		data++;
	}
	return escapeList;
}

uint8_t vsnc::vjt::__check(const uint8_t* data, const size_t& length) noexcept
{
	uint8_t checkSum = 0;
	for (size_t i = 0; i < length; ++i) {
		checkSum = checkSum ^ *data;
		data++;
	}
	return checkSum;
}

JTMessage vsnc::vjt::JTParser(const Packet& originalPacket, Packet& messagePacket) noexcept
{
	//如果指针为空或者少于14个字节的消息头直接返回(包含前后各一个字节的标记位)
	/*if (!originalPacket.Data || originalPacket.Length < 14) {
		return JTMessage::UNKNOWN;
	}*/
	// 1.去掉标识符，同时转义还原
	auto temp = __escape(originalPacket.Data + 1, originalPacket.Length - 2);
	if (temp.empty()) {
		return JTMessage::UNKNOWN;
	}
	// 2.验证校验码
	auto checkSum = __check(&temp.front(), temp.size());
	if (checkSum != temp.at(temp.size() - 2)) {
		std::cout << "false" << std::endl;
		return JTMessage::UNKNOWN;
	}
	auto data = &temp.at(0);
	auto length = temp.size();
	// 3.获取消息头结构体
	auto jt808Header = reinterpret_cast<JT808Header*>(data);
	jt808Header->Id = ntohs(jt808Header->Id);
	jt808Header->Sequence = ntohs(jt808Header->Sequence);

	// 4.默认不分包，如果分包理论不在车辆信息和刹车系统信息中。直接返回未知枚举
	if (jt808Header->Body.Subcontract) {
		return JTMessage::UNKNOWN;
	}
	// 5.去掉标识位和消息头
	data += 12;
	length -= 13;
	// 如果是车辆信息返回车辆信息枚举
	if (jt808Header->Id == VEHICLEINFO) {
		// 去掉消息头
		auto vehicleInfo = reinterpret_cast<VehicleInfo*>(data);
		// 大端转小端。
		vehicleInfo->Speed = ntohs(vehicleInfo->Speed);
		// 使用原来的传进来的内存，否则函数销毁时，就会销毁。
		memcpy(originalPacket.Data, vehicleInfo, length);
		messagePacket.Data = originalPacket.Data;
		// 去掉消息头长度和校验码
		messagePacket.Length = length;

		return JTMessage::VEHICLEINFO;
	}
	// 如果是车辆信息返回车辆信息枚举
	if (jt808Header->Id == BRAKESYSTEM) {
		auto brakeSystem = reinterpret_cast<Brakesystem*>(data);
		brakeSystem->Distance = ntohs(brakeSystem->Speed);
		// 使用原来的传进来的内存，否则函数销毁时，就会销毁。
		memcpy(originalPacket.Data, brakeSystem, length);
		messagePacket.Data = originalPacket.Data;
		// 去掉消息头长度和校验码
		messagePacket.Length = length;
		return JTMessage::BRAKESYSTEM;
	}
	// 其他不分析，直接返回未知枚举
	return JTMessage::UNKNOWN;
}
