#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <sstream>

// 兼容旧编译器没有 std::to_string
template <typename T>
std::string to_string(T value) {
    std::ostringstream oss;
    oss << value;
    return oss.str();
}

// 生成长度为 n 的随机小写字母字符串
std::string random_string(int n) {
    std::string s;
    for (int i = 0; i < n * 1024; ++i) {
        char c = 'a' + rand() % 26;
        s += c;
    }
    return s;
}

int main() {
    srand((unsigned)time(0)); // 随机数种子

    int file_count, char_count;
    std::cout << "要生成几个文件？: ";
    if (!(std::cin >> file_count) || file_count <= 0) return 0;
    std::cout << "每个文件多少个随机字符？: ";
    if (!(std::cin >> char_count) || char_count <= 0) return 0;

    for (int i = 1; i <= file_count; ++i) {
        std::string filename = "demo_" + to_string(i) + ".txt";
        std::ofstream file(filename.c_str());
        if (!file) {
            std::cout << "无法创建文件: " << filename << std::endl;
            continue;
        }
        file << random_string(char_count); // 只写一行，没有换行
        file.close();
        std::cout << "已生成 " << filename << std::endl;
    }
    std::cout << "全部完成！" << std::endl;
    return 0;
}

