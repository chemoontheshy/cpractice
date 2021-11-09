#ifndef __UTILS_H_
#define __UTILS_H_
#include <iostream>

namespace vsnc
{
	namespace vweb
	{
		typedef struct HEVCIndicator
		{
#ifdef RTP_BIG_ENDIAN
			/// <summary>固定为0</summary>
			uint8_t flag : 1;
			/// <summary>NAL Unit</summary>
			uint8_t type : 6;
			/// <summary>用于拓展，暂未使用，为0，前</summary>
			uint8_t layerId1 : 1;
			/// <summary>用于拓展，暂未使用，为0，后</summary>
			uint8_t layerId2 : 5;
			/// <summary>时间NAL单元的标识符+1</summary>
			uint8_t tid : 3;
#else
			/// <summary>用于拓展，暂未使用，为0，前</summary>
			uint8_t layerId1: 1;
			/// <summary>NAL Unit</summary>
			uint8_t type : 6;
			/// <summary>固定为0</summary>
			uint8_t flag : 1;
			/// <summary>时间NAL单元的标识符+1</summary>
			uint8_t tid : 3;
			/// <summary>用于拓展，暂未使用，为0，后</summary>
			uint8_t layerId2 : 5;

#endif // RTP_BIG_ENDIAN

		} HEVCIndicator;

		typedef struct HEVCFUHeader
		{
#ifdef RTP_BIG_ENDIAN
			/// <summary>开始标志</summary>
			uint8_t s : 1;
			/// <summary>结束标志</summary>
			uint8_t e : 1;
			/// <summary>NAL Unit类型</summary>
			uint8_t type : 6;
#else
			/// <summary>NAL Unit类型</summary>
			uint8_t type : 6;
			/// <summary>结束标志</summary>
			uint8_t e : 1;
			/// <summary>开始标志</summary>
			uint8_t s : 1;
#endif // RTP_BIG_ENDIAN
		} HEVCFUHeader;
		/// <summary>
		///   模拟帧
		/// </summary>
		typedef struct VPacket
		{
			uint8_t* Head;
			int Size;
		} VPacket;
		//HEVC fu解包
		VPacket unPack(uint8_t* const stream, const int size);
	}

}

#endif // !__UTILS_H_
