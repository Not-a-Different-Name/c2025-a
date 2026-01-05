#include "QtWidgetsApplication1.h" // 引入主窗口类头文件
#include <QtWidgets/QApplication> // 引入 QApplication 应用入口类

int main(int argc, char *argv[]) // 程序入口函数
{
    QApplication app(argc, argv); // 创建 Qt 应用对象，接管事件循环

    QtWidgetsApplication1 window; // 创建主窗口
    window.resize(600, 600); // 设定初始窗口大小
    window.show(); // 显示主窗口

    return app.exec(); // 进入事件循环，返回应用退出码
}
