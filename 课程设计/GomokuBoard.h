#pragma once
#include <QWidget>
#include <QVector>
#include <QStack>
#include <QPoint>

class GomokuBoard : public QWidget
{
    Q_OBJECT
public:
    // 棋子类型：0=空，1=黑，2=白（与 m_board 内存储的数值一致）
    enum Stone : int { Empty = 0, Black = 1, White = 2 };

    explicit GomokuBoard(QWidget* parent = nullptr);    // 构造：初始化棋盘、状态等

    // 尺寸建议（用于布局系统）
    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;

signals:
    // 当前执子变化（1=黑，2=白）
    void currentPlayerChanged(int player);
    // 棋局结束（1=黑胜，2=白胜）
    void gameOver(int winner);

public slots:
    // 新开一局：清空棋盘与历史，黑先
    void reset();
    // 撤销一步：回退上一手，轮换执子
    void undo();
	//设置搜索深度
    void setDepth(int depth);
    //显示当前估值
	void showEvaluation();

protected:
    // 绘制：棋盘底色、网格、星位、棋子、最后一步标记
    void paintEvent(QPaintEvent* e) override;
    // 鼠标左键释放：尝试将点击位置转换为格点并落子
    void mouseReleaseEvent(QMouseEvent* event) override;

private:
    // 逻辑辅助
    bool placeStone(int row, int col);                  // 在(row,col)落子（合法性检查、判胜、换手/结束）
    bool inBoard(int row, int col) const;               // 是否在棋盘范围内
    bool checkWin(int row, int col) const;              // 是否形成五连
    int  countDir(int row, int col, int dr, int dc) const; // 沿方向(dr,dc)累计同色数量（不含自身）
    int evaluate(int chess, int chess_ , const QVector<QPoint>& candidates, int candidateCount);
    QPoint computer_board_ai(int chess_ai, int chess_player);
    int alphabeta(int depth, int alpha, int beta, bool maximizing,
        int chess1, int chess2, int lastRow, int lastCol,
        const QVector<QPoint>& candidates, int candidateCount);

    // 新增：让白棋（AI）走一步
    void playWhiteOnce();
    // 新增：增量维护候选着法（围绕最新落子 5x5 区域，即 24 个格）
    void updateCandidatesAfterMove(int row, int col);
    void addCandidate(int row, int col);
    void removeCandidate(int row, int col);

    // 坐标转换
    // 约定：格坐标使用(row, col)，并以 QPoint(row, col) 承载（x=行, y=列）
    QPoint coordToCell(const QPointF& pos) const;       // 像素坐标 -> 最近格坐标（带边界/吸附判断）
    QPoint cellToPoint(int row, int col) const;         // 格坐标 -> 该格中心像素坐标

private:
    // 棋盘参数
    const int m_boardSize = 15;     // 棋盘尺寸：m_boardSize x m_boardSize
    const int m_cellSize  = 32;     // 网格边长（像素）
    const int m_margin    = 24;     // 棋盘边距（像素）

    // 棋盘与状态
    QVector<QVector<int>> m_board;  // 棋盘数据：[row][col]，取值见 Stone
    bool   m_blackTurn = true;      // true=黑棋回合，false=白棋回合
    bool   m_gameEnded = false;     // true=已分胜负
    QStack<QPoint> m_moves;         // 走子栈：QPoint(row,col)
	int     m_depth = 3;    // AI 搜索深度
	int	 m_evaluation = 0; // 当前局面估值

    // 候选着法容器 + 标记矩阵（用于 O(1) 判重）
    QVector<QPoint> m_candidates;
    QVector<QVector<bool>> m_candidateFlags; // true 表示在候选集合中
};