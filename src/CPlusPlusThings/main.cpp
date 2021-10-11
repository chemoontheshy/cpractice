/**
 * @file main.cpp
 * @brief 调用验证的主函数
 * @author xzf
 * @version v1
 * @date 2021-10-11
 */
#include "test.h"


bool fun(std::string name, size_t age, vsnc::cplus::OnRspCallback req_callback)
{
    req_callback("taka", 19);
    return true;
}
int main(int argc, char const* argv[])
{

    vsnc::cplus::FunctionClass funClass;
    funClass.PrintFun(fun);
    return 0;
}