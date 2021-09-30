//lab4.cpp
//Author: Christie Chen, christiec@wustl.edu
//        Lina Chang, n.chang@wustl.edu
//        Jiwoo Seo, jiwooseo@wustl.edu
// This source file has the main function, where program execution begins and ends. The main function plays 
// a game depending on the parameters passed to the command line. 
//usageMsg() instructs the user how to use the program

#include "lab4.h"
#include "Game.h"
#include <iostream>

using namespace std;

int main(int argc, char * argv[])
{
    if (argc < expected_argument_count)
    {
        //invalid number of arguments
        char astring[] = "'TicTacToe' or 'Gomoku'";
        char* toString = astring;
        return usageMsg(argv[program_name], toString);
    }

    GameBase * game = GameBase::playWhich(argc, argv);
    if (game == nullptr) {
        //invalid arguments passed in
        char astring[] = "'TicTacToe' or 'Gomoku' or 'Gomoku 5 5'";
        char* toString = astring;
        return usageMsg(argv[program_name], toString);
    } 
    shared_ptr<GameBase> sharedGame(game);
    return sharedGame->play();
}


//usageMessage() gives the user a template to use on the command line when the user inputs
//an incorrect number of arguments or invalid arguments.
//returns 1 - unexpected number of arguments
int usageMsg(char* cs1, char* cs2)
{
    cout << "usage: " << cs1 << " " << cs2 << endl;
    return not_expected_argnum;
}