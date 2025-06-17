#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <sstream>

// ���ݾɱ�����û�� std::to_string
template <typename T>
std::string to_string(T value) {
    std::ostringstream oss;
    oss << value;
    return oss.str();
}

// ���ɳ���Ϊ n �����Сд��ĸ�ַ���
std::string random_string(int n) {
    std::string s;
    for (int i = 0; i < n * 1024; ++i) {
        char c = 'a' + rand() % 26;
        s += c;
    }
    return s;
}

int main() {
    srand((unsigned)time(0)); // ���������

    int file_count, char_count;
    std::cout << "Ҫ���ɼ����ļ���: ";
    if (!(std::cin >> file_count) || file_count <= 0) return 0;
    std::cout << "ÿ���ļ����ٸ�����ַ���: ";
    if (!(std::cin >> char_count) || char_count <= 0) return 0;

    for (int i = 1; i <= file_count; ++i) {
        std::string filename = "demo_" + to_string(i) + ".txt";
        std::ofstream file(filename.c_str());
        if (!file) {
            std::cout << "�޷������ļ�: " << filename << std::endl;
            continue;
        }
        file << random_string(char_count); // ֻдһ�У�û�л���
        file.close();
        std::cout << "������ " << filename << std::endl;
    }
    std::cout << "ȫ����ɣ�" << std::endl;
    return 0;
}

