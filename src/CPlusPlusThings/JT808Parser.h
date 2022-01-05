#ifndef __STRUCTURER_H__
#define __STRUCTURER_H__
#include <iostream>

namespace vsnc
{
	namespace vjt
	{
		/// <summary>
		/// ԭʼ���ݰ�
		/// </summary>
		typedef struct Packet
		{
			/// <summary>ԭʼ����ָ��ͷ</summary>
			uint8_t*  Data;
			/// <summary>ԭʼ���ݳ���</summary>
			size_t    Length;
		}Packet;

		/// <summary>
		/// �ϻ�λ�·�������Ϣ
		/// ��ϢID:0x88F1
		/// </summary>
		typedef struct VehicleInfo
		{
			/// <summary>�ٶȣ�����Km/h</summary>
			uint16_t Speed;
			/// <summary>ת��ƣ�0x00������0x01��ת�������0x02��ת�������</summary>
			uint8_t  Turnsignal;
			
		}VehicleInfo;

		/// <summary>
		/// ɲ��ϵͳ��Ϣ��������Ϣ
		/// ��ϢID:0x08B1
		/// </summary>
		typedef struct Brakesystem
		{
			/// <summary>�ٶ�0~255������Km/h</summary>
			uint8_t  Speed;
			/// <summary>��ײʱ�䣬1/10�룬eg: 0x48 ����7.2��</summary>
			uint8_t  CollisionTime;
			/// <summary>ǰ��Զ�룬0x00������0x01ǰ��Զ�룬��ʾǰ��</summary>
			uint8_t  KeepAway;
			/// <summary>
			/// �����ź�
			/// 0x00 ����
			/// 0x01 ���ˣ�����Զ
			/// 0x02 ���ˣ������
			/// 0x03 �����г�������Զ
			/// 0x04 �����г��������
			/// </summary>
			uint8_t  Pedestrian;
			/// <summary>
			/// ״̬��Ϣ
			/// 0~8λ
			/// 0λ��1Ϊ��ƿ���0Ϊ������
			/// 1λ��1Ϊ�ҵƿ���0Ϊ������
			/// 2λ��1Ϊ��������0Ϊ������
			/// </summary>
			uint8_t  State;
			/// <summary>���룬����ǰ���������롣��λ�ף�m��</summary>
			uint16_t Distance;
			/// <summary>2Dbox��X,Y,WIDTH,HEIGHT</summary>
			uint8_t  Box[4];
			
		}Brakesystem;

		/// <summary>
		/// ��Ϣ����
		/// </summary>
		enum class JTMessage
		{
			/// <summary>����</summary>
			UNKNOWN,
			/// <summary>������Ϣ</summary>
			VEHICLEINFO,
			/// <summary>ɲ��ϵͳ��Ϣ</summary>
			BRAKESYSTEM
		};

		/// <summary>
		///  ԭʼ���ݰ�������������Ҫ����ת�廹ԭ����֤У���룬����м��ܻ���Ҫ�������ܣ�
		/// </summary>
		/// <param name="originalPacket">���룺ԭʼ���ݰ�</param>
		/// <param name="messagePacket">�������Ϣ���ݰ���ȥ����Ϣͷ����������Ϣ���Ϳ���ת���ɲ�ͬ��Ϣ���͵Ľṹ��</param>
		/// <returns>��Ϣ����</returns>
		JTMessage JTParser(const Packet& originalPacket, Packet& messagePacket) noexcept;

	}
}



#endif // !__STRUCTURER_H__
