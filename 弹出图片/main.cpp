#include <iostream>
#include "imageviewer.h"

int main() {
    std::cout << "Enter 1 to preview image, others to quit: ";
    int cmd;  if (!(std::cin >> cmd) || cmd != 1) return 0;

    ShowImage(L"test.png");   // �� �ĳ��Լ����ļ���
    return 0;
}

