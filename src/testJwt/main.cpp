#include "base64.h"
#include <iostream>
#include<algorithm>
#include <vector>

static std::string __username = "ivisionic";
static std::string __password = "123456";

int main() {
    const std::string orig = "ivisionic,123456,1637652777";
    std::cout << orig.length() << std::endl;
    std::cout << orig.size() << std::endl;
    std::string encoded = base64_encode(reinterpret_cast<const unsigned char*>(orig.c_str()), orig.length());
    // 二次加密,除了最后一位
    // 前面倒转
    std::reverse(encoded.begin(), encoded.end()-1);
    // 正常解密
    std::string decoded = base64_decode(encoded);
    std::cout << decoded << std::endl;
    // 先解二次加密
    std::reverse(encoded.begin(), encoded.end()-1);
    decoded = base64_decode(encoded);
    std::cout << decoded << std::endl;
    std::vector<std::string> tokenList;
    int num = 0;
    while (num>=0)
    {
        num = decoded.find(",");
        tokenList.push_back(decoded.substr(0, num));
        decoded = decoded.substr(num+1);
    }
    if (tokenList.at(0) != __username || tokenList.at(1) != __password)
    {
        std::cout << "username or password is incorrect" << std::endl;
    }
    int32_t nowtime = static_cast<int32_t>(time(nullptr));
    std::cout << nowtime << std::endl;

    if (static_cast<int32_t>(time(nullptr)) - std::stoi(tokenList.at(2)) > (60 * 30))
    {
        std::cout << "timeout" << std::endl;
    }
    return 0;
}
