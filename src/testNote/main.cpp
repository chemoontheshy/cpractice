#include <iostream>
#include <list>

size_t test(const std::list<size_t>& lstNum, const size_t& w)
{
	std::list<size_t> lstBigNum;
	for (const auto& num : lstNum)
	{
		if (num > w)
		{
			lstBigNum.push_back(num);
		}
	}
	//≈≈–Ú

}

int main()
{

}