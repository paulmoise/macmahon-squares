#include "piece.hpp"

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <map>
#include <string>


Piece::Piece(): left(O), top(O), right(O), bottom(O) {}
// Piece::Piece(Color top, Color bottom, Color right, Color left): top(top), bottom(bottom), right(right), left(left) {}
Piece::Piece(char left, char top, char right, char bottom): left(left), top(top), right(right), bottom(bottom), isUsed(false) {}


char Piece::getDirectionColor(Direction direction){

    std::map<Direction, char> direction_map {
            { TOP, this->top},
            { BOTTOM, this->bottom },
            { RIGHT, this->right },
            { LEFT, this->left }
    };
    return direction_map.at(direction);
}



void Piece::display(){
    std::cout << "Left:  " << getLeft() << std::endl;
    std::cout << "Top:   " << getTop() << std::endl;
    std::cout << "Right: " << getRight() << std::endl;
    std::cout << "Bottom:" << getBottom() << std::endl;
}


char & Piece::getTop(){return this->top;};
void  Piece::setTop(Color c){this->top = c; };
char & Piece::getBottom(){return this->bottom;};
void  Piece::setBottom(Color c){this->bottom = c; };
char & Piece::getRight(){return this->right;};
void  Piece::setRight(Color c){this->right = c; };
char & Piece::getLeft(){return this->left;};
void  Piece::setLeft(Color c){this->left = c; };


bool Piece::getIsUsed(){ return this->isUsed;}
void Piece::setIsUsed(bool status){ this->isUsed = status;};

Piece::~Piece(){

}