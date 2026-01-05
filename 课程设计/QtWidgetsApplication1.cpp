#include "QtWidgetsApplication1.h" // 引入主窗口类的头文件

QtWidgetsApplication1::QtWidgetsApplication1(QWidget *parent) // 构造函数实现
    : QMainWindow(parent) // 调用父类构造，传入父对象
{
    ui.setupUi(this); // 根据 .ui 文件构建基础界面
    setupGameUi(); // 追加搭建游戏 UI（棋盘/菜单/状态栏/信号连接）
}

QtWidgetsApplication1::~QtWidgetsApplication1() {} // 析构函数，当前无自定义资源需释放

void QtWidgetsApplication1::setupGameUi() // 组装游戏界面
{
    // 中心棋盘
    m_board = new GomokuBoard(this); // 创建棋盘控件，父对象为主窗口
    setCentralWidget(m_board); // 将棋盘设置为中心窗口部件


    // 状态栏
    if (!statusBar()) setStatusBar(new QStatusBar(this)); // 若无状态栏则创建一个
    statusBar()->showMessage("当前执子：黑"); // 初始消息：黑方先手


    // 菜单与动作
    QMenu* gameMenu = menuBar()->addMenu("游戏"); // 在菜单栏添加“游戏”菜单
    QMenu* gameMenu2 = menuBar()->addMenu("无用菜单项"); // 在菜单栏添加“游戏”菜单
    m_newGameAct = new QAction("新局", this); // 创建“新局”动作
    m_newGameAct->setShortcut(QKeySequence::New); // Ctrl+N 设置快捷键
    m_undoAct = new QAction("悔棋", this); // 创建“悔棋”动作
    m_undoAct->setShortcut(QKeySequence::Undo);   // Ctrl+Z 设置快捷键
    m_depthAct = new QAction("depth", this); // 创建动作
    m_evaluateAct = new QAction("eva", this); // 创建动作


    gameMenu->addAction(m_newGameAct); // 将“新局”加入菜单
    gameMenu->addAction(m_undoAct); // 将“悔棋”加入菜单
    gameMenu2->addAction(m_depthAct); // 将“depth”加入菜单
    gameMenu2->addAction(m_evaluateAct); // 加入菜单


    connect(m_newGameAct, &QAction::triggered, m_board, &GomokuBoard::reset); // 触发新局 -> 棋盘重置
    connect(m_undoAct, &QAction::triggered, m_board, &GomokuBoard::undo); // 触发悔棋 -> 棋盘撤销一步
    connect(m_depthAct, &QAction::triggered, m_board, &GomokuBoard::setDepth); // 触发
    connect(m_evaluateAct, &QAction::triggered, m_board, &GomokuBoard::showEvaluation); // 触发


    connect(m_board, &GomokuBoard::currentPlayerChanged, this, [this](int player) 
    { 
        // 执子方变化时更新状态栏
        statusBar()->showMessage(QString("当前执子：%1").arg(player == 1 ? "黑" : "白")); // 显示黑/白
    });

    connect(m_board, &GomokuBoard::gameOver, this, [this](int winner) 
    { 
        // 棋局结束时提示胜者
        statusBar()->showMessage(QString("胜者：%1").arg(winner == 1 ? "黑" : "白")); // 状态栏显示胜者
        QMessageBox::information(this, "游戏结束", 
                                 QString("%1方五连，胜利！").arg(winner == 1 ? "黑" : "白")); // 文本提示
    });

    // 初始化显示
    m_board->reset(); // 启动时清盘并设置为黑先
}

