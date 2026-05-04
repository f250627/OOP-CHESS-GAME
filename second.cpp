#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <string>
#include <cstdlib>  // for exit()
#include <cmath>    // for abs()

using namespace std;

// ================= BASE CLASS =================
class Piece {
protected:
    char color;

public:
    Piece(char c) : color(c) {}
    virtual ~Piece() {}

    virtual bool isValidMove(int sx, int sy, int dx, int dy) = 0;
    virtual char getSymbol() = 0;
    char getColor() { return color; }
};

// ================= PIECES CLASSES =================

class Pawn : public Piece {
public:
    Pawn(char c) : Piece(c) {}

    bool isValidMove(int sx, int sy, int dx, int dy) override {
        if (color == 'W')
            return (dx == sx - 1 && dy == sy); // Basic move: Forward 1
        else
            return (dx == sx + 1 && dy == sy); // Basic move: Forward 1
    }

    char getSymbol() override { return 'P'; }
};

class Rook : public Piece {
public:
    Rook(char c) : Piece(c) {}
    bool isValidMove(int sx, int sy, int dx, int dy) override {
        return (sx == dx || sy == dy);
    }
    char getSymbol() override { return 'R'; }
};

class Knight : public Piece {
public:
    Knight(char c) : Piece(c) {}
    bool isValidMove(int sx, int sy, int dx, int dy) override {
        return (abs(dx - sx) == 2 && abs(dy - sy) == 1) ||
            (abs(dx - sx) == 1 && abs(dy - sy) == 2);
    }
    char getSymbol() override { return 'N'; }
};

class Bishop : public Piece {
public:
    Bishop(char c) : Piece(c) {}
    bool isValidMove(int sx, int sy, int dx, int dy) override {
        return abs(dx - sx) == abs(dy - sy);
    }
    char getSymbol() override { return 'B'; }
};

class Queen : public Piece {
public:
    Queen(char c) : Piece(c) {}
    bool isValidMove(int sx, int sy, int dx, int dy) override {
        return (sx == dx || sy == dy) || (abs(dx - sx) == abs(dy - sy));
    }
    char getSymbol() override { return 'Q'; }
};

class King : public Piece {
public:
    King(char c) : Piece(c) {}
    bool isValidMove(int sx, int sy, int dx, int dy) override {
        return abs(dx - sx) <= 1 && abs(dy - sy) <= 1;
    }
    char getSymbol() override { return 'K'; }
};

// ================= BOARD =================

class Board {
private:
    Piece* board[8][8];

public:
    Board() {
        for (int i = 0; i < 8; i++)
            for (int j = 0; j < 8; j++)
                board[i][j] = nullptr;
    }

    ~Board() {
        for (int i = 0; i < 8; i++)
            for (int j = 0; j < 8; j++)
                delete board[i][j];
    }

    void setupBoard() {
        for (int i = 0; i < 8; i++) {
            board[1][i] = new Pawn('B');
            board[6][i] = new Pawn('W');
        }
        board[0][0] = new Rook('B'); board[0][7] = new Rook('B');
        board[7][0] = new Rook('W'); board[7][7] = new Rook('W');
        board[0][1] = new Knight('B'); board[0][6] = new Knight('B');
        board[7][1] = new Knight('W'); board[7][6] = new Knight('W');
        board[0][2] = new Bishop('B'); board[0][5] = new Bishop('B');
        board[7][2] = new Bishop('W'); board[7][5] = new Bishop('W');
        board[0][3] = new Queen('B'); board[7][3] = new Queen('W');
        board[0][4] = new King('B'); board[7][4] = new King('W');
    }

    void display() {
        cout << "\n   0  1  2  3  4  5  6  7\n";
        cout << "  -----------------------\n";
        for (int i = 0; i < 8; i++) {
            cout << i << "| ";
            for (int j = 0; j < 8; j++) {
                if (board[i][j])
                    cout << board[i][j]->getColor() << board[i][j]->getSymbol() << " ";
                else
                    cout << ".  ";
            }
            cout << "|" << i << endl;
        }
        cout << "  -----------------------\n";
        cout << "   0  1  2  3  4  5  6  7\n\n";
    }

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

    bool isCheck(char kingColor) {
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

    bool move(int sx, int sy, int dx, int dy, char turn) {
        if (!board[sx][sy]) return false;
        Piece* p = board[sx][sy];
        if (p->getColor() != turn) return false;
        if (board[dx][dy] && board[dx][dy]->getColor() == turn) return false;
        if (!p->isValidMove(sx, sy, dx, dy)) return false;
        if (p->getSymbol() != 'N' && !isPathClear(sx, sy, dx, dy)) return false;

        Piece* captured = board[dx][dy];
        board[dx][dy] = board[sx][sy];
        board[sx][sy] = nullptr;

        if (isCheck(turn)) {
            board[sx][sy] = board[dx][dy];
            board[dx][dy] = captured;
            return false;
        }

        delete captured;
        return true;
    }
};

// ================= MAIN =================

int main() {
    Board game;
    game.setupBoard();
    char turn = 'W';
    string input;

    cout << "====================================\n";
    cout << "        WELCOME TO CHESS GAME       \n";
    cout << "====================================\n";
    cout << "White (W) plays first | sx sy dx dy\n";

    // Print the board ONCE before the loop starts
    game.display();

    while (true) {
        bool inCheck = game.isCheck(turn);
        bool canMove = game.hasLegalMoves(turn);

        if (inCheck) {
            if (!canMove) {
                cout << "CHECKMATE! " << (turn == 'W' ? "Black" : "White") << " wins!\n";
                break;
            }
            cout << "CHECK! " << (turn == 'W' ? "White" : "Black") << " king is in danger!\n";
        }
        else if (!canMove) {
            cout << "STALEMATE! It's a draw.\n";
            break;
        }

        cout << "Player " << turn << " move: ";
        int sx, sy, dx, dy;

        if (!(cin >> sx >> sy >> dx >> dy)) {
            cin.clear();
            cin >> input;
            if (input == "exit" || input == "quit") break;
            cout << "Invalid input! Try again.\n";
            cin.ignore(1000, '\n');
            continue; // Goes back to the top, but DOESN'T reprint the board
        }

        if (sx < 0 || sx > 7 || sy < 0 || sy > 7 || dx < 0 || dx > 7 || dy < 0 || dy > 7) {
            cout << "Out of range! Try again.\n";
            continue;
        }

        if (!game.move(sx, sy, dx, dy, turn)) {
            cout << "Invalid Move! Try again.\n";
            continue;
        }

        // --- SUCCESSFUL MOVE ---
        // Switch turns and ONLY print the board when a valid move happens!
        turn = (turn == 'W') ? 'B' : 'W';
        game.display();
    }
    return 0;
}