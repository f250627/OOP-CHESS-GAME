// ================= BOARD =================
// Composition: Included a Board class that contains Piece objects.

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
        // Prevents memory leaks by deleting all dynamically allocated pieces.
        for (int i = 0; i < 8; i++)
            for (int j = 0; j < 8; j++)
                delete board[i][j];
    }

    //  Creating the game board with all pieces 
    void setupBoard() {
        // Pawns
        for (int i = 0; i < 8; i++) {
            board[1][i] = new Pawn('B');
            board[6][i] = new Pawn('W');
        }
        // Rooks
        board[0][0] = new Rook('B');
        board[0][7] = new Rook('B');
        board[7][0] = new Rook('W');
        board[7][7] = new Rook('W');
        // Knights
        board[0][1] = new Knight('B');
        board[0][6] = new Knight('B');
        board[7][1] = new Knight('W');
        board[7][6] = new Knight('W');
        // Bishops
        board[0][2] = new Bishop('B');
        board[0][5] = new Bishop('B');
        board[7][2] = new Bishop('W');
        board[7][5] = new Bishop('W');
        // Queen
        board[0][3] = new Queen('B');
        board[7][3] = new Queen('W');
        // King
        board[0][4] = new King('B');
        board[7][4] = new King('W');
    }

    // Displays the chessboard with row numbers (0-7) on both sides and column numbers (0-7) above and below.
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

