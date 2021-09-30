// gamePieces.h
//Author: Christie Chen, christiec@wustl.edu
//        Lina Chang, n.chang@wustl.edu
//        Jiwoo Seo, jiwooseo@wustl.edu
// header file that has declarations of enums (piece_color), functions, and struct (game_piece) that are used in the source file (gamePieces.cpp)


#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>


enum struct piece_color { red, black, white, blue, invalid_color, no_color };
std::string enumToString(piece_color);
piece_color stringToEnum(std::string);

struct game_piece {
    game_piece(piece_color color, std::string name, std::string display);
    piece_color color_;
    std::string name_;
    std::string display_;
};
