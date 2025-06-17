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

/* ─────────────────────────────────────
   核心持久化接口
   ────────────────────────────────────*/
// 读全部：每次调用都会把文件内容载入 db[].
// 返回 db 指针，outCount 返回记录数。
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

// 写/改：先同步到内存，再更新 db[id]，然后整表重写回文件。
void setOne(int id, const std::string& s) {
    int n; getAll(n);                             // 先同步
    if (id < 0 || id >= MAX_TASKS) {              // 基本检查
        std::cerr << "Error: id 越界\n";
        return;
    }
    db[id] = s;
    if (id >= dbCount) dbCount = id + 1;          // 新增时扩充

    std::ofstream ofs(DB_FILE, std::ofstream::trunc);
    for (int i = 0; i < dbCount; ++i)
        ofs << db[i] << '\n';
}

// 删除：同步后挪动数组并重写文件
void deleteOne(int id) {
    int n; getAll(n);
    if (id < 0 || id >= n) {
        std::cerr << "Error: id 越界\n";
        return;
    }
    for (int i = id; i < n - 1; ++i)
        db[i] = db[i + 1];
    dbCount = n - 1;

    std::ofstream ofs(DB_FILE, std::ofstream::trunc);
    for (int i = 0; i < dbCount; ++i)
        ofs << db[i] << '\n';
}

/* ─────────────────────────────────────
   UI / 辅助函数
   ────────────────────────────────────*/
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
    std::cout << "\n--- 当前任务 (" << n << ") ---\n";
    for (int i = 0; i < n; ++i)
        std::cout << "[" << i << "] " << arr[i] << '\n';
    std::cout << "---------------------------\n";
}

void addTask() {
    int n;
    getAll(n);                        // 先拿最新条数
    std::string txt = promptLine("输入新任务内容：");
    setOne(n, txt);                   // 追加
    std::cout << "已添加。\n";
}

void updateTask() {
    listTasks();
    int id = promptInt("要修改哪一条 (id)：");
    std::string txt = promptLine("新的内容：");
    setOne(id, txt);
    std::cout << "已更新。\n";
}

void removeTask() {
    listTasks();
    int id = promptInt("要删除哪一条 (id)：");
    deleteOne(id);
    std::cout << "已删除。\n";
}

void showMenu() {
    std::cout << "\n====== TodoList 菜单 ======\n"
              << "1. 查看全部任务\n"
              << "2. 新增任务\n"
              << "3. 修改任务\n"
              << "4. 删除任务\n"
              << "5. 退出\n"
              << "请选择 (1-5)：";
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
            default: std::cout << "无效选项！\n";
        }
    }
    return 0;
}

