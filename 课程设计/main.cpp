#include "QtWidgetsApplication1.h" 
#include <QtWidgets/QApplication> 

int main(int argc, char *argv[]) // 程序入口函数
{
    QApplication app(argc, argv); 

    QtWidgetsApplication1 window; // 创建主窗口
    window.resize(600, 600); 
    window.show(); 

    return app.exec(); // 进入事件循环，返回应用退出码
}
