#ifndef GAME_H
#define GAME_H

#include <QObject>
#include "board.h"

class Game : public QObject
{
    Q_OBJECT
public:
    explicit Game(QObject *parent = nullptr);

    void startNewGame();

    PieceColor currentPlayer() const {return m_currentPlayer;}
    bool isGameOver() const {return m_board.isGameOver();}
    bool handleCellClick(int row, int col);

    QVector<QPair<int, int>> getHintMoves(int row, int col) const;

    board& board(){return m_board;}

signals:
    void pieceMoved(int fromRow, int fromCol, int toRow, int toCol);
    void pieceCaptured(int row, int col);
    void gameEnded(pieceColor winner);
    void turnChanged(PieceColor player);
    void hintUpdated(QVector<QPair<int, int>> cells);


private:
    board m_board;
    PieceColor m_currentPlayer;

    int m_selectedRow;
    int m_selectedCol;
    bool m_mustCapture;

    void checkTurnChange();
    void checkForPromotion(int row, int col);
};

#endif // GAME_H
