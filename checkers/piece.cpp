#include "piece.h"
#include <QBrush>
#include <QPen>
Piece::Piece(PieceColor color, PieceType type, int row, int col, QGraphicsItem *parent)
    :QGraphicsEllipseItem(parent)
    ,m_color(color)
    ,m_type(type)
    ,m_row(row)
    ,m_col(col)
{
    setRect(5,5, CELL_SIZE - 10, CELL_SIZE - 10);
    setAcceptHoverEvents(true);
    updateAppearance();
}

void Piece::setPosition(int row, int col){
    m_row = row,
    m_col = col,
    setPos(col*CELL_SIZE + 5, row * CELL_SIZE + 5);
}

void Piece::promoteToKing(){
    m_type = PieceType::Queen;
    updateAppearance();
}

void Piece::updateAppearance(){
    QColor baseColor = (m_color == PieceColor::White) ? QColor("#eee") : QColor("#222");
    setBrush(QBrush(baseColor));
    setPen(QPen(Qt::black, 2));

    if (m_type == PieceType::Queen){
        setPen(QPen(Qt::yellow, 3));
    }
}
