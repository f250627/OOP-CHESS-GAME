// Check to see if the path is clear for a piece to move
bool isPathClear(int sx, int sy, int dx, int dy) {
    int xStep = (dx == sx) ? 0 : (dx > sx ? 1 : -1);
    int yStep = (dy == sy) ? 0 : (dy > sy ? 1 : -1);
    int currX = sx + xStep;
    int currY = sy + yStep;

    while (currX != dx || currY != dy) {
        if (board[currX][currY] != nullptr) return false;
        currX += xStep;
        currY += yStep;
    }
    return true;
}

// Check if a square is attacked by any piece of given color
bool isSquareAttacked(int row, int col, char attackerColor) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            Piece* p = board[i][j];
            if (p && p->getColor() == attackerColor) {
                if (p->isValidMove(i, j, row, col)) {
                    if (p->getSymbol() == 'N' || isPathClear(i, j, row, col))
                        return true;
                }
            }
        }
    }
    return false;
}

// Check if king of given color is in check
bool isCheck(char kingColor) {
    // Find king position
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            Piece* p = board[i][j];
            if (p && p->getSymbol() == 'K' && p->getColor() == kingColor) {
                char attackerColor = (kingColor == 'W') ? 'B' : 'W';
                return isSquareAttacked(i, j, attackerColor);
            }
        }
    }
    return false;
}