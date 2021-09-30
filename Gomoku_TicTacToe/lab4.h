// lab4.h
// //Author: Christie Chen, christiec@wustl.edu
//        Lina Chang, n.chang@wustl.edu
//        Jiwoo Seo, jiwooseo@wustl.edu
// header file that holds general values used in the program

#pragma once
//variables for arguments
const int expected_argument_count = 2;
const int argnum_gomoku_dimension = 3;
const int argnum_gomoku_connect = 4;

//constants used in all games
const int sameString = 0;
const unsigned int minInclusive = 1; //universal for all games
enum valuesInGame {singleDimVal = 1, one_char = 1, col_format = 9, space_val = 1};  //enum for dimension intricacies to avoid hardcoding

//gomoku values
const int go_defaultCon = 5;
const int go_defaultDim = 20;
const int go_dimensionAdd = 1;

//tictactoe specific 
const unsigned int ticMaxExclusive = 4;   // tictactoe board dimensions to avoid hard-coded constants
const int ttt_dim = 5;
const int ttt_con = 3;
enum valuesTtt {first = 1, second = 2, third = 3}; //enum for tictactoe board to avoid hard-coded constants

//enums not private, allowed as stated on Piazza
enum arrayIndex { program_name, game_name, gomoku_dimension, gomoku_connect_num };
enum returnValue { success, not_expected_argnum, result_quit, result_draw, bad_allocation };  //success for done()
enum gameStatus { coordinates_read_complete, coordinates_read_failed, quit, done, draw, progress };
int usageMsg(char*, char*);