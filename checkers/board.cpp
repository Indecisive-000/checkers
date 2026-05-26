#include "board.h"

#include <QDebug>


board::board() {
    m_board.resize(CELL_COUNT);
    for (int i = 0; i<CELL_COUNT; ++i){
        m_board[i].resize(CELL_COUNT, nullptr);

    }

}

void board::setupInitialPosition(){
    for (int r = 0; r < CELL_COUNT; ++r){
        for (int c = 0; c < CELL_COUNT; ++c){
            if (!isDarkCell(r, c)) continue;

            if (r<3){
                auto* piece = new Piece(PieceColor::Black, PieceType::Regular, r, c);
                setPiece(r,c,piece);

            }
            else if (r >= CELL_COUNT - 3){
                auto* piece = new Piece(PieceColor::White, PieceType::Regular, r, c);
                setPiece(r,c,piece);
            }
        }
    }
}

bool board::isValidPosition(int row, int col) const{
    return row>=0 && row < CELL_COUNT && col >= 0 && col < CELL_COUNT;

}
bool board::isDarkCell(int row, int col) const{
    return (row + col) % 2 == 1;
}

Piece* board::pieceAt(int row, int col) const{
    if (!isValidPosition(row, col)) return nullptr;
    return m_board[row][col];
}

void board::setPiece(int row, int col, Piece *piece){
    if (!isValidPosition(row, col)) return;
    m_board[row][col] = piece;
    if (piece) piece -> setPosition(row, col);
}

void board::removePiece(int row, int col){
    if (!isValidPosition(row, col)) return;
    delete m_board[row][col];
    m_board[row][col] = nullptr;
}


QVector<Move> board::getRegularMoves(int row, int col) const{
    QVector<Move> moves;
    Piece* piece = pieceAt(row,col);

    QVector<QPair<int, int>> directions;
    if (piece -> color() == PieceColor::White || piece->isKing()){
        directions << QPair<int, int>(-1, -1) << QPair<int, int>(-1, 1);
    }
    if (piece -> color() == PieceColor::Black || piece -> isKing()){
        directions << QPair<int, int>(1, -1) << QPair<int, int>(1, 1);
    }

    for(const auto& dir : directions){
        int newRow = row + dir.first;
        int newCol = col + dir.second;

        if (isValidPosition(newRow, newCol) && !pieceAt(newRow, newCol)){
            Move move{row, col, newRow, newCol, false, -1, -1};
            moves.append(move);
        }
    }
    return moves;

}

QVector<Move> board::getCaptureMoves(int row, int col) const{
    QVector<Move> moves;

    Piece* piece = pieceAt(row, col);

    if (!piece) return moves;

    QVector<QPair<int, int>> directions;
    if (piece -> color() == PieceColor::White || piece->isKing()){
        directions << QPair<int, int>(-1, -1) << QPair<int, int>(-1, 1);

    }
    if (piece->color() == PieceColor::Black || piece->isKing()){
        directions << QPair<int, int>(1, -1) << QPair<int, int>(1, 1);

    }
    for (const auto& dir : directions){
        int midRow = row + dir.first;
        int midCol = col + dir.second;
        int newRow = row + 2* dir.first;
        int newCol = col + 2 * dir.second;

        if (isValidPosition(newRow, newCol) && !pieceAt(newRow, newCol)){
            Piece* midPiece = pieceAt(midRow, midCol);
            if (midPiece && midPiece->color() != piece->color()){
                Move move{row, col, newRow, newCol, true, midRow, midCol};
                moves.append(move);
            }
        }
    }
    return moves;
}


QVector<Move> board::getPossibleMoves(int row, int col) const{
    QVector<Move> moves;
    Piece* piece = pieceAt(row, col);
    if (!piece) return moves;

    auto capture = getCaptureMoves(row,col);
    if (!capture.isEmpty()) return capture;

    return getRegularMoves(row,col);
}

bool board::hasCapturesAvailable(PieceColor color) const{
    for (int c = 0; c <CELL_COUNT; c++){
        for (int r=0; r<CELL_COUNT; r++){
            Piece* p=pieceAt(r,c);
            if (p && p->color() == color){
                if (!getCaptureMoves(r, c).isEmpty()) return true;
            }
        }
    }
    return false;
}

bool board::isValidMove(const Move &move, PieceColor currentPlayer) const{
    Piece* piece = pieceAt(move.fromRow, move.fromCol);
    if (!piece || piece->color() != currentPlayer){
        return false;
    }
    auto possibleMoves = getPossibleMoves(move.fromRow, move.fromCol);
    for (const auto& m : possibleMoves){
        if (m.toRow == move.toRow && m.toCol == move.toCol && m.isCapture == move.isCapture){
            return true;
        }
    }
    return false;
}

bool board::makeMove(const Move &move){
    if (!isValidMove(move, pieceAt(move.fromRow, move.fromCol)->color())) return false;

    Piece* piece = pieceAt(move.fromRow, move.fromCol);
    romovePiece(move.fromRow, move.fromCol);
    if (move.isCapture){
        removePiece(move.capturedRow, move.capturedCol);
    }
    if ((piece->color() == PieceColor::White && move.toRow == 0 || (piece->color() == PieceColor::Black && move.toRow == CELL_COUNT - 1))){
        piece -> promoteToKing();

    }
    setPiece(move.toRow, move.toCol, Piece);
    return true;
}

bool board::isGameOver() const{
    int whiteCount = 0, blackCount = 0;
    for (int r = 0; r < CELL_COUNT; r++ ){
        for (int c =0; c < CELL_COUNT; ++c){
            Piece* p = pieceAt(r,c);
            if (p){
                if (p->color() == PieceColor::White) whiteCount ++;
                else blackCount++;
            }
        }
    }
}

PieceColor board::winner() const{
    int whiteCount =0, blackCount = 0;
    for (int r =0; r < CELL_COUNT; ++r){
        for (int c =0; c<CELL_COUNT; ++c){
            Piece* p = pieceAt(r, c);
            if (p){
                if (p->color() == PieceColor::White) whiteCount++;
                else blackCount++;
            }
        }
    }
    if (blackCount == 0) return PieceColor::White;
    if (whiteCount == 0) return PieceColor::Black;
    return PieceColor::White;
}






