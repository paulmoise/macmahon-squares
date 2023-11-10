#ifndef HELPER_HPP
#define HELPER_HPP

#include<iostream>
#include <cstdlib>
#include <ctime>
#include<string>
#include<set>
#include<vector>
#include<sstream>
#include<fstream>
#include<map>

#include "piece.hpp"

namespace helper_function{

    void split(const std::string & line, const char delimiter, std::vector<std::string> & output){
        std::stringstream ss(line);
        std::string s;
        while (std::getline(ss, s, delimiter)){
            output.push_back(s);
        }
    }

    Piece getInitilializeRandomPiece(){
        static const Color colors[3]  = { R , G, B};
        srand(time(NULL));
        Piece p = Piece();
        p.setTop(colors[rand() % 3]);
        p.setBottom(colors[rand() % 3]);
        p.setRight(colors[rand() % 3]);
        p.setLeft(colors[rand() % 3]);
        return p;
    }

    Piece getInitilializePiece(Color top, Color bottom, Color right, Color left){
        return Piece(top, bottom, right, left);
    }



    std::vector<Piece> readPiecesFromFile(std::string piecesFilePath){

        std::vector<Piece> pieces;

        int rowSize, colSize;
        std::map<std::string, Color> colorMap {
                { "R", R },
                { "G", G },
                { "B", B }
        };

        std::ifstream boardPiecesFileStream;
        std::string line;
        const char delimiter = ' ';

        boardPiecesFileStream.open(piecesFilePath);

        if(boardPiecesFileStream.is_open()){

            std::getline(boardPiecesFileStream, line);
            std::vector<std::string> output;
            helper_function::split(line, delimiter, output);

            int rowSize = stoi(output.front());
            int colSize = stoi(output.back());

            for(int i = 0; i < rowSize*colSize; i++){
                std::getline(boardPiecesFileStream, line);
                std::vector<std::string> output;
                helper_function::split(line, delimiter, output);
                Piece p = Piece(output[0][0], output[1][0], output[2][0], output[3][0]);
                pieces.push_back(p);

            }

            boardPiecesFileStream.close();
            return pieces;
        }
        std::cout << "File can't be open" << std::endl;
        return pieces;



    }

    void initializeGrid( std::vector<std::vector<Piece>> & grid, int dim){
        //  std::cout << dim << std::endl;

        for (int i = 0; i < dim; i++){
            grid.push_back(std::vector<Piece>(dim));
        }

        for (int i = 0; i < dim; i++){
            for (int j = 0; j < dim; j++){
                grid[i][j] = Piece();
            }
        }
    }


}


#endif
