#ifndef PIECE_H
#define PIECE_H

#include <QColor>
#include <QGraphicsEllipseItem>
#include "mainwindow.h"

enum class PieceColor {White, Black};
enum class PieceType {Regular, Queen};

class Piece : public QGraphicsEllipseItem
{
public:
    Piece(PieceColor color, PieceType type, int row, int col, QGraphicsItem *parent = nullptr);
    PieceColor color() const {return m_color;}
    PieceType pType() const {return m_type;}
    int row() const {return m_row;}
    int col() const {return m_col;}

    void setPosition(int row, int col);
    void promoteToKing();
    bool isKing() const {return m_type == PieceType::Queen;}

    void updateAppearance();

private:
    PieceColor m_color;
    PieceType m_type;
    int m_row;
    int m_col;
};

#endif // PIECE_H
