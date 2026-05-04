#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <string>
#include <cstdlib>  // for exit()
#include <cmath>    // for abs()

using namespace std;

// ================= BASE CLASS =================
// Encapsulation: Used classes and private/protected data members

class Piece {
protected:
    char color;

public:
    Piece(char c) : color(c) {}
    virtual ~Piece() {}

    // Polymorphism: Used virtual functions for movement validation.
    virtual bool isValidMove(int sx, int sy, int dx, int dy) = 0;
    virtual char getSymbol() = 0;
    char getColor() { return color; }
};