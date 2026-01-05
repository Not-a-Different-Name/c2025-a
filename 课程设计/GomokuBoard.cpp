#include "GomokuBoard.h"
#include <QPainter>
#include <QMouseEvent>
#include <QtMath>
#include <QTimer>
#include <QInputDialog>
#include <QMessageBox>
#include <algorithm>

GomokuBoard::GomokuBoard(QWidget* parent)
    : QWidget(parent),
      m_board(m_boardSize, QVector<int>(m_boardSize, Empty)),
      m_candidateFlags(m_boardSize, QVector<bool>(m_boardSize, false))
{
    setMouseTracking(true);
    setFocusPolicy(Qt::StrongFocus);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

QSize GomokuBoard::sizeHint() const
{
    const int side = m_margin * 2 + (m_boardSize - 1) * m_cellSize;
    return { side, side };
}

QSize GomokuBoard::minimumSizeHint() const
{
    const int side = m_margin * 2 + (m_boardSize - 1) * m_cellSize;
    return { side, side };
}

void GomokuBoard::reset()
{
    for (auto& row : m_board) row.fill(Empty);
    m_moves.clear();
    m_blackTurn = true;
    m_gameEnded = false;
    m_evaluation = 0;

    m_candidates.clear();
    for (auto& f : m_candidateFlags) f.fill(false);

    // 初始：把中心及其 5x5（除中心）加入候选
    const int cx = m_boardSize / 2;
    const int cy = m_boardSize / 2;
    addCandidate(cx, cy);
    updateCandidatesAfterMove(cx, cy); // 扩展周围 24 格

    emit currentPlayerChanged(Black);
    update();
}

void GomokuBoard::undo()
{
    if (m_moves.isEmpty()) return;
    const QPoint last = m_moves.pop();
    m_board[last.x()][last.y()] = Empty;
    m_gameEnded = false;
    m_blackTurn = !m_blackTurn;
    emit currentPlayerChanged(m_blackTurn ? Black : White);

    // 简单策略：重新全量重建候选（避免复杂回退逻辑）
    m_candidates.clear();
    for (auto& f : m_candidateFlags) f.fill(false);

    // 扫描所有已下子，围绕它们扩展 5x5
    for (int idx = 0; idx < m_moves.size(); ++idx) {
        const QPoint pt = m_moves[idx];
        updateCandidatesAfterMove(pt.x(), pt.y());
    }
    // 已有子本身不能是候选，确保移除
    for (int idx = 0; idx < m_moves.size(); ++idx) {
        const QPoint pt = m_moves[idx];
        removeCandidate(pt.x(), pt.y());
    }

    update();
}

void GomokuBoard::setDepth(int /*depth*/)
{
    bool ok = false;
    const int newDepth = QInputDialog::getInt(
        this,
        tr("设置搜索深度"),
        tr("深度(1-6)："),
        m_depth,
        1, 6, 1,
        &ok
    );
    if (!ok) return;
    m_depth = newDepth;
}

void GomokuBoard::showEvaluation()
{
    QMessageBox::information(
        this,
        tr("当前估值"),
        tr("AI 估值: %1").arg(m_evaluation)
    );
}

void GomokuBoard::paintEvent(QPaintEvent*)
{
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing, true);
    p.fillRect(rect(), QColor("#F0D9B5"));

    const int left = m_margin;
    const int top = m_margin;
    const int right = m_margin + (m_boardSize - 1) * m_cellSize;
    const int bottom = m_margin + (m_boardSize - 1) * m_cellSize;

    QPen grid(Qt::black);
    grid.setWidth(1);
    p.setPen(grid);
    for (int i = 0; i < m_boardSize; ++i) {
        int x = left + i * m_cellSize;
        int y = top + i * m_cellSize;
        p.drawLine(left, y, right, y);
        p.drawLine(x, top, x, bottom);
    }

    auto drawStar = [&](int r, int c) {
        QPoint pt = cellToPoint(r, c);
        p.setBrush(Qt::black);
        p.drawEllipse(pt, 3, 3);
    };
    const int star = (m_boardSize == 15) ? 3 : 2;
    drawStar(star, star);
    drawStar(star, m_boardSize / 2);
    drawStar(star, m_boardSize - 1 - star);
    drawStar(m_boardSize / 2, star);
    drawStar(m_boardSize / 2, m_boardSize / 2);
    drawStar(m_boardSize / 2, m_boardSize - 1 - star);
    drawStar(m_boardSize - 1 - star, star);
    drawStar(m_boardSize - 1 - star, m_boardSize / 2);
    drawStar(m_boardSize - 1 - star, m_boardSize - 1 - star);

    for (int r = 0; r < m_boardSize; ++r) {
        for (int c = 0; c < m_boardSize; ++c) {
            if (m_board[r][c] == Empty) continue;
            QPoint pt = cellToPoint(r, c);
            const int radius = m_cellSize / 2 - 2;
            QRect stoneRect(pt.x() - radius, pt.y() - radius, radius * 2, radius * 2);
            if (m_board[r][c] == Black) {
                p.setBrush(Qt::black);
                p.setPen(QPen(Qt::black, 1));
            } else {
                p.setBrush(Qt::white);
                p.setPen(QPen(Qt::black, 1));
            }
            p.drawEllipse(stoneRect);
        }
    }

    if (!m_moves.isEmpty()) {
        QPoint last = m_moves.top();
        QPoint pt = cellToPoint(last.x(), last.y());
        p.setBrush(Qt::red);
        p.setPen(Qt::NoPen);
        p.drawEllipse(pt, 4, 4);
    }
}

void GomokuBoard::mouseReleaseEvent(QMouseEvent* event)
{
	if (event->button() != Qt::LeftButton) return;
	if (m_gameEnded) return;
	if (!m_blackTurn) return; // 只允许玩家（黑）点击

#if QT_VERSION >= QT_VERSION_CHECK(6,0,0)
	const QPoint cell = coordToCell(event->position());
#else
	const QPoint cell = coordToCell(event->pos());
#endif
	const int row = cell.x();
	const int col = cell.y();
	if (!inBoard(row, col)) return;
	if (!placeStone(row, col)) return;

	// 请求重绘黑子并立刻返回事件循环
	update();

	// 推迟到下一次事件循环，让白棋（AI）走一步
	QTimer::singleShot(0, this, &GomokuBoard::playWhiteOnce);
	// 将 AI 调用推迟到下一次事件循环，避免阻塞导致黑子不即时显示
	
}

void GomokuBoard::playWhiteOnce()
{
    // 游戏已结束或当前不是白棋回合则不走
    if (m_gameEnded || m_blackTurn) return;

    QPoint aiCell = computer_board_ai(White, Black);
    int aiRow = aiCell.x();
    int aiCol = aiCell.y();

    // 若 AI 返回非法或已占用位置，改用安全后备：从候选中找第一个空点
    if (!inBoard(aiRow, aiCol) || m_board[aiRow][aiCol] != Empty) {
        bool found = false;
        for (const QPoint& mv : m_candidates) {
            int r = mv.x(), c = mv.y();
            if (inBoard(r, c) && m_board[r][c] == Empty) {
                aiRow = r; aiCol = c;
                found = true;
                break;
            }
        }
        // 候选可能异常为空，兜底全盘扫描（极少发生）
        if (!found) {
            for (int r = 0; r < m_boardSize && !found; ++r) {
                for (int c = 0; c < m_boardSize; ++c) {
                    if (m_board[r][c] == Empty) {
                        aiRow = r; aiCol = c;
                        found = true;
                        break;
                    }
                }
            }
        }
        // 仍未找到则直接返回并把回合还给黑方，避免“卡住”
        if (!found) {
            m_blackTurn = true;
            emit currentPlayerChanged(Black);
            return;
        }
    }

    if (placeStone(aiRow, aiCol)) {
        update();
    } else {
        // 极端情况下再兜底一次，避免停在白方
        m_blackTurn = true;
        emit currentPlayerChanged(Black);
    }
}


bool GomokuBoard::placeStone(int row, int col)
{
	if (!inBoard(row, col) || m_board[row][col] != Empty) return false;
	const int stone = m_blackTurn ? Black : White;
	m_board[row][col] = stone;
    m_moves.push(QPoint(row, col));

    // 增量维护候选集合：移除该点并扩展其周围 24 格
    removeCandidate(row, col);
    updateCandidatesAfterMove(row, col);

	if (checkWin(row, col)) {
		m_gameEnded = true;
		emit gameOver(stone);
	}
	else {
		m_blackTurn = !m_blackTurn;
		emit currentPlayerChanged(m_blackTurn ? Black : White);
	}
	return true;
}

bool GomokuBoard::inBoard(int row, int col) const
{
	return row >= 0 && row < m_boardSize && col >= 0 && col < m_boardSize;
}

int GomokuBoard::countDir(int row, int col, int dr, int dc) const
{
	const int stone = m_board[row][col];
	int cnt = 0;
	int r = row + dr, c = col + dc;
	while (inBoard(r, c) && m_board[r][c] == stone) {
		++cnt; r += dr; c += dc;
	}
	return cnt;
}

bool GomokuBoard::checkWin(int row, int col) const
{
	if (m_board[row][col] == Empty) return false;
	static const int dirs[4][2] = { {0,1}, {1,0}, {1,1}, {1,-1} };
	for (auto& d : dirs) {
		int line = 1 + countDir(row, col, d[0], d[1]) + countDir(row, col, -d[0], -d[1]);
		if (line >= 5) return true;
	}
	return false;
}

QPoint GomokuBoard::coordToCell(const QPointF& pos) const
{
	const double x = pos.x();
	const double y = pos.y();
	const double edge = m_margin;
	const double right = m_margin + (m_boardSize - 1) * m_cellSize;
	const double bottom = m_margin + (m_boardSize - 1) * m_cellSize;
	if (x < edge - m_cellSize / 2.0 || x > right + m_cellSize / 2.0 ||
		y < edge - m_cellSize / 2.0 || y > bottom + m_cellSize / 2.0)
		return QPoint(-1, -1);
	const int col = qRound((x - edge) / m_cellSize);
	const int row = qRound((y - edge) / m_cellSize);
	return QPoint(row, col);
}

QPoint GomokuBoard::cellToPoint(int row, int col) const
{
	const int x = m_margin + col * m_cellSize;
	const int y = m_margin + row * m_cellSize;
	return QPoint(x, y);
}

int GomokuBoard::evaluate(int chess, int /*chess_*/, const QVector<QPoint>& candidates, int candidateCount)
{
	const QVector<QPoint>& moves = candidates;
	int count = candidateCount;

	static const int drect[4][2] = { {0,1}, {1,0}, {1,1}, {1,-1} };
	int score = 0;

	////// 强化系数：连续子权重、开放端权重、微调偏置
	//constexpr double kLen  = 1.10; // 原 0.9 -> 1.10，更强调长连
	//constexpr double kOpen = 0.70; // 原对 openends 等效系数 1.0*(openends-1) -> 0.70*(openends-1)，但整体仍更高
	//constexpr double kBias = 0.25; // 原 0.15 -> 0.25，整体抬高分数

    for (const QPoint& mv : m_candidates) {
        int i = mv.x(), j = mv.y();
		if (m_board[i][j] != chess) continue;
		for (int d = 0; d < 4; ++d) {
			const int pr = i - drect[d][0];
			const int pc = j - drect[d][1];
			if (inBoard(pr, pc) && m_board[pr][pc] == chess) continue; // 非段起点
			int cntForward = countDir(i, j, drect[d][0], drect[d][1]);
			int count = 1 + cntForward;
			int openends = 0;

			if (inBoard(pr, pc) && m_board[pr][pc] == Empty) openends++;
			const int er = i + count * drect[d][0];
			const int ec = j + count * drect[d][1];
			if (inBoard(er, ec) && m_board[er][ec] == Empty) openends++;
			if (count >= 5) return INT_MAX;

			//// 加强后的代数运算得分（注意：当前实现是覆盖而非累加）
			//score += (openends > 0)? static_cast<int>(pow(10.0, kLen * count + kOpen * (openends - 1) + kBias)) : 0;
			switch (count) {
			case 1:
				score += (openends == 2) ? 10 : (openends == 1 ? 2 : 0);
				break;
			case 2:
				score += (openends == 2) ? 500 : (openends == 1 ? 50 : 0);
				break;
			case 3:
				score += (openends == 2) ? 10000 : (openends == 1 ? 500 : 0);
				break;
			case 4:
				score += (openends == 2) ? INT_MAX : (openends == 1 ? 200000 : 0);
				break;
			default:
				break;
			}
		}
	}
	return score;
}

QPoint GomokuBoard::computer_board_ai(int chess_ai, int chess_player)
{
    int bestScore = INT_MIN;
    int best_i = -1, best_j = -1;
    int depth = m_depth;

    // 候选集为空（极少见）：回到中心
    if (m_candidates.isEmpty()) {
        return QPoint(m_boardSize / 2, m_boardSize / 2);
    }

    // 1) 立赢着
    for (const QPoint& mv : m_candidates) {
        int i = mv.x(), j = mv.y();
        if (m_board[i][j] != Empty) continue;
        m_board[i][j] = chess_ai;
        bool winNow = checkWin(i, j);
        m_board[i][j] = Empty;
        if (winNow) return QPoint(i, j);
    }

    // 2) 必堵着
    for (const QPoint& mv : m_candidates) {
        int i = mv.x(), j = mv.y();
        if (m_board[i][j] != Empty) continue;
        m_board[i][j] = chess_player;
        bool oppWin = checkWin(i, j);
        m_board[i][j] = Empty;
        if (oppWin) return QPoint(i, j);
    }

    // 限制过大候选数量时降深
    /*if (m_candidates.size() > 60 && depth > 1) depth--;*/

    // 简单遍历搜索（可在此处加入排序启发）
    for (const QPoint& mv : m_candidates) {
        int i = mv.x(), j = mv.y();
        if (m_board[i][j] != Empty) continue;
        m_board[i][j] = chess_ai;
        int score = alphabeta(depth, INT_MIN, INT_MAX, false, chess_ai, chess_player,
                              i, j, m_candidates, m_candidates.size());
        m_board[i][j] = Empty;
        if (score > bestScore) {
            bestScore = score;
            m_evaluation = score;
            best_i = i; best_j = j;
        }
    }

    if (best_i != -1) return QPoint(best_i, best_j);
    return QPoint(m_boardSize / 2, m_boardSize / 2);
}

int GomokuBoard::alphabeta(int depth, int alpha, int beta, bool maximizing,
                           int chess1, int chess2, int lastRow, int lastCol,
                           const QVector<QPoint>& candidates, int candidateCount)
{
    if (lastRow >= 0 && lastCol >= 0) {
        if (checkWin(lastRow, lastCol))
            return maximizing ? INT_MIN : INT_MAX;
    }
    if (depth <= 0 || candidateCount == 0) {
        return evaluate(chess1, chess2, candidates, candidateCount) -
               static_cast<int>(1.2 * evaluate(chess2, chess1, candidates, candidateCount));
    }

    if (maximizing) {
        int best = INT_MIN;
        for (int t = 0; t < candidateCount; ++t) {
            int i = candidates[t].x(), j = candidates[t].y();
            if (m_board[i][j] != Empty) continue;
            m_board[i][j] = chess1;
            int val = alphabeta(depth - 1, alpha, beta, false,
                                chess1, chess2, i, j, candidates, candidateCount);
            m_board[i][j] = Empty;
            if (val > best) best = val;
            if (best > alpha) alpha = best;
            if (beta <= alpha) break;
        }
        return best;
    } else {
        int best = INT_MAX;
        for (int t = 0; t < candidateCount; ++t) {
            int i = candidates[t].x(), j = candidates[t].y();
            if (m_board[i][j] != Empty) continue;
            m_board[i][j] = chess2;
            int val = alphabeta(depth - 1, alpha, beta, true,
                                chess1, chess2, i, j, candidates, candidateCount);
            m_board[i][j] = Empty;
            if (val < best) best = val;
            if (best < beta) beta = best;
            if (beta <= alpha) break;
        }
        return best;
    }
}

// ----------------- 新增增量候选维护 -----------------

// 将 (row,col) 加入候选列表（若为空且未存在）
void GomokuBoard::addCandidate(int row, int col)
{
    if (!inBoard(row, col)) return;
    if (m_board[row][col] != Empty) return;
    if (m_candidateFlags[row][col]) return;
    m_candidates.push_back(QPoint(row, col));
    m_candidateFlags[row][col] = true;
}

// 从候选列表移除该点（若存在）
void GomokuBoard::removeCandidate(int row, int col)
{
    if (!inBoard(row, col)) return;
    if (!m_candidateFlags[row][col]) return;
    // 线性删除（候选量较小可接受）
    for (int k = 0; k < m_candidates.size(); ++k) {
        if (m_candidates[k].x() == row && m_candidates[k].y() == col) {
            m_candidates.remove(k);
            break;
        }
    }
    m_candidateFlags[row][col] = false;
}

// 落子后扩展其周围 5x5（除自身 24 格）为空点加入候选
void GomokuBoard::updateCandidatesAfterMove(int row, int col)
{
    for (int dr = -2; dr <= 2; ++dr) {
        for (int dc = -2; dc <= 2; ++dc) {
            if (dr == 0 && dc == 0) continue; // 排除自身，留下 24 格
            int nr = row + dr;
            int nc = col + dc;
            addCandidate(nr, nc);
        }
    }
}