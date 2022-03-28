#ifndef __COMMON_UTILS_H_
#define __COMMON_UTILS_H_

namespace vscm
{
	namespace utils
	{
		/// <summary>
		/// ����˳��洢�ṹ��Ҫ��������
		/// 
		/// </summary>
		struct SqList
		{
			size_t data[20];
			size_t length;
		};


		/// <summary>
		/// ģ������
		/// </summary>
		/// <typeparam name="Data">��������</typeparam>
		template<typename Data>
		class Vlist
		{
		public:
			/// <summary>
			/// �����ʼ��
			/// </summary>
			/// <param name="maxSize">����洢Ԫ�����ֵ</param>
			/// <returns>�ɹ�����true,���󷵻�false</returns>
			bool   Init(size_t maxSize);
			/// <summary>
			/// ���������Ƿ�Ϊ��
			/// </summary>
			/// <returns>Ϊ�շ���true����Ϊ�շ���false</returns>
			bool   Empty();
			/// <summary>
			/// �������
			/// </summary>
			void   Clear();
			/// <summary>
			/// ��ȡ����ǰλ��n��Ԫ��ֵ
			/// </summary>
			/// <param name="n">����ǰλ��n</param>
			/// <returns>����ǰλ��n��Ԫ��ֵ</returns>
			Data   GetElem(size_t n);
			/// <summary>
			/// �������в��������ֵdata��ȵ�Ԫ��
			/// </summary>
			/// <param name="data">��Ҫ���ҵĲ���</param>
			/// <returns>������ҳɹ����ظ�Ԫ�ص��ڱ��е���ű�ʾ�ɹ������򣬷���0��ʾʧ�ܡ�</returns>
			size_t LocateElem(Data data);
			/// <summary>
			/// ������Ԫ��data
			/// </summary>
			/// <param name="n">����λ��</param>
			/// <param name="data">����Ԫ��ֵ</param>
			/// <returns>�ɹ�����true,����ʧ�ܷ���false</returns>
			bool   Insert(size_t n, Data data);
			/// <summary>
			/// ɾ��nλ�õ�Ԫ��ֵ
			/// </summary>
			/// <param name="n">λ�ã��±꣩</param>
			/// <returns>�ɹ�����true��ʧ�ܷ���false</returns>
			bool   Delete(size_t n);
			/// <summary>
			/// ������Ԫ�صĸ���
			/// </summary>
			/// <returns>����</returns>
			size_t Length();
		};
	}
}

#endif // !__COMMON_UTILS_H_

