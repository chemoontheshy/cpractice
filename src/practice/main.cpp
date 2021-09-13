#include <iostream>
#include "mailbox.h"

using namespace std;
using namespace vsnc::bot;

class Add
{
public:
	Add() :m_x(-1), m_y(-1) {};
	Add(int x, int y) :m_x(x), m_y(y) {};
	~Add() {};

	int getSum() { return m_x + m_y; }

	Add operator+(const Add& b)
	{
		Add a;
		a.m_x = this->m_x + b.m_x;
		a.m_y = this->m_y + b.m_y;
		return a;
	}

	Add operator-(const Add& b)
	{
		Add a;
		a.m_x = this->m_x - b.m_x;
		a.m_y = this->m_y - b.m_y;
		return a;
	}

	Add operator&(const Add& b)
	{
		Add a;
		(this->m_x > b.m_x) ? a.m_x = this->m_x : a.m_x = b.m_x;
		(this->m_y > b.m_y) ? a.m_y = this->m_y: a.m_x = b.m_y;
	}


private:
	int m_x;
	int m_y;
};



int main() {
	
	MailBox mailbox;
	MailBox::User f_user;
	f_user.name = "张三";
	f_user.tripcode = "123";
	MailBox::User t_user;
	t_user.name = "李四";
	t_user.tripcode = "1234";
	MailBox::Data data;
	data.from_User = f_user;
	data.to_User = t_user;
	data.message = "你好，李四";
	data.timestamp = 12340;
	data.secret = false;
	int i;
	for(i = 0;i<100;i++)
	{
		if (!mailbox.Send(data)) break;
	}
	cout << i << endl;
	mailbox.Send(data);
	return 0;
}
