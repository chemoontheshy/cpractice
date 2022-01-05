#ifndef __STRUCTURER_H__
#define __STRUCTURER_H__
#include <iostream>

namespace vsnc
{
	namespace vjt
	{
		/// <summary>
		/// 原始数据包
		/// </summary>
		typedef struct Packet
		{
			/// <summary>原始数据指针头</summary>
			uint8_t*  Data;
			/// <summary>原始数据长度</summary>
			size_t    Length;
		}Packet;

		/// <summary>
		/// 上机位下发车辆信息
		/// 消息ID:0x88F1
		/// </summary>
		typedef struct VehicleInfo
		{
			/// <summary>速度，整形Km/h</summary>
			uint16_t Speed;
			/// <summary>转向灯，0x00正常，0x01左转向灯亮，0x02右转向灯亮，</summary>
			uint8_t  Turnsignal;
			
		}VehicleInfo;

		/// <summary>
		/// 刹车系统消息体数据信息
		/// 消息ID:0x08B1
		/// </summary>
		typedef struct Brakesystem
		{
			/// <summary>速度0~255，整形Km/h</summary>
			uint8_t  Speed;
			/// <summary>碰撞时间，1/10秒，eg: 0x48 就是7.2秒</summary>
			uint8_t  CollisionTime;
			/// <summary>前车远离，0x00正常，0x01前车远离，提示前进</summary>
			uint8_t  KeepAway;
			/// <summary>
			/// 行人信号
			/// 0x00 正常
			/// 0x01 有人，距离远
			/// 0x02 有人，距离近
			/// 0x03 有自行车，距离远
			/// 0x04 有自行车，距离近
			/// </summary>
			uint8_t  Pedestrian;
			/// <summary>
			/// 状态信息
			/// 0~8位
			/// 0位：1为左灯开，0为正常。
			/// 1位：1为右灯开，0为正常。
			/// 2位：1为倒车档，0为正常。
			/// </summary>
			uint8_t  State;
			/// <summary>距离，距离前方车辆距离。单位米（m）</summary>
			uint16_t Distance;
			/// <summary>2Dbox，X,Y,WIDTH,HEIGHT</summary>
			uint8_t  Box[4];
			
		}Brakesystem;

		/// <summary>
		/// 信息类型
		/// </summary>
		enum class JTMessage
		{
			/// <summary>不明</summary>
			UNKNOWN,
			/// <summary>车辆信息</summary>
			VEHICLEINFO,
			/// <summary>刹车系统信息</summary>
			BRAKESYSTEM
		};

		/// <summary>
		///  原始数据包解析（里面需要包含转义还原，验证校验码，如果有加密还需要解析加密）
		/// </summary>
		/// <param name="originalPacket">输入：原始数据包</param>
		/// <param name="messagePacket">输出：消息数据包（去掉消息头），根据消息类型可以转换成不同信息类型的结构体</param>
		/// <returns>信息类型</returns>
		JTMessage JTParser(const Packet& originalPacket, Packet& messagePacket) noexcept;

	}
}



#endif // !__STRUCTURER_H__
