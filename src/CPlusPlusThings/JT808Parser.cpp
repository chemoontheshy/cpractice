#include "JT808Parser.h"
#include <vector>
#include<WinSock2.h>

using namespace vsnc::vjt;

namespace vsnc
{
	namespace vjt
	{

		//ת����ر�ʶ��protocolEscapeFlag
		/// <summary> ��ʶλ </summary>
		static constexpr uint8_t PROTOCOL_SIGN = 0x7E;
		/// <summary> ת���ʶλ </summary>
		static constexpr uint8_t PROTOCOL_ESCAPE = 0x7D;
		/// <summary> 0x7E<-->0x7D�����һ��0x02 </summary>
		static constexpr uint8_t PROTOCOL_ESCAPE_SIGN = 0x02;
		/// <summary> 0x7D<-->0x7D�����һ��0x01 </summary>
		static constexpr uint8_t PROTOCOL_ESCAPE_ESCAPE = 0x01;

		/// <summary> ��λ���·�������Ϣ </summary>
		static constexpr uint16_t VEHICLEINFO = 0x88F1;
		/// <summary> ��λ���·�������Ϣ </summary>
		static constexpr uint16_t BRAKESYSTEM = 0x08B1;

		/// <summary>
		/// ��Ϣ������Ϊ2�ֽ�
		/// </summary>
		typedef struct JT808Body
		{
#ifdef __BIGENDIAN_
			/// <summary>����ǰ</summary>
			uint8_t   LengthFront;
			/// <summary>���Ⱥ�</summary>
			uint8_t   LengthBack : 2;
			/// <summary>���ܱ�ʶ����001ΪRSA���ܣ�000������</summary>
			uint8_t   EncryptedBit : 3;
			/// <summary>�ְ���ʶ��ʶ����Ϊ1Ϊ����Ϣ���ְ���Ϊ0���ְ�</summary>
			uint8_t   Subcontract : 1;
			/// <summary>����λ</summary>
			uint8_t   ReservedBit : 2;
#else
			/// <summary>����ǰ</summary>
			uint8_t   LengthFront;

			/// <summary>����λ</summary>
			uint8_t   ReservedBit : 2;
			/// <summary>�ְ���ʶ��ʶ����Ϊ1Ϊ����Ϣ���ְ���Ϊ0���ְ�</summary>
			uint8_t   Subcontract : 1;
			/// <summary>���ܱ�ʶ����001ΪRSA���ܣ�000������</summary>
			uint8_t   EncryptedBit : 3;
			/// <summary>���Ⱥ�</summary>
			uint8_t   LengthBack : 2;

#endif // !__BIGENDIAN_
		}JT808Body;

		/// <summary>
		/// ��ϢͷΪ12�ֽڣ���������Ϣ������2�ֽڣ�
		/// </summary>
		typedef struct JT808Header
		{
			/// <summary>��ϢID</summary>
			uint16_t  Id;
			/// <summary>��Ϣ������ID</summary>
			JT808Body Body;
			/// <summary>�豸��</summary>
			uint8_t   No[6];
			/// <summary>��Ϣ��ˮ��</summary>
			uint16_t  Sequence;
		}JT808Header;

		/// <summary>
		/// ��Ϣ����װ����ְ���ʶ��Ϊ1��ʱ������Ϣ����װ�Ϊ0����û��
		/// </summary>
		typedef struct JTPacketItem
		{
			/// <summary>��Ϣ�ܰ���</summary>
			uint16_t Total;
			/// <summary>�����</summary>
			uint16_t PacketSequence;
		}JTPacketItem;




		/// <summary>
		/// ת�廹ԭ
		/// </summary>
		/// <param name="data">ȥ����ʶλ�����ݰ�ͷָ��</param>
		/// <param name="length">ȥ����ʶλ�����ݰ�����</param>
		/// <returns>��vector�������ʽ����ת�廹ԭ������ݰ�</returns>
		static std::vector<uint8_t> __escape(const uint8_t* data, const size_t& length) noexcept;

		/// <summary>
		/// ����У����
		/// </summary>
		/// <param name="data">ת�������ݰ�ͷָ��</param>
		/// <param name="length">ת�������ݰ�����</param>
		/// <returns>���õ���У����</returns>
		static uint8_t __check(const uint8_t* data, const size_t& length) noexcept;

		/// <summary>
		/// BCD��ת16����
		/// </summary>
		/// <param name="src">BCD��</param>
		/// <returns>16����</returns>
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
	//���ָ��Ϊ�ջ�������14���ֽڵ���Ϣͷֱ�ӷ���(����ǰ���һ���ֽڵı��λ)
	/*if (!originalPacket.Data || originalPacket.Length < 14) {
		return JTMessage::UNKNOWN;
	}*/
	// 1.ȥ����ʶ����ͬʱת�廹ԭ
	auto temp = __escape(originalPacket.Data + 1, originalPacket.Length - 2);
	if (temp.empty()) {
		return JTMessage::UNKNOWN;
	}
	// 2.��֤У����
	auto checkSum = __check(&temp.front(), temp.size());
	if (checkSum != temp.at(temp.size() - 2)) {
		std::cout << "false" << std::endl;
		return JTMessage::UNKNOWN;
	}
	auto data = &temp.at(0);
	auto length = temp.size();
	// 3.��ȡ��Ϣͷ�ṹ��
	auto jt808Header = reinterpret_cast<JT808Header*>(data);
	jt808Header->Id = ntohs(jt808Header->Id);
	jt808Header->Sequence = ntohs(jt808Header->Sequence);

	// 4.Ĭ�ϲ��ְ�������ְ����۲��ڳ�����Ϣ��ɲ��ϵͳ��Ϣ�С�ֱ�ӷ���δ֪ö��
	if (jt808Header->Body.Subcontract) {
		return JTMessage::UNKNOWN;
	}
	// 5.ȥ����ʶλ����Ϣͷ
	data += 12;
	length -= 13;
	// ����ǳ�����Ϣ���س�����Ϣö��
	if (jt808Header->Id == VEHICLEINFO) {
		// ȥ����Ϣͷ
		auto vehicleInfo = reinterpret_cast<VehicleInfo*>(data);
		// ���תС�ˡ�
		vehicleInfo->Speed = ntohs(vehicleInfo->Speed);
		// ʹ��ԭ���Ĵ��������ڴ棬����������ʱ���ͻ����١�
		memcpy(originalPacket.Data, vehicleInfo, length);
		messagePacket.Data = originalPacket.Data;
		// ȥ����Ϣͷ���Ⱥ�У����
		messagePacket.Length = length;

		return JTMessage::VEHICLEINFO;
	}
	// ����ǳ�����Ϣ���س�����Ϣö��
	if (jt808Header->Id == BRAKESYSTEM) {
		auto brakeSystem = reinterpret_cast<Brakesystem*>(data);
		brakeSystem->Distance = ntohs(brakeSystem->Speed);
		// ʹ��ԭ���Ĵ��������ڴ棬����������ʱ���ͻ����١�
		memcpy(originalPacket.Data, brakeSystem, length);
		messagePacket.Data = originalPacket.Data;
		// ȥ����Ϣͷ���Ⱥ�У����
		messagePacket.Length = length;
		return JTMessage::BRAKESYSTEM;
	}
	// ������������ֱ�ӷ���δ֪ö��
	return JTMessage::UNKNOWN;
}
