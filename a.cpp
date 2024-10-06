#include <iostream>
#include <openssl/evp.h> // 使用EVP接口
#include <iomanip>
#include <sstream>

// 使用EVP接口计算SHA-256哈希值的函数
std::string sha256(const std::string& input) {
    EVP_MD_CTX* context = EVP_MD_CTX_new();               // 创建EVP上下文
    const EVP_MD* md = EVP_sha256();                      // 使用SHA-256算法
    unsigned char hash[EVP_MAX_MD_SIZE];                  // 存储哈希值
    unsigned int lengthOfHash = 0;                        // 实际哈希长度

    EVP_DigestInit_ex(context, md, nullptr);              // 初始化上下文
    EVP_DigestUpdate(context, input.c_str(), input.size()); // 更新输入数据
    EVP_DigestFinal_ex(context, hash, &lengthOfHash);     // 获取最终哈希值

    EVP_MD_CTX_free(context);                             // 释放EVP上下文

    // return toHexString(hash, lengthOfHash);               // 返回十六进制哈希字符串

    std::stringstream ss;
    for (size_t i = 0; i < lengthOfHash; ++i) {
        ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(hash[i]);
    }
    return ss.str();
}

int main() {
    std::string input = "22307130440";  // 你想要加密的数字
    std::string hash = sha256(input);

    std::cout << "Input: " << input << std::endl;
    std::cout << "SHA-256 Hash: " << hash << std::endl;

    return 0;
}
