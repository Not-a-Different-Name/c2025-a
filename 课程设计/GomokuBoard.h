#pragma once
#include <QWidget>
#include <QVector>
#include <QStack>
#include <QPoint>

class GomokuBoard : public QWidget
{
    Q_OBJECT
public:
    enum Stone : int { Empty = 0, Black = 1, White = 2 };

    explicit GomokuBoard(QWidget* parent = nullptr);

    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;

signals:
    void currentPlayerChanged(int player);
    void gameOver(int winner);

public slots:
    void reset();
    void undo();
    void setDepth(int depth);
    void showEvaluation();

protected:
    void paintEvent(QPaintEvent* e) override;
    void mouseReleaseEvent(QMouseEvent* event) override;

private:
    bool placeStone(int row, int col);
    bool inBoard(int row, int col) const;
    bool checkWin(int row, int col) const;
    int  countDir(int row, int col, int dr, int dc) const;
    int evaluate(int chess, int chess_ , const QVector<QPoint>& candidates, int candidateCount);
    QPoint computer_board_ai(int chess_ai, int chess_player);
    int alphabeta(int depth, int alpha, int beta, bool maximizing,
        int chess1, int chess2, int lastRow, int lastCol,
        const QVector<QPoint>& candidates, int candidateCount);

    void playWhiteOnce();
    void updateCandidatesAfterMove(int row, int col);
    void addCandidate(int row, int col);
    void removeCandidate(int row, int col);

    
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
    bool   m_blackTurn = true;      
    bool   m_gameEnded = false;     
    QStack<QPoint> m_moves;         // 走子栈：QPoint(row,col)
	int     m_depth = 3;    // AI 搜索深度
	int	 m_evaluation = 0;

    // 候选着法容器 + 标记矩阵（用于 O(1) 判重）
    QVector<QPoint> m_candidates;
    QVector<QVector<bool>> m_candidateFlags; // true 表示在候选集合中
};