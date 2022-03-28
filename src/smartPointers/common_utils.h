#ifndef __COMMON_UTILS_H_
#define __COMMON_UTILS_H_

namespace vscm
{
	namespace utils
	{
		/// <summary>
		/// 线性顺序存储结构需要三个属性
		/// 
		/// </summary>
		struct SqList
		{
			size_t data[20];
			size_t length;
		};


		/// <summary>
		/// 模拟链表
		/// </summary>
		/// <typeparam name="Data">数据类型</typeparam>
		template<typename Data>
		class Vlist
		{
		public:
			/// <summary>
			/// 链表初始化
			/// </summary>
			/// <param name="maxSize">链表存储元素最大值</param>
			/// <returns>成功返回true,错误返回false</returns>
			bool   Init(size_t maxSize);
			/// <summary>
			/// 数据链表是否为空
			/// </summary>
			/// <returns>为空返回true，不为空返回false</returns>
			bool   Empty();
			/// <summary>
			/// 清空链表
			/// </summary>
			void   Clear();
			/// <summary>
			/// 获取链表当前位置n的元素值
			/// </summary>
			/// <param name="n">链表当前位置n</param>
			/// <returns>链表当前位置n的元素值</returns>
			Data   GetElem(size_t n);
			/// <summary>
			/// 在链表中查找与给定值data相等的元素
			/// </summary>
			/// <param name="data">需要查找的参数</param>
			/// <returns>如果查找成功返回该元素的在表中的序号表示成功；否则，返回0表示失败。</returns>
			size_t LocateElem(Data data);
			/// <summary>
			/// 插入新元素data
			/// </summary>
			/// <param name="n">插入位置</param>
			/// <param name="data">插入元素值</param>
			/// <returns>成功返回true,插入失败返回false</returns>
			bool   Insert(size_t n, Data data);
			/// <summary>
			/// 删除n位置的元素值
			/// </summary>
			/// <param name="n">位置（下标）</param>
			/// <returns>成功返回true，失败返回false</returns>
			bool   Delete(size_t n);
			/// <summary>
			/// 链表含有元素的个数
			/// </summary>
			/// <returns>返回</returns>
			size_t Length();
		};
	}
}

#endif // !__COMMON_UTILS_H_

