#include <iostream>
#include "board.hpp"
#include "helper.hpp"
#include <chrono>
#include <math.h>
#include <atomic>
#include <thread>
#include <csignal>
#include <algorithm>

std::atomic<bool> solutionFound(false);
std::atomic<int> nThread(0);



void displayPiece(std::vector<Piece> rowPieces) {

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

void displaySeparator(int n) {
    for (int i = 0; i < n; i++) {
        std::cout << "_";
    }
    std::cout << "\n";
}


void displayBoard(std::vector<std::vector<Piece>> & grid, int dim) {
    // display board with pieces

    int sep = 15;

    if (dim == 5)
        sep = 19;

    if (dim == 6)
        sep = 23;

    displaySeparator(sep);
    for (int i = 0; i < dim; i++) {
        displayPiece(grid[i]);
        displaySeparator(sep);
    }

}


bool areBorderPiecesHasSameColor(std::vector<std::vector<Piece>> &grid, int indexRow, int indexCol, Piece p, int dim) {
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


bool hasValidAjacentPieces(std::vector<std::vector<Piece>> &grid, int indexRow, int indexCol, Piece p) {
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

bool isValidState(std::vector<std::vector<Piece>> &grid, int indexRow, int indexCol, Piece p, int dim) {

    bool rule1 = areBorderPiecesHasSameColor(grid, indexRow, indexCol, p, dim);
    bool rule2 = hasValidAjacentPieces(grid, indexRow, indexCol, p);
    return rule1 && rule2;
}


bool backtracking(std::vector<std::vector<Piece>> &grid, std::vector<Piece> &pieces, int indexRow, int indexCol, int dim) {

//    displayBoard(grid,dim);
//    sleep(2);

    if (solutionFound){
        return true;
    }

    if (indexRow == dim) {
        // Reached the end of the board, return true as the puzzle is solved
        solutionFound = true;
        return true;
    }
    // Loop through all available pieces
    for (auto &availablePiece: pieces) {
        if (!availablePiece.getIsUsed() && isValidState(grid, indexRow, indexCol, availablePiece, dim)) {
            // Try placing the current piece
            availablePiece.setIsUsed(true);
            grid[indexRow][indexCol] = availablePiece;

            // Explore the next position
            int nextRow = indexCol == dim - 1 ? indexRow + 1 : indexRow;
            int nextCol = indexCol == dim - 1 ? 0 : indexCol + 1;

            // Recur for the next position
            if (backtracking(grid, pieces, nextRow, nextCol, dim)) {
//                std::cout << nextCol << std::endl;
                solutionFound = true;
                return true; // Solution found
            }

            // Backtrack if the current placement doesn't lead to a solution
            availablePiece.setIsUsed(false);
            grid[indexRow][indexCol] = Piece(); // Reset the cell
        }
    }

    // No solution found
    return false;
}

void lauchBacktracking(std::vector<std::vector<Piece>> &grid, std::vector<Piece> &pieces, int i, int j, int dim, int taskId) {


    std::cout << "Task id =  " <<  taskId << "launch in " << " in thread Number = " << nThread << std::endl;
    nThread++;
    backtracking(grid, pieces, i, j, dim);
    nThread--;
    std::cout << "Task id =  " <<  taskId << "finished in " << " in thread Number = " << nThread << std::endl;

}

std::vector<std::vector<Piece>> threadPoolSolving(std::vector<std::vector<Piece>> grid, std::vector<Piece> pieces, int dim) {

    std::vector<int> tasks;
    for (int i = 0; i < dim * dim; i++) {
        tasks.push_back(i);
    }
    int i = 0;
    int j = 0;

    std::vector<Piece> filteredTasks;
    auto isValid = [](Piece p){
        return p.getLeft() == p.getTop();
    };
    std::copy_if(pieces.begin(), pieces.end(), std::back_inserter(filteredTasks), isValid);


    auto action = [&grid, &pieces, i, j, dim](int taskId) {
        grid[0][0] = pieces[24];
        pieces[2].setIsUsed(true);

        lauchBacktracking(grid, pieces, 0, 1, dim, taskId);

    };


    int taskId = 0;
    while (!(solutionFound or tasks.empty())) {

        if (nThread < 5) {
            std::thread t(action, taskId);
            taskId ++;

            tasks.pop_back();
            t.detach();
        }
    }

//    displayBoard(grid, dim);


//    std::thread t(action);
//    t.join();

    return grid;
}


int main() {
    std::cout << "I am here" << std::endl;

    using std::chrono::high_resolution_clock;
    using std::chrono::milliseconds;
    using std::chrono::duration;


//    std::string filePath = "/mnt/c/Users/pgangbadja/CLionProjects/macmahon-squares/data/4x4_colorv2.txt";
    std:: string filePath = "/mnt/c/Users/pgangbadja/CLionProjects/macmahon-squares/data/5x5_colorv2.txt";
//    std:: string filePath = "/mnt/c/Users/pgangbadja/CLionProjects/macmahon-squares/data/6x6_colorv2.txt";

    std::vector<Piece> pieces = helper_function::readPiecesFromFile(filePath);
    int dim = pieces.size();
    dim = int(sqrt(dim));
    std::vector<std::vector<Piece>> grid;
    helper_function::initializeGrid(grid, dim);

    Board board = Board(dim, grid, pieces);

    auto t1 = high_resolution_clock::now();
    board.solve();
//board.solveByThread();
//    board.solveByThreadV2();

//    grid = threadPoolSolving(grid, pieces, dim);
//    displayBoard(grid, dim);

    auto t2 = high_resolution_clock::now();

    duration<double, std::milli> ms_double = t2 - t1;

    board.displayBoard();
    std::cout << ms_double.count() << " ms\n";
    std::cout << ms_double.count() / 1000 << " s\n";


    return 0;
}