//tictactoe.cpp
//Author: Christie Chen, christiec@wustl.edu
//        Lina Chang, n.chang@wustl.edu
//        Jiwoo Seo, jiwooseo@wustl.edu
// This source file has functions and constructors that are needed to play a TicTacToe game
// done() and draw() check the currently occupied squares and tells if the game is over (by win or draw)
// turn() receives input values from prompt() and determines if those values are valid.
//        is responsible for keeping track of the turn.

#include "tictactoe.h"
using namespace std;

//Default constructor for the TicTacToe class
TicTacToeGame::TicTacToeGame() : GameBase(ttt_dim, ttt_dim, true, " ", "X", ttt_con) 
{
}


//return if a player has won the game
//done() takes in no parameters
//
//returns true if a player has won; otherwise, false
bool TicTacToeGame::done() 
{

    bool returnVal = false; 
    // width*row# + col# formula given in lab instructions
    // checking row
    
    int dimSide = valuesInGame::singleDimVal;

    int f = valuesTtt::first;
    int s = valuesTtt::second;
    int t = valuesTtt::third;

    
    for (unsigned int y = minInclusive; y < ticMaxExclusive; ++y)
    {
        if (vtr_[width_*y+1].display_ != " ") 
        {  
            returnVal = (vtr_[width_ * y + f].display_ == vtr_[width_ * y + s].display_) && (vtr_[width_ * y + f].display_ == vtr_[width_ * y + t].display_);
        }
        if (returnVal) 
        {
            winner_ = (vtr_[width_ * y + f].display_);
            return returnVal;
        }
    }

    //checking col
    for (unsigned int x = minInclusive; x < width_ - dimSide; ++x)
    {
        if (vtr_[width_ * f + x].display_ != " ") 
        {  
            returnVal = (vtr_[width_ * f + x].display_ == vtr_[width_ * s + x].display_) && (vtr_[width_ * f + x].display_ == vtr_[width_ * t + x].display_);
        }
        if (returnVal) 
        {
            winner_ = (vtr_[width_ * f + x].display_);
            return returnVal;
        }
    }

    //checking diagonal
    if (vtr_[width_ * f + f].display_ != " ") {
        winner_ = (vtr_[width_ * s + s].display_);
        returnVal = (vtr_[width_ * f + f].display_ == vtr_[width_ * s + s].display_) && (vtr_[width_ * f + f].display_ == vtr_[width_ * t + t].display_);
    }
    if (vtr_[width_ * t + f].display_ != " ") {
        returnVal = (vtr_[width_ * t + f].display_ == vtr_[width_ * s + s].display_) && (vtr_[width_ * t + f].display_ == vtr_[width_ * f + t].display_);
        winner_ = (vtr_[width_ * s + s].display_);
    }
    return returnVal;
}


//return if the game has ended in a draw
//draw() takes in no parameters
//
//returns true if the board is filled; otherwise, false.
bool TicTacToeGame::draw() 
{
   
    if (done() == true) 
    {
        return false;
    }
  
    for (unsigned int y = minInclusive; y < ticMaxExclusive; ++y)
    {
        for (unsigned int x = minInclusive; x < ticMaxExclusive; ++x)
        {
            //formula given in lab instructions
            if (vtr_[(width_) * y + x].display_ == " ") 
            {
                return false;
            }
        }
    }
    return true;
}


//receives input values from prompt() and determines if those values are valid. If location is valid, 
//turn() puts the stone on the game board. Alternates the player
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
int TicTacToeGame::turn() 
{
    playerturn_ = !playerturn_;
    string turnDP;
    //alternate player
    if (!playerturn_) 
    {
        turnDP = "O";
    }
    else 
    {
        turnDP = "X";
    }
    cout << ">> TURN: PLAYER " << turnDP << endl;

    bool valid = false;
    unsigned int x, y; //location of piece
     
    while (!valid) 
    {
        int promptVal = prompt(x, y);
        if (promptVal == gameStatus::quit) 
        {
            return gameStatus::quit;
        }

        if (promptVal == gameStatus::coordinates_read_complete) 
        {
            if (x >= ticMaxExclusive || x < minInclusive || y >= ticMaxExclusive || y < minInclusive) {
                cout << ">> COORDINATE VALUES SHOULD RANGE FROM 1 TO 3" << endl;
            }
            else if ((vtr_[width_*y+x].display_ == " ")) 
            {
                        vtr_[width_*y+x].display_ = turnDP;
                       
                        cout << *this << endl;
                        cout << ">> PLAYER " << turnDP << ":" ;
                        for (unsigned int y = minInclusive; y < ticMaxExclusive; ++y)
                        {
                            for (unsigned int x = minInclusive; x < ticMaxExclusive; ++x)
                            {
                                if (vtr_[width_ * y + x].display_ == turnDP) 
                                {
                                    cout << " " << x << "," << y << ";";
                                    
                                    //keep track of the longest display
                                    if(turnDP.length() > longestDisplay_.length()){
                                        longestDisplay_ = turnDP;
                                    }

                                }
                            }
                        }
                        cout << endl;
                        valid = true;
            }
            else {
                cout << ">> COORDINATES "<< "'" << x << "," << y << "'" << " ARE TAKEN" << endl;
            }
      
        }
    }
    return gameStatus::progress;
}

//The insertion operator for a GomokuGame object.
//This operator takes in 2 parameters:
//o: an ostream (that it references)
//g: a TicTacToeGame object(that it references)
//
//returns the ostream passed to it
ostream& operator<< (ostream& o, const TicTacToeGame& g) 
{
    int spaceVal = valuesInGame::one_char;
    int dimSide = valuesInGame::singleDimVal;


    o << endl;
    size_t width = g.longestDisplay_.length() + spaceVal;

    o << setw(width);
    for (int i = g.height_ - dimSide; i >= 0; --i) 
    {
        o << i; //row labels
        for (unsigned int j = 0; j < g.width_; ++j) 
        {

            o << g.vtr_[g.width_ * i + j].display_ << setw(width); //pieces
        }
        o << endl; //end of one row
    }
    o << " ";
    for (unsigned int k = 0; k < g.width_; ++k) 
    {
        o <<  k << setw(width); //column labels
    }

    o << endl;
    return o;
}

//prints the game board
//print() takes in no parameters.
//print() is a void method
void TicTacToeGame::print()
{
    cout << *this << endl;
} 