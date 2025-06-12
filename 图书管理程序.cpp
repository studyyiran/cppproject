// todolist.cpp
// g++ todolist.cpp -o todolist

#include <iostream>
#include <fstream>
#include <string>
#include <limits>

const int MAX_TASKS = 1000;
static std::string db[MAX_TASKS];
static int         dbCount = 0;
static const char* DB_FILE = "todo.txt";

/* ��������������������������������������������������������������������������
   ���ĳ־û��ӿ�
   ������������������������������������������������������������������������*/
// ��ȫ����ÿ�ε��ö�����ļ��������� db[].
// ���� db ָ�룬outCount ���ؼ�¼����
std::string* getAll(int& outCount) {
    std::ifstream ifs(DB_FILE);
    dbCount = 0;
    if (ifs) {
        std::string line;
        while (dbCount < MAX_TASKS && std::getline(ifs, line))
            db[dbCount++] = line;
    }
    outCount = dbCount;
    return db;
}

// д/�ģ���ͬ�����ڴ棬�ٸ��� db[id]��Ȼ��������д���ļ���
void setOne(int id, const std::string& s) {
    int n; getAll(n);                             // ��ͬ��
    if (id < 0 || id >= MAX_TASKS) {              // �������
        std::cerr << "Error: id Խ��\n";
        return;
    }
    db[id] = s;
    if (id >= dbCount) dbCount = id + 1;          // ����ʱ����

    std::ofstream ofs(DB_FILE, std::ofstream::trunc);
    for (int i = 0; i < dbCount; ++i)
        ofs << db[i] << '\n';
}

// ɾ����ͬ����Ų�����鲢��д�ļ�
void deleteOne(int id) {
    int n; getAll(n);
    if (id < 0 || id >= n) {
        std::cerr << "Error: id Խ��\n";
        return;
    }
    for (int i = id; i < n - 1; ++i)
        db[i] = db[i + 1];
    dbCount = n - 1;

    std::ofstream ofs(DB_FILE, std::ofstream::trunc);
    for (int i = 0; i < dbCount; ++i)
        ofs << db[i] << '\n';
}

/* ��������������������������������������������������������������������������
   UI / ��������
   ������������������������������������������������������������������������*/
void clearInput() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
std::string promptLine(const std::string& msg) {
    std::cout << msg;
    std::string s;
    std::getline(std::cin, s);
    return s;
}
int promptInt(const std::string& msg) {
    int x;
    std::cout << msg;
    std::cin >> x;
    clearInput();
    return x;
}

void listTasks() {
    int n;
    std::string* arr = getAll(n);
    std::cout << "\n--- ��ǰ���� (" << n << ") ---\n";
    for (int i = 0; i < n; ++i)
        std::cout << "[" << i << "] " << arr[i] << '\n';
    std::cout << "---------------------------\n";
}

void addTask() {
    int n;
    getAll(n);                        // ������������
    std::string txt = promptLine("�������������ݣ�");
    setOne(n, txt);                   // ׷��
    std::cout << "����ӡ�\n";
}

void updateTask() {
    listTasks();
    int id = promptInt("Ҫ�޸���һ�� (id)��");
    std::string txt = promptLine("�µ����ݣ�");
    setOne(id, txt);
    std::cout << "�Ѹ��¡�\n";
}

void removeTask() {
    listTasks();
    int id = promptInt("Ҫɾ����һ�� (id)��");
    deleteOne(id);
    std::cout << "��ɾ����\n";
}

void showMenu() {
    std::cout << "\n====== TodoList �˵� ======\n"
              << "1. �鿴ȫ������\n"
              << "2. ��������\n"
              << "3. �޸�����\n"
              << "4. ɾ������\n"
              << "5. �˳�\n"
              << "��ѡ�� (1-5)��";
}

int main() {
    while (true) {
        showMenu();
        int choice;
        if (!(std::cin >> choice)) break;
        clearInput();
        switch (choice) {
            case 1: listTasks();   break;
            case 2: addTask();     break;
            case 3: updateTask();  break;
            case 4: removeTask();  break;
            case 5: return 0;
            default: std::cout << "��Чѡ�\n";
        }
    }
    return 0;
}

