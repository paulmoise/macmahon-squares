#include <iostream>
#include "board.hpp"
#include <chrono>




int main() {

    using std::chrono::high_resolution_clock;
    using std::chrono::milliseconds;
    using std::chrono::duration;


//    std:: string filePath = "/mnt/c/Users/pgangbadja/CLionProjects/macmahon-squares/data/4x4_colorv2.txt";
    std:: string filePath = "/mnt/c/Users/pgangbadja/CLionProjects/macmahon-squares/data/5x5_colorv2.txt";
//    std:: string filePath = "/mnt/c/Users/pgangbadja/CLionProjects/macmahon-squares/data/6x6_colorv2.txt";
    Board board = Board(filePath);

    auto t1 = high_resolution_clock::now();
    board.solve();
    auto t2 = high_resolution_clock::now();

    duration<double, std::milli> ms_double = t2 - t1;

//     board.init();
    board.displayBoard();
    std::cout << ms_double.count() << "ms\n";
    // Piece p = Piece();
    // p.display()


    return 0;
}