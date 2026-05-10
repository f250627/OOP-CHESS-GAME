// ================= PIECES CLASSES =================
// Inheritence: Derived piece classes from a common base class Piece.

// Class Pawn
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

// Class Rook
class Rook : public Piece {
public:
    Rook(char c) : Piece(c) {}
    bool isValidMove(int sx, int sy, int dx, int dy) override {
        return (sx == dx || sy == dy);
    }
    char getSymbol() override { return 'R'; }
};

// Class Knight
class Knight : public Piece {
public:
    Knight(char c) : Piece(c) {}
    bool isValidMove(int sx, int sy, int dx, int dy) override {
        return (abs(dx - sx) == 2 && abs(dy - sy) == 1) ||
            (abs(dx - sx) == 1 && abs(dy - sy) == 2);
    }
    char getSymbol() override { return 'N'; }
};

// Class Bishop
class Bishop : public Piece {
public:
    Bishop(char c) : Piece(c) {}
    bool isValidMove(int sx, int sy, int dx, int dy) override {
        return abs(dx - sx) == abs(dy - sy);
    }
    char getSymbol() override { return 'B'; }
};

// Class Queen
class Queen : public Piece {
public:
    Queen(char c) : Piece(c) {}
    bool isValidMove(int sx, int sy, int dx, int dy) override {
        return (sx == dx || sy == dy) || (abs(dx - sx) == abs(dy - sy));
    }
    char getSymbol() override { return 'Q'; }
};

// Class King
class King : public Piece {
public:
    King(char c) : Piece(c) {}
    bool isValidMove(int sx, int sy, int dx, int dy) override {
        return abs(dx - sx) <= 1 && abs(dy - sy) <= 1;
    }
    char getSymbol() override { return 'K'; }
};