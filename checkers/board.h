#ifndef BOARD_H
#define BOARD_H

#include <QVector>
#include <QPair>
#include "piece.h"
#include "mainwindow.h"

struct Move{
    int fromRow, fromCol;
    int toRow, toCol;
    bool isCapture;
    int capturedRow, capturedCol;
};

class board
{
public:
    board();

    void setupInitialPosition();

    Piece* pieceAt(int row, int col) const;
    void setPiece(int row, int col, Piece* piece);
    void removePiece(int row, int col);

    bool isValidMove(const Move& move, PieceColor currentPlayer) const;
    bool hasCapturesAvailable(PieceColor color) const;

    bool makeMove(const Move& move);
    QVector<Move> getPossibleMoves(int row, int col) const;

    bool isGameOver() const;
    PieceColor winner() const;

    int size() const {return CELL_COUNT;}
private:
    QVector<QVector<Piece*>> m_board;

    bool isValidPosition(int row, int col) const;
    bool isDarkCell(int row, int col) const;
    QVector<Move> getRegularMoves(int row, int col) const;
    QVector<Move> getCaptureMoves(int row, int col) const;
};

#endif // BOARD_H
