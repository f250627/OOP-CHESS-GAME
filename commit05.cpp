
// Check that a color in check has any more possible moves or not
bool hasLegalMoves(char turn) {
    for (int sx = 0; sx < 8; sx++) {
        for (int sy = 0; sy < 8; sy++) {
            Piece* p = board[sx][sy];
            if (p && p->getColor() == turn) {
                for (int dx = 0; dx < 8; dx++) {
                    for (int dy = 0; dy < 8; dy++) {
                        if (p->isValidMove(sx, sy, dx, dy)) {
                            if (p->getSymbol() != 'N' && !isPathClear(sx, sy, dx, dy)) continue;
                            if (board[dx][dy] && board[dx][dy]->getColor() == turn) continue;

                            Piece* captured = board[dx][dy];
                            board[dx][dy] = board[sx][sy];
                            board[sx][sy] = nullptr;
                            bool safe = !isCheck(turn);
                            board[sx][sy] = board[dx][dy];
                            board[dx][dy] = captured;

                            if (safe) return true;
                        }
                    }
                }
            }
        }
    }
    return false;
}

// Checking to make sure valid moves are entered by user according to rules of chess, along 
// with checking for check and game-ending conditions.
// Stimulate the move to verify it does not expose own King to check.
bool move(int sx, int sy, int dx, int dy, char turn) {
    if (!board[sx][sy]) return false;
    Piece* p = board[sx][sy];
    if (p->getColor() != turn) return false;
    if (board[dx][dy] && board[dx][dy]->getColor() == turn) return false;
    if (!p->isValidMove(sx, sy, dx, dy)) return false;
    if (p->getSymbol() != 'N' && !isPathClear(sx, sy, dx, dy)) return false;
    // Save state for undoing move if king is in danger
    Piece* captured = board[dx][dy];
    // Execute move
    board[dx][dy] = board[sx][sy];
    board[sx][sy] = nullptr;
    // Check if move puts own king in check
    if (isCheck(turn)) {
        board[sx][sy] = board[dx][dy];
        board[dx][dy] = captured;
        return false;
    }
    // Clean up captured piece
    delete captured;
    return true;
}
};