// Gomoku.h
// Author: Christie Chen, christiec@wustl.edu
//        Lina Chang, n.chang@wustl.edu
//        Jiwoo Seo, jiwooseo@wustl.edu
// header file that has class declaration of Gomoku game and the ostream operator for Gomoku game

#pragma once
#include "gamePieces.h"
#include "Game.h"
#include "lab4.h"

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>

class GomokuGame : public GameBase {
	friend std::ostream& operator<< (std::ostream& o, const GomokuGame& s);
public:
	GomokuGame(int, int);
	virtual bool draw();
	virtual bool done();
	virtual int turn(); // true- black , false- white
	void print();
private:
	 unsigned int goComplete_val = 5; //number of pieces in a row required to win
	 unsigned int goMaxExclusive = 20; //default upper bound of game board
};


std::ostream& operator<< (std::ostream& o, const GomokuGame& s);

