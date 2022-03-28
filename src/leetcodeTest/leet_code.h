#ifndef __LEET_CODE_H__
#define __LEET_CODE_H__
#include<iostream>
#include<vector>
#include<list>
#include<stack>
#include<set>

namespace vsnc
{
	namespace leet
	{
		class Solution {
		public:
			int search(std::vector<int>& nums, int target) {
				int count = 0;
				for (auto& num : nums) {
					if (num == target) {
						return count;
					}
					count++;
				}
				return -1;
			}
			bool isBadVersion(int n) {
				if (n >= 4) {
					return true;
				}
				return false;
			}
			int firstBadVersion(int n) {
				int left = 0;
				int right = n;
				while (left != right-1) {
					auto temp = left+(right - left) / 2;
					if (isBadVersion(temp)) {
						right = temp;
					}
					else {
						left = temp;
					}
				}
				return right;
			}

			int searchInsert(std::vector<int>& nums, int target) {
				int count = 0;
				for (auto& num : nums) {
					if (num >= target) {
						return count;
					}
					count++;
				}
				return count;
			}
			bool containsDuplicate(std::vector<int>& nums) {
				return std::set<int>(nums.begin(), nums.end()).size() != nums.size();
			}
			std::string replaceSpace(std::string s) {
				std::string temp;
				for (size_t i = 0; i < s.size(); i++) {
					if (s.at(i) == ' ') {
						temp = temp + "%20";
					}
					else {
						temp = temp + s.at(i);
					}
				}
				return temp;
			}
		};

		class CQueue {
		public:
			CQueue() {

			}

			void appendTail(int value) {
				lstStack.push_back(value);
			}

			int deleteHead() {
				if (lstStack.empty()) {
					return -1;
				}
				auto temp = lstStack.front();
				lstStack.pop_front();
				return temp;
			}
		private:
			std::list<int> lstStack;
		};
		class MinStack {
		public:
			/** initialize your data structure here. */
			MinStack() {
				
			}

			void push(int x) {
				ListNode lstNode{x,x};
				if (!lstStack.empty()) 
				{
					if (lstNode.Min > lstStack.top().Min)
					{
						lstNode.Min = lstStack.top().Min;
					}
				}
				lstStack.push(lstNode);
			}

			void pop() {
				
				if (!lstStack.empty())
				{
					lstStack.pop();
				}
			}

			int top() {
				return lstStack.top().Now;
			}

			int min() {
				return lstStack.top().Min;
			}
		private:
			struct ListNode
			{
				int Now;
				int Min;
			};
			std::stack<ListNode> lstStack;
		};
	}
}

#endif // !__LEET_CODE_H__

