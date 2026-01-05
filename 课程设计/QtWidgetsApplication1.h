#pragma once // 头文件只编译一次的保护指令

#include <QtWidgets> // 引入常用 Qt Widgets 头
#include <QMainWindow> // 引入 QMainWindow 定义
#include "ui_QtWidgetsApplication1.h" // 引入由 uic 生成的 UI 头文件
#include "GomokuBoard.h" // 引入自定义的五子棋棋盘控件

class QtWidgetsApplication1 : public QMainWindow // 主窗口类，继承自 QMainWindow
{
    Q_OBJECT // 启用 Qt 的元对象系统（信号/槽等）

public:
    QtWidgetsApplication1(QWidget *parent = nullptr); // 构造函数，默认父对象为空
    ~QtWidgetsApplication1(); // 析构函数

private:
    void setupGameUi(); // 搭建游戏相关 UI（菜单、状态栏、中心棋盘）

private:
    Ui::QtWidgetsApplication1Class ui; // 由 uic 生成的 UI 类实例
    GomokuBoard* m_board = nullptr; // 中央的棋盘控件指针
    QAction* m_newGameAct = nullptr; // 菜单动作
    QAction* m_undoAct = nullptr; 
	QAction* m_depthAct = nullptr;
    QAction* m_evaluateAct = nullptr;
    /*QAction* m_func = nullptr;*///随便加的
};

