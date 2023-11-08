#include<vector>
#include<string>
#include "piece.hpp"

class Board{
private:

    int dim; // board game dimension rowSize = colSize
    std::vector<std::vector<Piece>> grid;  // board matrix
    std::vector<Piece> availablePieces;    // all available pieces for the game
    // std::vector<Piece> usedPieces;         // usedPiece when soliving the game


public:
    Board();
    Board(std::string);
    ~Board();

    void initializeGrid( std::vector<std::vector<Piece>>, int);
    std::vector<Piece> getAvailablePieces();
    bool isValidState(int, int, Piece);
    bool areBorderPiecesHasSameColor(int, int, Piece);
    bool areAdjacentPiecesHasSameColor(int, int, Piece);
    bool hasValidAjacentPieces(int, int, Piece);

    bool solver(int, int);
    void solve();


    void setPiece(int, int, Piece);
    void displayBoard();       // display board matrix

    std::vector<std::vector<Piece>> getGrid();
    void setDim(int);
    void fillOnePiece(int, int, Piece);
    void init();
};
   
