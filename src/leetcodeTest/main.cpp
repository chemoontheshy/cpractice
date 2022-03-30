#include "leet_code.h"

struct Test
{
	int A;
};

int main()
{
	std::unique_ptr<Test> test;
	test = new struct Test();


	std::vector<int> nums = { -1, 0, 3, 5, 9, 12 };
	int target = 6;
	vsnc::leet::Solution solution;
	auto temp = solution.searchInsert(nums, target);
	std::cout << temp << std::endl;
	vsnc::leet::CQueue cQueue;
	std::cout << cQueue.deleteHead() << std::endl;
	vsnc::leet::MinStack minStack;
	minStack.push(-2);
	minStack.push(0);
	minStack.push(-3);
	std::cout << minStack.min() << std::endl;
	minStack.pop();
	std::cout << minStack.top() << std::endl;
	std::cout << minStack.min() << std::endl;
	return 0;
}