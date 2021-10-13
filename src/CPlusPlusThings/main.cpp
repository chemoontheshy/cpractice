/**
 * @file main.cpp
 * @brief 调用验证的主函数
 * @author xzf
 * @version v1
 * @date 2021-10-11
 */
#include "test.h"


void callback(std::string name, size_t age)
{
    std::cout << name << " " << age << std::endl;
}

bool fun(std::string name, size_t age, vsnc::cplus::OnRspCallback req_callback)
{
    req_callback(name, age);
    return true;
}

class A{};

int main(int argc, char const* argv[])
{
    A a;
    std::cout << sizeof(a) << std::endl;
    return 0;
}