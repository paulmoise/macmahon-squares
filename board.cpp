#include "board.hpp"
#include "piece.hpp"
#include <iostream>
#include <string>
#include <thread>
#include <atomic>

std::atomic<bool> solved;


Board::Board() {}

void Board::setDim(int d) {
    this->dim = d;
}

//Board::Board(std::string filePiecesPath) {
//    int d = readPiecesFromFile(filePiecesPath, this->availablePieces);
//    setDim(d);
//    helper_function::initializeGrid(this->grid, this->dim);
//}

Board::Board(int dim, std::vector<std::vector<Piece>> grid, std::vector<Piece> pieces) :
        dim(dim),
        grid(grid),
        availablePieces(pieces) {
}
//
//Board::Board(Board &b) {
//    this->dim = b.dim;
//    this->grid = b.grid;
//    this->availablePieces = b.availablePieces;
//}


std::vector<Piece> Board::getAvailablePieces() { return this->availablePieces; }


bool Board::isValidState(int indexRow, int indexCol, Piece p) {

    bool rule1 = areBorderPiecesHasSameColor(indexRow, indexCol, p);
    bool rule2 = hasValidAjacentPieces(indexRow, indexCol, p);
    return rule1 && rule2;
}

bool Board::areBorderPiecesHasSameColor(int indexRow, int indexCol, Piece p) {
    // first rule of the game
    // if all the boarder have the same color

    // the first piece to be placed
    if (indexRow == 0 and indexCol == 0) {
        if (p.getTop() == p.getLeft()) {
            return true;
        }
        return false;
    }

    char topColor = grid[0][0].getTop();


    if (indexRow == dim - 1 && indexCol == dim - 1) {
        if (topColor == p.getRight() && p.getRight() == p.getBottom()) {
            return true;
        }
        return false;

    } else if (indexRow == 0 && indexCol == dim - 1) {
        if (p.getTop() == topColor && p.getRight() == topColor) {
            return true;
        }
        return false;
    } else if (indexRow == dim - 1 && indexCol == 0) {
        if (topColor == p.getLeft() && p.getLeft() == p.getBottom()) {
            return true;
        }
        return false;
    } else if (indexRow == 0 && indexCol > 0 && indexCol < dim - 1) {
        // the first row
        return p.getTop() == topColor;
    } else if (indexRow == dim - 1 && indexCol > 0 && indexCol < dim - 1) {
        // the last row
        return p.getBottom() == topColor;
    } else if (indexCol == 0 && indexRow > 0 && indexRow < dim - 1) {
        // for the cell who has j == 0 (first column)
        return p.getLeft() == topColor;
    } else if (indexCol == dim - 1 && indexRow > 0 && indexRow < dim - 1) {
        // for the cell who has j == dim - 1 (last column)
        return p.getRight() == topColor;
    }
    return true;

}


bool Board::hasValidAjacentPieces(int indexRow, int indexCol, Piece p) {
    // verify the second rule
    // check if the active piece to be placed in the specific postion
    // boarder color is matched to all his adjacent piece color

    if (indexRow == 0 && indexCol == 0) {
        return true;
    }

    // every element of the first line has just one adjacent piece
    if (indexRow == 0 && indexCol > 0) {
        if (grid[indexRow][indexCol - 1].getRight() == p.getLeft()) {
            return true;
        }
        return false;
    } else if (indexCol == 0 && indexRow > 0) {
        // every element of the first column has exactly one adjacent piece
        if (grid[indexRow - 1][indexCol].getBottom() == p.getTop()) {
            return true;
        }
        return false;
    } else {
        // for all other case, they have exactly two adjacent pieces (left, top)
        if (grid[indexRow - 1][indexCol].getBottom() == p.getTop() &&
            grid[indexRow][indexCol - 1].getRight() == p.getLeft()) {
            return true;
        }
        return false;
    }

}


bool Board::solver(int indexRow, int indexCol) {

    if (indexRow == dim) {
        // Reached the end of the board, return true as the puzzle is solved
        std::cout << "I reached the end" << std::endl;
        return true;
    }
    // Loop through all available pieces
    for (auto &availablePiece: availablePieces) {
        if (!availablePiece.getIsUsed() && isValidState(indexRow, indexCol, availablePiece)) {
            // Try placing the current piece
            availablePiece.setIsUsed(true);
            setPiece(indexRow, indexCol, availablePiece);

            // Explore the next position
            int nextRow = indexCol == dim - 1 ? indexRow + 1 : indexRow;
            int nextCol = indexCol == dim - 1 ? 0 : indexCol + 1;

            // Recur for the next position
            if (solver(nextRow, nextCol)) {
//                std::cout << nextCol << std::endl;
                return true; // Solution found
            }

            // Backtrack if the current placement doesn't lead to a solution
            availablePiece.setIsUsed(false);
            setPiece(indexRow, indexCol, Piece()); // Reset the cell
        }
    }

    // No solution found
    return false;
}

void Board::solve() {
//    for (auto &p: availablePieces){
//        setPiece(0, 0, p);
//        p.setIsUsed(true);
//        if(solver(0, 1)) {
//            std::cout << "Solution found" << std::endl;
//            break;
//        }else{
//            p.setIsUsed(false);
//            std::cout << "Solution not found" << std::endl;
//        }
//    }
    solver(0, 0);
}




void Board::displayPiece(std::vector<Piece> rowPieces) {

    for (int k = 0; k < 3; k++) {
        for (int i = 0; i < rowPieces.size(); i++) {

            if (k == 0) {

                std::cout << " ";
                std::cout << rowPieces[i].getTop();
                std::cout << " ";
                std::cout << "|";

            } else if (k == 1) {

                std::cout << rowPieces[i].getLeft();
                std::cout << " ";
                std::cout << rowPieces[i].getRight();
                std::cout << "|";

            } else {


                std::cout << " ";
                std::cout << rowPieces[i].getBottom();
                std::cout << " ";
                std::cout << "|";


            }

        }
        std::cout << "\n";
    }
}

void Board::displaySeparator(int n) {
    for (int i = 0; i < n; i++) {
        std::cout << "_";
    }
    std::cout << "\n";
}


void Board::displayBoard() {
    // display board with pieces

    int sep = 15;

    if (dim == 5)
        sep = 19;

    if (dim == 6)
        sep = 23;

    displaySeparator(sep);
    for (int i = 0; i < this->dim; i++) {
        displayPiece(this->getGrid()[i]);
        displaySeparator(sep);
    }

}

std::vector<std::vector<Piece>> Board::getGrid() {
    return this->grid;
}

void Board::setPiece(int i, int j, Piece p) {
    this->grid[i][j] = p;
}


void Board::fillOnePiece(int i, int j, Piece p) {

//    std::cout << i << j << std::endl;
    if (i == this->dim - 1 && j == this->dim - 1) {
        this->setPiece(i, j, p);
        fillOnePiece(i, j, p);
    }


    if (j < this->dim - 1) {
        this->setPiece(i, j + 1, p);
        fillOnePiece(i, j + 1, p);
    } else if (i < this->dim - 1) {
        this->setPiece(i + 1, j, p);
        fillOnePiece(i + 1, j, p);
    }
}


void Board::init() {
    setPiece(0, 0, this->getAvailablePieces()[0]);
    setPiece(0, 1, this->getAvailablePieces()[1]);
    setPiece(0, 2, this->getAvailablePieces()[2]);
    setPiece(0, 3, this->getAvailablePieces()[3]);
    setPiece(1, 0, this->getAvailablePieces()[4]);
    setPiece(1, 1, this->getAvailablePieces()[5]);
    setPiece(1, 2, this->getAvailablePieces()[6]);
    setPiece(1, 3, this->getAvailablePieces()[7]);
    setPiece(2, 0, this->getAvailablePieces()[8]);
    setPiece(2, 1, this->getAvailablePieces()[9]);
    setPiece(2, 2, this->getAvailablePieces()[10]);
    setPiece(2, 3, this->getAvailablePieces()[11]);
    setPiece(3, 0, this->getAvailablePieces()[12]);
    setPiece(3, 1, this->getAvailablePieces()[13]);
    setPiece(3, 2, this->getAvailablePieces()[14]);
    setPiece(3, 3, this->getAvailablePieces()[15]);
}


Board::~Board() {

}


bool Board::puzzleSolver(int indexRow, int indexCol) {

    if (solved){
        return true;
    }

    if (indexRow == dim) {
        // Reached the end of the board, return true as the puzzle is solved
        solved = true;
        return true;
    }
    // Loop through all available pieces
    for (auto &availablePiece: availablePieces) {
        if (!availablePiece.getIsUsed() && isValidState(indexRow, indexCol, availablePiece)) {
            // Try placing the current piece
            availablePiece.setIsUsed(true);
            setPiece(indexRow, indexCol, availablePiece);

            // Explore the next position
            int nextRow = indexCol == dim - 1 ? indexRow + 1 : indexRow;
            int nextCol = indexCol == dim - 1 ? 0 : indexCol + 1;

            // Recur for the next position
            if (solver(nextRow, nextCol)) {
//                std::cout << nextCol << std::endl;
                solved = true;
                return true; // Solution found
            }

            // Backtrack if the current placement doesn't lead to a solution
            availablePiece.setIsUsed(false);
            setPiece(indexRow, indexCol, Piece()); // Reset the cell
        }
    }

    // No solution found
    return false;
}

void Board::solveByThread() {
    std::vector<std::thread> threads;

    auto action = [this]( int i, int j) {
        this->puzzleSolver(i, j);
    };

    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            threads.emplace_back(action, i, j);
        }
    }

    for (auto &t: threads) {
        t.join();
    }
}

/*
 *
 * 1- shuffle a list of vector
 * 2- have a fix number of thread and run them parallel
 * 3- the fist who finish set the atomic variable
 */


void Board::solveByThreadV2() {
    std::vector<std::thread> threads;
    Board b = Board();
    b.availablePieces = this->availablePieces;
    b.grid = this->grid;
    b.dim = this->dim;


    auto action = [](Board b) {
        b.puzzleSolver(0, 0);
    };

    for (int i = 0; i < 5; i++) {
        threads.emplace_back(action, b);
    }



    for (auto &t: threads) {
        t.join();
    }
}







/*
 * 1- Create at least n*n n tasks
 * 2- Can be filtered to remove all pieces that can be removed from the vector of tasks
 * 3- Place the every piece at (0, 0)
 * 4- Start the backtracking in position (0,1)
 *
 *  lauchBacktracking(Board, Tuile, int, int){
 *   nbreThread++;
 *   backtracking()
 *   }
 *   while (1) == tant que j'ai de tache, tant que j'ai pas trouve une solution
 *
 */


