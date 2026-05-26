#include "game.h"
#include <QDebug>



Game::Game(QObject *parent)
    : QObject(parent)
    ,m_currentPlayer(PieceColor::White)
    ,m_selectedRow(-1), m_selectedCol(-1)
    ,m_mustCapture(false)
{
    startNewGame();
}

void Game::startNewGame(){
    m_board = board();
    m_board.setupInitialPosition();
    m_currentPlayer = PieceColor::White;
    m_selectedRow = m_selectedCol = -1;
    m_mustCapture = m_board.hasCapturesAvailable(m_currentPlayer);
    emit turnChanged(m_currentPlayer);
}


void Game::checkTurnChange(){
    m_mustCapture = m_board.hasCapturesAvailable(m_currentPlayer);
    m_currentPlayer = (m_currentPlayer == PieceColor::White) ? PieceColor::Black : PieceColor::White;
    emit turnChanged(m_currentPlayer);

}

void Game::checkForPromotion(int row, int col){
    Piece* piece = m_board.pieceAt(row, col);
    if (!piece) return;

    if ((piece->color() == PieceColor::White && row == 0) || (piece->color() == PieceColor::Black && row == CELL_COUNT - 1){
            piece->promoteToKing();
        }

}
QVector<QPair<int, int>> Game::getHintMoves(int row, int col) const {
    QVector<QPair<int,int>> hints;
    auto moves = m_board.getPossibleMoves(row, col);
    for (const auto& move : moves){
        hints.append({move.toRow, move.toCol});

    }
    return hints;
}
