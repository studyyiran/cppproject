#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>  // for NULL

using namespace std;

const int MAX_LOGS = 1000;

struct Record {
    string text;
    time_t ts;
};

Record logs[MAX_LOGS];
int logCount = 0;
int xp = 0;

// 打印带颜色的消息，默认绿色 (32)
void colorPrint(const string& msg, const string& colorCode = "32") {
    cout << "\033[" << colorCode << "m" << msg << "\033[0m\n";
}

void saveRecord() {
    if (logCount >= MAX_LOGS) {
        colorPrint("记录已满，无法保存新条目。", "31");
        return;
    }
    colorPrint("输入星球笔记：", "36");
    string s;
    cin >> s;
    logs[logCount].text = s;
    // C++98 写法，用 NULL
    logs[logCount].ts = time(NULL);
    logCount++;
    xp += 10;
    colorPrint("? 保存成功！ +10 XP");
}

void listRecords() {
    if (logCount == 0) {
        colorPrint("当前没有任何记录。", "33");
        return;
    }
    for (int i = 0; i < logCount; i++) {
        // 去掉 ctime 的末尾换行符（手动做）
        string tsStr = ctime(&logs[i].ts);
        if (tsStr.size() > 0 && tsStr[tsStr.size()-1] == '\n') {
            tsStr.resize(tsStr.size()-1);
        }
        cout << i << ". " << logs[i].text
             << " (" << tsStr << ")\n";
    }
    cout << "当前等级：" << (xp / 100 + 1)
         << "  XP: " << xp << "\n";
}

void deleteRecord() {
    listRecords();
    if (logCount == 0) return;

    colorPrint("输入要删除的编号：", "31");
    int idx;
    cin >> idx;
    if (idx >= 0 && idx < logCount) {
        colorPrint("删除 " + logs[idx].text + " ? 1=是 0=否", "33");
        int confirm;
        cin >> confirm;
        if (confirm == 1) {
            // 将后面的元素前移
            for (int j = idx; j < logCount - 1; j++) {
                logs[j] = logs[j + 1];
            }
            logCount--;
            colorPrint("已删除");
        }
    } else {
        colorPrint("编号无效。", "31");
    }
}

void welcome() {
    cout << "欢迎使用 ?? 星际日志终端 v0.9\n";
}

void menu() {
    cout << "\n—— 菜单 ——\n"
         << "1) 记录新星球\n"
         << "2) 浏览已发现的星球\n"
         << "3) 删除错误记录\n"
         << "4) 退出\n"
         << "请选择：";
    string choice;
    cin >> choice;
    if (choice == "1") {
        saveRecord();
    } else if (choice == "2") {
        listRecords();
    } else if (choice == "3") {
        deleteRecord();
    } else if (choice == "4") {
        colorPrint("再见，探险家！", "36");
        exit(0);
    } else {
        colorPrint("无效选择，请重试。", "31");
    }
}

int main() {
    welcome();
    while (true) {
        menu();
    }
    return 0;
}

