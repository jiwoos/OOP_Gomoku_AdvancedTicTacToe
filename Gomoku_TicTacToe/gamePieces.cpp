//gamePieces.cpp
//Author: Christie Chen, christiec@wustl.edu
//        Lina Chang, n.chang@wustl.edu
//        Jiwoo Seo, jiwooseo@wustl.edu
// This source file has functions and a struct that interprets pieces in the input file.
//  



#include "gamePieces.h"
using namespace std;


//return the corresponding color of a piece_color as a lowercase string
//enumToString() takes in one parameter,
//pc: an enumerated color value
//
//returns the corresponding string
string enumToString(piece_color pc)
{
    if (pc == piece_color::red)
    {
        return "red";
    }
    else if (pc == piece_color::black)
    {
        return "black";
    }
    else if (pc == piece_color::white)
    {
        return "white";
    }
    else if (pc == piece_color::blue)
    {
        return "blue";
    }
    else if (pc == piece_color::no_color)
    {
        return "no_color";
    }
    else
    {
        return "invalid color";
    }
}

//return the corresponding piece_color value 
//stringToEnum() takes in one parameter,
//s: a string that corresponds to the enumerated values
//
// Possible return values (as enum, not casted to int):
//     0 - red
//     1 - black
//     2 - white
//     3 - blue
//     4 - invalid color
//     5 - no color
piece_color stringToEnum(string s)
{
    if (s == "red")
    {
        return piece_color::red;
    }
    else if (s == "black")
    {
        return piece_color::black;
    }
    else if (s == "white")
    {
        return piece_color::white;
    }
    else if (s == "blue")
    {
        return piece_color::blue;
    }
    else if (s == "no_color" || s == "" || s == "/t")
    {
        return piece_color::no_color;
    }
    else
    {
        return piece_color::invalid_color;
    }
}

//define struct
//name: string variable to hold the name of the piece
//display : string variable to represent how the piece should be displayed when a game board containing it is printed out
game_piece::game_piece(piece_color color, string name, string display)
    :color_(color), name_(name), display_(display) {}