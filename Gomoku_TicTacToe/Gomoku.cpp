//Gomoku.cpp
//Author: Christie Chen, christiec@wustl.edu
//        Lina Chang, n.chang@wustl.edu
//        Jiwoo Seo, jiwooseo@wustl.edu
// This source file has functions and constructors that are needed to play a Gomoku game
// done() and draw() check the currently occupied squares and tells if the game is over (by win or draw)
// turn() receives input values from prompt() and determines if those values are valid.
//        is responsible for keeping track of the turn.


#include "Gomoku.h"
using namespace std;

//Constructor for a GomokuGame object. 
//This constructor takes in two parameters:
//d: one dimension of the board. (square board, so one value used for both dimensions)
//c: the number of pieces in a row needed to win the game
GomokuGame::GomokuGame(int d, int c) : GameBase(d, d, true, " ", "X", c) {
    goComplete_val = c;
    goMaxExclusive = d;
};

//return if the game has ended in a draw
//draw() takes in no parameters
//
//returns true if there is no way to form 5 pieces of the same
//display value in a row; otherwise, false.
bool GomokuGame::draw()
{
    int dimSide = valuesInGame::singleDimVal;

    if (!done()) {
        GomokuGame copyBoardB = *this; //shallow copy
        GomokuGame copyBoardW = *this; //shallow copy

        //simulate what would happen if you put a game piece at location i,j for every empty space
        //i is rows, y dimension
        for (size_t i = goMaxExclusive - dimSide; i >= minInclusive; --i) {
            //j is cols, x dimension
            for (size_t j = minInclusive; j < goMaxExclusive; ++j) {
                size_t index = width_ * i + j; //formula given in lab instructions
                //black stone
                if (copyBoardB.vtr_[index].display_ == " ") {
                    copyBoardB.vtr_[index].display_ = "B";
                    copyBoardB.vtr_[index].name_ = "black stone";
                    copyBoardB.vtr_[index].color_ = piece_color::black;
                }
                //white stone
                if (copyBoardW.vtr_[index].display_ == " ") {
                    copyBoardW.vtr_[index].display_ = "W";
                    copyBoardW.vtr_[index].name_ = "white stone";
                    copyBoardW.vtr_[index].color_ = piece_color::white;
                }
            }
        }
        
        //if you put a black/white stone on every space, are any winning rows formed
        if (copyBoardB.done() == true || copyBoardW.done() == true) {
            return false;
        }
        //no winning rows formed
        else if (copyBoardB.done() == false && copyBoardW.done() == false) {
            cout << endl;
            return true;

        }
    }

    return false;
}


//return if a player has won the game
//done() takes in no parameters
//
//returns true if a player has won; otherwise, false
bool GomokuGame::done()
{

    int initialPieceCount = valuesInGame::one_char;
    int dimSide = valuesInGame::singleDimVal;
    int count = initialPieceCount; // initial count is set to 1 b/c oneself is counted as connect-1
     
    // checking rows (from lower-left)
    for (unsigned int y = minInclusive; y < goMaxExclusive; ++y)
    {
        //with every row, restart the count. winning rows can not span different rows
        count = initialPieceCount;
        
        for (unsigned int x = minInclusive; x < goMaxExclusive - dimSide; ++x) 
        {
            //formulas given in lab instructions
            int index = width_ * y + x; 
            int prevIndex = width_ * y + (x + dimSide);
            
            //current piece is a stone, next piece is the same stone.
            if ((vtr_[index].display_ != " ") && (vtr_[index].display_ == vtr_[prevIndex].display_)) {
                ++count;
            }
            else {
                count = initialPieceCount;
            }
            //if can count goComplete_val pieces in a row, winner announced
            if (count == goComplete_val) {
                winner_ = vtr_[index].display_;
                return true;
            }
        }
       
    }

    //checking cols (from lower-left)
    for (unsigned int x = minInclusive; x < goMaxExclusive; ++x) {
        //reset count from checking rows
        count = initialPieceCount;
        
        for (unsigned int y = minInclusive; y < goMaxExclusive - dimSide; ++y) {
            //formulas given in lab instructions
            int index = width_ * y + x;
            int prevIndex = width_ * (y + dimSide) + x;

            //current piece is a stone, next piece is the same stone.
            if ((vtr_[index].display_ != " ") && (vtr_[index].display_ == vtr_[prevIndex].display_)) {
                ++count;
            }
            else {
                count = initialPieceCount;
            }
            if (count == goComplete_val) {
                winner_ = vtr_[index].display_;
                return true;
            }
        }
    }

    //reset count from checking columns
    count = initialPieceCount;
    //checking diagonals (/) from bottom-left corner
    for (unsigned int y = minInclusive; y < goMaxExclusive- goComplete_val + dimSide; ++y)
    {
        for (unsigned int x = minInclusive; x < goMaxExclusive - goComplete_val + dimSide; ++x)
        {
            //reset count with each new piece checked
            count = initialPieceCount;
            //formula given in lab instructions
            int index = width_ * y + x;
            if (vtr_[index].display_ != " ") 
            {
                //if goComplete_val pieces in a row found, return true
                for (unsigned int i = minInclusive; i < goComplete_val; ++i) 
                {
                    //formula given in lab instructions
                    int nextIndex = width_ * (y + i) + (x + i);
                    if (vtr_[index].display_ == vtr_[nextIndex].display_) {
                        ++count;
                    }
                    else {
                        count = initialPieceCount;
                    }
                    if (count == goComplete_val) {
                        winner_ = vtr_[index].display_;
                        return true;
                    }
                }
            }
            
        }

    }

    //reset count from checking diagonals (/)
    count = initialPieceCount;

    //checking diagonals (\) from upper-left corner 
    for (unsigned int y = goMaxExclusive - dimSide; y > goComplete_val - dimSide; --y)
    {
        for (unsigned int x = minInclusive; x < goMaxExclusive - goComplete_val + dimSide; ++x)
        {
            //reset count when each new piece is checked
            count = initialPieceCount;
            //formula given in lab instructions
            int index = width_ * y + x;

            if (vtr_[index].display_ != " ")
            {
                for (unsigned int i = minInclusive; i < goComplete_val; ++i)
                {
                    //formula given in lab instructions
                    int nextIndex = width_ * (y - i) + (x + i);
                    if (vtr_[index].display_ == vtr_[nextIndex].display_) {
                        ++count;
                    }
                    else {
                        count = initialPieceCount;
                    }
                    if (count == goComplete_val) {
                        winner_ = vtr_[index].display_;
                        return true;
                    }
                }
            }
        }
    }

    return false;
}



//receives input values from prompt() and determines if those values are valid. If location is valid, 
//turn() puts the stone on the game board. Alternates the player.
//a valid location satisfies these requirements:
//      1. location must be in bounds
//      2. location must not already have a game piece there
//      3. location must be two integers
//      4. location must be in this format: "x,y" format
//turn() takes in no parameters.
//Possible return values:
// This is an intermediate step, and these values will not returned from main.
//      2 - the player has quit
//      5 - the turn was successfully completed
int GomokuGame::turn()
{
    int dimSide = valuesInGame::singleDimVal;

    playerturn_ = !playerturn_; //very first turn becomes false
    string turnDP;
    if (!playerturn_) // black stone has to go first
    {
        turnDP = "B";
    }
    else
    {
        turnDP = "W";
    }
    cout << ">> TURN: PLAYER " << turnDP << endl;

    bool valid = false;
    unsigned int x, y; //locations of the piece

    while (!valid)
    {
        int promptVal = prompt(x, y);
        
        if (promptVal == gameStatus::quit)
        {
            return gameStatus::quit;
        }

        if (promptVal == gameStatus::coordinates_read_complete)
        {
            //check out of bounds
            if (x >= goMaxExclusive || x < minInclusive || y >= goMaxExclusive || y < minInclusive) {
                cout << ">> COORDINATE VALUES SHOULD RANGE FROM 1 TO " << width_ - dimSide << endl;
            }
            //check for empty space
            else if ((vtr_[width_ * y + x].display_ == " "))
            {
                
                vtr_[width_ * y + x].display_ = turnDP;

                cout << *this << endl;

                //print out player moves
                cout << ">> PLAYER " << turnDP << ":";
                for (unsigned int y = minInclusive; y < goMaxExclusive; ++y)
                {
                    for (unsigned int x = minInclusive; x < goMaxExclusive; ++x)
                    {
                        if (vtr_[width_ * y + x].display_ == turnDP)
                        {
                            cout << " " << x << "," << y << ";";

                            //keep track of the longest display
                            if (turnDP.length() > longestDisplay_.length()) {
                                longestDisplay_ = turnDP;
                            }

                        }
                    }
                }
                cout << endl;
                valid = true;
            }
            //check for taken spot
            else {
                cout << ">> COORDINATES " << "'" << x << "," << y << "'" << " ARE TAKEN" << endl;
            }

        }
    }
    return gameStatus::progress;
}


//prints the game board
//print() takes in no parameters.
//print() is a void method
void GomokuGame::print()
{
    cout << *this << endl;
}


//The insertion operator for a GomokuGame object.
//This operator takes in 2 parameters:
//o: an ostream (that it references)
//s: a GomokuGame object(that it references)
//
//returns the ostream passed to it
std::ostream& operator<<(std::ostream& o, const GomokuGame& s)
{
    int oneChar = valuesInGame::one_char;//space for one character
    int dimSide = valuesInGame::singleDimVal;
    int spaceVal = valuesInGame::one_char;

    o << endl;
    size_t width = s.longestDisplay_.length() + spaceVal;

    o << " ";
    //printing out columns correctly
    if ((s.height_ - oneChar) < valuesInGame::col_format) { //one digit or two digits
        o << " ";
    }

    //rows
    for (int i = s.height_ - dimSide; i >= dimSide; --i)
    {
        if (to_string(i).length() > s.longestDisplay_.length()) {
            width = to_string(i).length() + spaceVal;
        }
        else {
            width = s.longestDisplay_.length() + spaceVal + spaceVal; //need two spaces for the correct width
        }

        o << i << setw(width); //row labels


    //cols
        for (unsigned int j = dimSide; j < s.width_; ++j)
        {
            if (to_string(j).length() > s.longestDisplay_.length()) {
                width = to_string(j).length() + spaceVal;
            }
            else {
                width = s.longestDisplay_.length() + spaceVal + spaceVal; //need two spaces for the correct width
            }

            o << s.vtr_[s.width_ * i + j].display_ << setw(width); //pieces
        }
        o << endl; //end of one row
    }
    o << "X" << setw(width); //origin piece

    //col labels
    for (unsigned int k = 1; k < s.width_; ++k)
    {
        if (to_string(k).length() > s.longestDisplay_.length()) {
            width = to_string(k).length() + spaceVal;
        }
        else {
            width = s.longestDisplay_.length() + spaceVal + spaceVal; //need two spaces for the correct width
        }
        o << setw(width) << k ; // col labels
    }

    o << endl;
    o << endl;
    
     return o;
}
