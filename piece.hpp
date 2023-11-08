#ifndef PIECE_HPP
#define PIECE_HPP

#include<string>


enum Direction {
    TOP, BOTTOM, RIGHT, LEFT
};

enum Color {
    R = 'R',
    G = 'G',
    B = 'B',
    O = 'O'// to use as default initilizer
};

class Piece {

private:
    char left;
    char top;
    char right;
    char bottom;

    bool isUsed;

public:
    Piece();
    // Piece(Color, Color, Color, Color);
    Piece(char , char , char , char );
    char getDirectionColor(Direction);

    void display();
    char & getTop();
    void setTop(Color);
    char & getBottom();
    void setBottom(Color);
    char & getRight();
    void setRight(Color);
    char & getLeft();
    void setLeft(Color);

    bool getIsUsed();
    void setIsUsed(bool);

    ~Piece();


};

#endif
