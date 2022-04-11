#include <iostream>

struct Packet
{
	uint8_t* Data;
	size_t   Lenght;

};

class VPacket
{
public:
	//构造函数
	VPacket(const size_t length) { m_iPacket.Data = new uint8_t[length]; m_iPacket.Lenght = length; };
	//默认构造函数
	VPacket() { m_iPacket.Data = new uint8_t[1500]; m_iPacket.Lenght = 1500; }

	//显示拷贝构造函数
	VPacket(const VPacket& packet) { m_iPacket.Data = new uint8_t[packet.m_iPacket.Lenght]; m_iPacket.Lenght = packet.m_iPacket.Lenght; }
	~VPacket()
	{
		std::cout <<"lenght" << m_iPacket.Lenght << std::endl;
		if (m_iPacket.Data) delete m_iPacket.Data;
	}
private:
	Packet m_iPacket;
};

class Animal
{
public:
    //构造函数
	Animal(const std::string& name) :m_sName{ name } {};
	//析构函数
	~Animal() {};
	void Say() { std::cout << "I'm " << m_sName << std::endl; }
private:
	std::string m_sName;
};



class Person
{
public:
	Person(const std::string& name, const size_t age) :m_sName{ name }, m_iAge{ age }{};
	void Introduction() { std::cout << "my name is " << m_sName << " " << m_iAge << "years"<<std::endl; }
	friend void Hello(const Person& preson) noexcept { std::cout << "Hi " << preson.m_sName << std::endl; }
private:
	std::string m_sName;
	size_t      m_iAge;
};

class Polygon
{
public:
	void SetValues(const size_t w, const size_t h) { m_iWidth = w; m_iHeight = h; }
protected:
	size_t m_iWidth;
	size_t m_iHeight;
};

class Rectangle : public Polygon
{
public:
	size_t area() { return m_iWidth * m_iHeight; }
};

class Triangle : public Polygon
{
public:
	size_t area() { return m_iWidth * m_iHeight / 2; }
};

int main()
{
	
	Rectangle rect;
	Triangle tri;
	rect.SetValues(4, 6);
	tri.SetValues(4,6);
	std::cout << rect.area() << std::endl;
	std::cout << tri.area() << std::endl;

	return 0;
}