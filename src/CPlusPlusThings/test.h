/**
 * @file test.h
 * @brief 简介
 * @author xzf
 * @version v1
 * @date 2021-10-11
 */

#include <iostream>
#include <vector>
#include <functional>

namespace vsnc
{
	namespace cplus
	{
		//不可以对 alias template做偏特化或全特化
		template <typename T>
		// alias template using新用法
		using Vec = std::vector<T, std::allocator<T>>;
		//# define Vec<T> template<typename T> vector<T, allocator<T>> 使用宏不行

		/// <summary>
		/// 定义callback
		/// </summary>
		typedef void OnRspCallback(std::string, size_t);

		/// <summary>
		/// req请求
		/// </summary>
		using ReqHandler = std::function<bool(std::string, size_t, OnRspCallback)>;

		class FunctionClass
		{
		public:
			FunctionClass() {};
			~FunctionClass() {};
			void PrintFun(ReqHandler req );

		};
	}
}