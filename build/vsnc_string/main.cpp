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
		//重载运输符
		class CVector
		{
		public:
			CVector():
				m_iX{ 0 },
				m_iY{ 0 }{ n++; }
			CVector(size_t x, size_t y) :
				m_iX{x}, 
				m_iY{y}{ n++; }
			CVector operator + (const CVector& param);
			size_t GetX() { return m_iX; }
			size_t GetY() { return m_iY; }
			static size_t n;
		private:
			size_t m_iX;
			size_t m_iY;
		};

	}
}

size_t vsnc::test::CVector::n = 0;

int main()
{
#ifdef UNIQUE_RESET
	std::unique_ptr<vsnc::test::Student> student;
	student = std::make_unique<vsnc::test::Student>("Tom", 12);
	student->SelfIntroduction();
	std::cout << student.get() << std::endl;
	student.reset();
	student = std::make_unique<vsnc::test::Student>("chenmo", 25);
	student->SelfIntroduction();
	std::cout << student.get() << std::endl;

	student.reset();
#endif // UNIQUE_RESET

	vsnc::test::CVector foo{ 4,2 };
	vsnc::test::CVector bar{ 1,8 };
	auto result = foo + bar;
	std::cout << "x: " << result.GetX() << std::endl;
	std::cout << "y: " << result.GetY() << std::endl;
	std::cout << "n: " << bar.n << std::endl;
	return 0;
}

vsnc::test::CVector vsnc::test::CVector::operator+(const CVector& param)
{
	CVector temp;
	temp.m_iX = this->m_iX + param.m_iX;
	temp.m_iY = this->m_iY + param.m_iY;
	return temp;
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