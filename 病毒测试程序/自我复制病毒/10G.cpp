#include <fstream>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <sstream>

std::string random_string(int n) {
    std::string s;
    for (int i = 0; i < n; ++i) s += ('a' + rand() % 26);
    return s;
}

int main() {
    srand((unsigned)time(0));

    long long total = 30 * 1073741824LL; // 1GB = 1,073,741,824 ×Ö½Ú
    int chunk = 1000000;
    int cnt = 0;
    std::ofstream file("bigfile.txt");
    while (total > 0) {
        int write_size = (total < chunk) ? total : chunk;
        file << random_string(write_size);
        total -= write_size;
        std::cout << ++cnt << std::endl; 
    }
    file.close();
    return 0;
}

