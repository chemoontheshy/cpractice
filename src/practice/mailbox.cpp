#include "mailbox.h"
#include <iostream>

bool vsnc::bot::MailBox::Send(Data data)
{
	if (toLists.empty())
	{
		To to;
		to.to_User = data.to_User;
		to.dataList.push_back(data);
		toLists.push_back(to);
		return true;
	}
	for (auto tolist : toLists)
	{
		if (tolist.to_User.name == data.to_User.name)
		{
			if (tolist.dataList.size() >= maxSize) return false;
			std::cout << tolist.dataList.size() << std::endl;
			tolist.dataList.push_back(data);
			break;
		}
	}
	return true;
}

void vsnc::bot::MailBox::Read(User user, int num)
{
	if (num > maxSize) {

	}

	for (auto tolist : toLists)
	{
		if (tolist.to_User == user) 
		{
			int m = 1;
			for (auto msg : tolist.dataList)
			{
				if (m == num) {
					std::cout << msg.message << std::endl;
				}
			}
		}
	}
}

int vsnc::bot::MailBox::check_full()
{
	return 0;
}
