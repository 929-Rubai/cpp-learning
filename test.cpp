#include <iostream>
#include <windows.h> // 引入 Windows API 头文件

using namespace std;

int main() {
    // 强制把终端的代码页改成 UTF-8，这样就不会乱码了
    SetConsoleOutputCP(65001); 

    cout << "Hello 拓扑排序!" << endl;
    cout << "我的 C++ 环境彻底通了！" << endl;
    return 0;
}