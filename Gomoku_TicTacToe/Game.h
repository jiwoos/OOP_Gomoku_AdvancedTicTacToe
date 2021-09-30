//Game.h
//Author: Christie Chen, christiec@wustl.edu
//        Lina Chang, n.chang@wustl.edu
//        Jiwoo Seo, jiwooseo@wustl.edu
// header file that has class declaration of basic game

#pragma once
#include "lab4.h"
#include "gamePieces.h"

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>



class GameBase{
public:
	GameBase(unsigned int w, unsigned int h, bool pTurn, std::string win, std::string longDisp, int cn);
	virtual bool done() = 0;
	virtual bool draw() = 0;
	int prompt(unsigned int&, unsigned int&);
	virtual int turn() = 0;
	int play();
	virtual void print() = 0;
	static GameBase * playWhich(int argc, char * argv[]);
protected:
	unsigned int width_;
	unsigned int height_;
	bool playerturn_; // true-"O"/"B" , false-"X"/"W"
	std::string winner_;
	std::vector<game_piece> vtr_; //all game pieces
	std::string longestDisplay_; //longest display within game pieces
	int connectNum_; //number of pieces in a row needed to win
};
