/**
 * @File main.cpp
 * @Brief ”√”⁄¡Ÿ ±≤‚ ‘
 * @Author xzf (xzfandzgx@gmal.com)
 * @Contact
 * @Version 1.0
 * @Date 2021-01-14
 * @copyright Copyright (c) 2022
 *
 */
constexpr size_t MAX_SIZE = 20;
using ElemType = size_t;
struct SqList
{
	ElemType data[MAX_SIZE];
	size_t   length;
};

int main()
{
	SqList sqList;
	sqList.data[0] = 4;
	sqList.length = 1;
	return 0;
}