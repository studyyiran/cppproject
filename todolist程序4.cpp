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

// ��ӡ����ɫ����Ϣ��Ĭ����ɫ (32)
void colorPrint(const string& msg, const string& colorCode = "32") {
    cout << "\033[" << colorCode << "m" << msg << "\033[0m\n";
}

void saveRecord() {
    if (logCount >= MAX_LOGS) {
        colorPrint("��¼�������޷���������Ŀ��", "31");
        return;
    }
    colorPrint("��������ʼǣ�", "36");
    string s;
    cin >> s;
    logs[logCount].text = s;
    // C++98 д������ NULL
    logs[logCount].ts = time(NULL);
    logCount++;
    xp += 10;
    colorPrint("? ����ɹ��� +10 XP");
}

void listRecords() {
    if (logCount == 0) {
        colorPrint("��ǰû���κμ�¼��", "33");
        return;
    }
    for (int i = 0; i < logCount; i++) {
        // ȥ�� ctime ��ĩβ���з����ֶ�����
        string tsStr = ctime(&logs[i].ts);
        if (tsStr.size() > 0 && tsStr[tsStr.size()-1] == '\n') {
            tsStr.resize(tsStr.size()-1);
        }
        cout << i << ". " << logs[i].text
             << " (" << tsStr << ")\n";
    }
    cout << "��ǰ�ȼ���" << (xp / 100 + 1)
         << "  XP: " << xp << "\n";
}

void deleteRecord() {
    listRecords();
    if (logCount == 0) return;

    colorPrint("����Ҫɾ���ı�ţ�", "31");
    int idx;
    cin >> idx;
    if (idx >= 0 && idx < logCount) {
        colorPrint("ɾ�� " + logs[idx].text + " ? 1=�� 0=��", "33");
        int confirm;
        cin >> confirm;
        if (confirm == 1) {
            // �������Ԫ��ǰ��
            for (int j = idx; j < logCount - 1; j++) {
                logs[j] = logs[j + 1];
            }
            logCount--;
            colorPrint("��ɾ��");
        }
    } else {
        colorPrint("�����Ч��", "31");
    }
}

void welcome() {
    cout << "��ӭʹ�� ?? �Ǽ���־�ն� v0.9\n";
}

void menu() {
    cout << "\n���� �˵� ����\n"
         << "1) ��¼������\n"
         << "2) ����ѷ��ֵ�����\n"
         << "3) ɾ�������¼\n"
         << "4) �˳�\n"
         << "��ѡ��";
    string choice;
    cin >> choice;
    if (choice == "1") {
        saveRecord();
    } else if (choice == "2") {
        listRecords();
    } else if (choice == "3") {
        deleteRecord();
    } else if (choice == "4") {
        colorPrint("�ټ���̽�ռң�", "36");
        exit(0);
    } else {
        colorPrint("��Чѡ�������ԡ�", "31");
    }
}

int main() {
    welcome();
    while (true) {
        menu();
    }
    return 0;
}

