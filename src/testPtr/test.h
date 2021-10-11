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
		/// ��������Ϊ16-bit �������
		/// </summary>
		/// <returns>����Ϊ16-bit �������</returns>
		uint16_t GetRandomU16();

		/// <summary>
		/// ��������Ϊ32-bit �������
		/// </summary>
		/// <returns>����Ϊ32-bit �������</returns>
		uint32_t GetRandomU32();

		/// <summary>
		/// ����֡ͷ
		/// �����һ֡֡��ָ��0000001����00000001��ͷ��֡��������������һ֡Ҳ������ֻ��һ֡�Ĳ���
		/// 00000001��һ֡�Ŀ�ͷ
		/// 000001��һ֡�Ĳ���
		/// ֡ͷ���һ��Nalu
		/// һ֡������һ��Nula�����߶��Nula���
		/// </summary>
		/// <param name="packet">����һ֡����</param>
		/// <returns>��ȷ����3����4�����󷵻�-1</returns>
		int CheckFrameHeader(const Packet& packet);


		

	}

}

#endif // !__TEST_H_
