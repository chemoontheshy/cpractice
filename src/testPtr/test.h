#ifndef __TEST_H_
#define __TEST_H_
#include <iostream>

namespace vsnc
{
	namespace test
	{
		struct Packet
		{
			uint8_t*	data;
			size_t		length;
		};
		/// <summary>
		/// 产生长度为16-bit 的随机数
		/// </summary>
		/// <returns>长度为16-bit 的随机数</returns>
		uint16_t GetRandomU16();

		/// <summary>
		/// 产生长度为32-bit 的随机数
		/// </summary>
		/// <returns>长度为32-bit 的随机数</returns>
		uint32_t GetRandomU32();

		/// <summary>
		/// 检验帧头
		/// 这里的一帧帧是指由0000001或者00000001开头的帧，可能是完整的一帧也可能是只是一帧的部分
		/// 00000001是一帧的开头
		/// 000001是一帧的部分
		/// 帧头后接一个Nalu
		/// 一帧可能由一个Nula，或者多个Nula组成
		/// </summary>
		/// <param name="packet">传入一帧数据</param>
		/// <returns>正确返回3或者4，错误返回-1</returns>
		int CheckFrameHeader(const Packet& packet);


		

	}

}

#endif // !__TEST_H_
