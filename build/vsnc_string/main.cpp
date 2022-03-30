#include <iostream>

namespace vsnc
{
	namespace test
	{
		void __get_ip();

		class Student
		{
		public:
			Student(const std::string& name, const size_t age) :m_sName(name),m_iAge(age){}
			void SelfIntroduction() noexcept { std::cout << "my name is " << m_sName <<", "<<m_iAge<< " years old"<<std::endl; }
		private:
			std::string m_sName;
			size_t      m_iAge;
		};
	}
}


int main()
{
	std::unique_ptr<vsnc::test::Student> student;
	student = std::make_unique<vsnc::test::Student>("Tom", 12);
	student->SelfIntroduction();
	std::cout << student.get() << std::endl;
	student.reset();
	student = std::make_unique<vsnc::test::Student>("chenmo", 25);
	student->SelfIntroduction();
	std::cout << student.get() << std::endl;

	student.reset();
	return 0;
}

void vsnc::test::__get_ip()
{
	auto __get_ip = [](const std::string& url, std::string& ip)->bool
	{
		std::string temp;
		if (url.find("rtsp://") == std::string::npos) return false;
		temp = url.substr(7);
		//有后缀的时候
		auto ret = temp.find("/");
		if (ret != std::string::npos)
		{
			temp = temp.substr(0, ret);
		}
		if (temp.find("@") != std::string::npos)
		{
			ret = temp.rfind("@");
			if (ret != std::string::npos)
			{
				temp = temp.substr(ret + 1);
			}
		}
		ip = temp;
		return true;
	};

	std::string rtsp = "rtsp://192.168.31.62/11";
	std::string ip;
	if (!__get_ip(rtsp, ip))
		std::cout << "error" << std::endl;
	std::cout << ip << std::endl;
}