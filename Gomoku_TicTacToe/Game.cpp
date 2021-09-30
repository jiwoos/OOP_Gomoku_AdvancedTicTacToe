//Game.cpp
//Author: Christie Chen, christiec@wustl.edu
//        Lina Chang, n.chang@wustl.edu
//        Jiwoo Seo, jiwooseo@wustl.edu
// This source file has functions and constructors that are needed to play a basic game
// prompt() lets user to put in coordinates values. It also allows user to quit and exit game.
// play() prints out the board, and calls turn() to keep the game on. 
//        checks done() and draw() to see if the user's latest move affected the result of the game.


#include "Game.h"
#include "lab4.h"
#include "TicTacToe.h"
#include "Gomoku.h"

#include <iomanip>
#include <string>
using namespace std;

//Constructor for a GameBase object. 
//This constructor takes in six parameters:
//w, h: width and height of the board, respectively.
//pTurn: true or false to signifiy which player's turn it is
//win: the winner of the game
//longDisp: the longest display string of a game piece
//connect: the number of pieces in a row needed to win the game
GameBase::GameBase(unsigned int w, unsigned int h, bool pTurn, string win, string longDisp, int connect)
    :width_(w), height_(h), playerturn_(pTurn), winner_(win), longestDisplay_(longDisp), connectNum_(connect)
{
    int dim = width_ * height_;
    //fill the board with empty game pieces
    for (int i = 0; i < dim; ++i) 
    {
        game_piece emptypiece(piece_color::no_color, "", " ");
        vtr_.push_back(emptypiece);
    }
};

//Prompts the player to input a valid location of a game piece. The location is
//then read into two unsigned ints. Validity of the location is checked in turn().
//prompt() takes in two parameters:
//x: the column (that it takes the reference of)
//y: the row (that it takes the reference of)
//
//Possible return values:
// This is an intermediate step, and these values will not returned from main.
//      0 - coordinates have been read correctly.
//      1 - coordinates could not be read
//      2 - the player has quit
int GameBase::prompt(unsigned int& x, unsigned int& y) 
{
    cout << ">> TYPE 'quit' OR 'x,y': " ;
    
    string userInput;
    cin >> userInput;
    cin.clear();
    cin.ignore(10000, '\n'); // it prevents cin to have some leftovers when input has a space after a character.

    //user quits the game
    if (userInput == "quit") 
    {
        cout << ">> QUITTING THE GAME..." << endl;
        return gameStatus::quit;
    }

    //no quit
    else 
    {
        //replace any instance of a comma with a space
        for (size_t i = 0; i < userInput.size(); ++i)
        {
            if (userInput[i] == ',')
            {
                userInput[i] = ' ';
            }
        }

        istringstream iss(userInput);
        //read into variables
        if ((iss >> x) && (iss >> y))
        {
            return gameStatus::coordinates_read_complete;
        }
        else
        {
            return gameStatus::coordinates_read_failed;
        }
    }
       
}

//plays a basic game.
//play() takes in no parameter.
//
//Possible return values:
//      0 - the game has been played successfully and there is a winner.
//      3 - the user has quit
//      4 - the game has ended in a draw
int GameBase::play()
{
    print();
    int status = gameStatus::progress;
    //while the player has not quit and the game is progressing
    while (status == gameStatus::progress) 
    {
        if (turn() == gameStatus::quit) 
        {
            return returnValue::result_quit;
        }
        if (done())
        {
            status = returnValue::success;
            cout << ">> PLAYER " << winner_ << " WON" << endl; 
        }
        if (draw()) //draw() implementation will not check for draws if done() is true
        {
            status = returnValue::result_draw;
            cout << ">> DRAW" << endl;
        }
    }
    return status;
}

//dynamically creates the appropriate game based on user input and returns a pointer to the created object.
//playWhich() takes in two parameters:
//argc: the number of arguments passed to the command line
//argv: a pointer to the arguments passed to the command line
//
//Possible returns:
//      nullptr - the game can not be created due to failed allocation or incorrect arguments
//      TicTacToeGame * - the user has chosen to play TicTacToe
//      GomokuGame *  - the user has chosen to play Gomoku
GameBase * GameBase::playWhich(int argc, char * argv[]) {
    //if argc has the baseline argument count
    if (argc == expected_argument_count) { //argc == 2

        string second = argv[arrayIndex::game_name];
        if (second.compare("TicTacToe") == sameString) {
            try {
                TicTacToeGame * game = new TicTacToeGame(); // a pointer to a dynamically allocated object
                return game;
            }
            //if allocation failed
            catch (bad_alloc & ba)
            {
                cout << "Failed Allocation:" << ba.what() << endl;
                return nullptr;
            }

        }
        else if (second.compare("Gomoku") == sameString) {
            try {
                GomokuGame* game = new GomokuGame(go_defaultDim, go_defaultCon); // a pointer to a dynamically allocated object
                return game;
            }
            //if allocation failed
            catch (bad_alloc & ba)
            {
                cout << "Failed Allocation:" << ba.what() << endl;
                return nullptr;
            }
        }
    }
    
    //if argc has an extra dimension meant for the gomoku game
    if (argc == argnum_gomoku_dimension) { //argc == 3

        string second = argv[arrayIndex::game_name];
        string third = argv[arrayIndex::gomoku_dimension];
        int dim; //dimensions
        int con; //how many pieces in a row to win
        try {
            dim = stoi(third); //storing the third string as a dimension
        }
        //not an integer
        catch (exception & err) {
            cout << "Dimension should be integers " << err.what()  << endl;
            return nullptr;
        }
        //ensure the call is for Gomoku
        if (second.compare("Gomoku") == sameString) {
            try {
                if (dim < 3) {
                    cout << "Rules:  Dimensions >= 3X3. Winning numbers >= 3" << endl;
                    return nullptr;
                }
                // when user's specifed dimension is smaller than 5, the connecting num cannot be 5.
                if (dim < 5) {
                    con = dim; 
                }
                else {
                    con = go_defaultCon; // when the user does not specify connecting num, default it with 5. 
                }
                dim = dim + go_dimensionAdd; // since the program is designed to be max-exclusive, we add 1 to make print out correct dimension
                GomokuGame* game = new GomokuGame(dim, con); 
                return game;
            }
            catch (bad_alloc & ba)
            {
                //allocation failed
                cout << "Failed Allocation:" << ba.what() << endl;
                return nullptr;
            }
        }

    }

    //if argc has two extra dimensions meant for the gomoku game
    if (argc == argnum_gomoku_connect) { //argc == 4 

        string second = argv[arrayIndex::game_name];
        string third = argv[arrayIndex::gomoku_dimension];
        string fourth = argv[arrayIndex::gomoku_connect_num];
        int dim; //dimensions of the board
        int con; //how many pieces in a row to win
        try {
            dim = stoi(third);
            con = stoi(fourth);
        }
        //not integers
        catch (exception& err) {
            cout << "Dimension and Winning numbers should be integers " << err.what() << endl;
            return nullptr;
        }
        
        if (second.compare("Gomoku") == sameString) {
            try {
                if (dim < 3 || con <3) {
                    cout << "Rules:  Dimensions >= 3X3. Winning numbers >= 3" << endl;
                    return nullptr;
                }
                if (con > dim) {
                    cout << "Dimensions should be bigger than Winning numbers" << endl;
                    return nullptr;
                }
                dim = dim + go_dimensionAdd; // since the program is designed to be max-exclusive, we add 1 to make print out correct dimension
                GomokuGame* game = new GomokuGame(dim, con); // a pointer to a dynamically allocated object
                return game;
            }
            catch (bad_alloc& ba)
            {
                //allocation failed
                cout << "Failed Allocation:" << ba.what() << endl;
                return nullptr;
            }
        }

    }

    return nullptr; //return a 0 pointer

}