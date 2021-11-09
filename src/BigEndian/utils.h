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
			/// <summary>�̶�Ϊ0</summary>
			uint8_t flag : 1;
			/// <summary>NAL Unit</summary>
			uint8_t type : 6;
			/// <summary>������չ����δʹ�ã�Ϊ0��ǰ</summary>
			uint8_t layerId1 : 1;
			/// <summary>������չ����δʹ�ã�Ϊ0����</summary>
			uint8_t layerId2 : 5;
			/// <summary>ʱ��NAL��Ԫ�ı�ʶ��+1</summary>
			uint8_t tid : 3;
#else
			/// <summary>������չ����δʹ�ã�Ϊ0��ǰ</summary>
			uint8_t layerId1: 1;
			/// <summary>NAL Unit</summary>
			uint8_t type : 6;
			/// <summary>�̶�Ϊ0</summary>
			uint8_t flag : 1;
			/// <summary>ʱ��NAL��Ԫ�ı�ʶ��+1</summary>
			uint8_t tid : 3;
			/// <summary>������չ����δʹ�ã�Ϊ0����</summary>
			uint8_t layerId2 : 5;

#endif // RTP_BIG_ENDIAN

		} HEVCIndicator;

		typedef struct HEVCFUHeader
		{
#ifdef RTP_BIG_ENDIAN
			/// <summary>��ʼ��־</summary>
			uint8_t s : 1;
			/// <summary>������־</summary>
			uint8_t e : 1;
			/// <summary>NAL Unit����</summary>
			uint8_t type : 6;
#else
			/// <summary>NAL Unit����</summary>
			uint8_t type : 6;
			/// <summary>������־</summary>
			uint8_t e : 1;
			/// <summary>��ʼ��־</summary>
			uint8_t s : 1;
#endif // RTP_BIG_ENDIAN
		} HEVCFUHeader;
		/// <summary>
		///   ģ��֡
		/// </summary>
		typedef struct VPacket
		{
			uint8_t* Head;
			int Size;
		} VPacket;
		//HEVC fu���
		VPacket unPack(uint8_t* const stream, const int size);
	}

}

#endif // !__UTILS_H_
