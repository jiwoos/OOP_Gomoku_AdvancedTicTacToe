// tictactoe.h
//Author: Christie Chen, christiec@wustl.edu
//        Lina Chang, n.chang@wustl.edu
//        Jiwoo Seo, jiwooseo@wustl.edu
// header file that has class declaration of tic-tac-toe game and the ostream operator for tic-tac-toe game

#pragma once
#include "gamePieces.h"
#include "Game.h"
#include "lab4.h"

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
class TicTacToeGame : public GameBase {
	friend std::ostream& operator<< (std::ostream& o, const TicTacToeGame& s);
public:
	TicTacToeGame();
	virtual bool draw();
	virtual bool done();
	virtual int turn();
	virtual void print();
};


std::ostream& operator<< (std::ostream& o, const TicTacToeGame& s);

