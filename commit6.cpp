//
//// ================= MAIN =================
//
//int main() {
//    Board game;
//    game.setupBoard();
//
//    // Setting default turn to white 
//    char turn = 'W';
//    string input;
//    cout << "====================================\n";
//    cout << "        WELCOME TO CHESS GAME       \n";
//    cout << "====================================\n";
//    cout << "White (W) plays first | sx sy dx dy\n";
//
//    // Print the board once before the loop starts
//    game.display();
//
//    while (true) {
//        bool inCheck = game.isCheck(turn);
//        bool canMove = game.hasLegalMoves(turn);
//        // Check for King
//        if (inCheck) {
//            if (!canMove) {
//                cout << "CHECKMATE! " << (turn == 'W' ? "Black" : "White") << " wins!\n";
//                break;
//            }
//            cout << "CHECK! " << (turn == 'W' ? "White" : "Black") << " king is in danger!\n";
//        }
//        else if (!canMove) {
//            cout << "STALEMATE! It's a draw.\n";
//            break;
//        }
//
//        cout << "Player " << turn << " move: ";
//        int sx, sy, dx, dy;
//
//        // Checking if user enters further input or wants to end the game, as well as validating the input
//        if (!(cin >> sx >> sy >> dx >> dy)) {
//            cin.clear();
//            cin >> input;
//            if (input == "exit" || input == "quit") break;
//            cout << "Invalid input! Try again.\n";
//            cin.ignore(1000, '\n');
//            continue; // Goes back to the top, but does not reprint the board
//        }
//
//        // Range check
//        if (sx < 0 || sx > 7 || sy < 0 || sy > 7 || dx < 0 || dx > 7 || dy < 0 || dy > 7) {
//            cout << "Out of range! Try again.\n";
//            continue;
//        }
//
//        // Move check
//        if (!game.move(sx, sy, dx, dy, turn)) {
//            cout << "Invalid Move! Try again.\n";
//            continue;
//        }
//
//        // Switch turns and only print the board when a valid move happens
//        turn = (turn == 'W') ? 'B' : 'W';
//        game.display();
//    }
//    return 0;
//}