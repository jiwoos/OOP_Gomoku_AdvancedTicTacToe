# Gomoku and Advanced TicTacToe
Gomoku game in C++

********************** variables/enum vars to avoid hard-coded constants are all documented in lab4.h ********************

Jiwoo Seo, Lina Chang, Christie Chen

This program prints out an interactive Tic-Tac-Toe game or Gomoku game for two players.
The command line must have the file name and either "TicTacToe" or "Gomoku" to run this program. If playing a gomoku game, the user has the option to 
personalize the board size and the amount of pieces in a row needed to win.


Program specifics: 
The following specifications were not explicitly stated in the labs. Here is how our program handles the following situations:
    Whitespace in the command line:
        As long as the string for the game name has no white space, the program runs. If the string is 
        split up (for example: "Tic     TacToe"), the usage message is sent.
        The game name must have the correct capitalization.
    
    Piece Location:
        If the location string ("x,y") is badly formatted with whitespace, the program will reprompt the user. For example,
        "2,     3" would mean a reprompt.
        
        If there are more than two locations passed in, the program will reprompt the user.

        If the inputted location has already been played by either player, the program alerts the player
        that there is already a game piece there and re-prompts the player.

Possible return values, documented in the lab4.h returnValue enum:
    0 - success: the game successfully played and ended in either a draw or a winner. 
    
    1 - not_expected_argnum: wrong number of arguments
    
    2 - result_quit: the player has entered "quit"

    3 - result_draw: the game has played and there is a draw
    
    4 – bad_allocation: the game was not able to be created.



TESTED CASES=======================================

1) wrong argument (wrong # of arguments, wrong name)

		H:\labs\lab3\lab3-jiwoos\lab3\Debug>lab3.exe arg1 arg2
		usage: lab4.exe 'TicTacToe' or 'Gomoku'
		=> errorlevel: 1  (returnVal::unexpeted_argnum)

		H:\labs\lab3\lab3-jiwoos\lab3\Debug>lab3.exe wronggame
		usage: lab4.exe 'TicTacToe' or 'Gomoku'
		=> errorlevel: 1 (returnVal::unexpeted_argnum)

		correct behavior. 1 represents wrong argument return value.


2) invalid inputs & user quits

    TicTacToe
		H:\labs\lab4\lab4-chenseochang\lab4\Debug>lab4.exe TicTacToe

		 4
		 3
		 2
		 1
		 0
		  0 1 2 3 4

		>> TURN: PLAYER O
		>> TYPE 'quit' OR 'x,y': invalid inputs
		>> TYPE 'quit' OR 'x,y': are just ignored
		>> TYPE 'quit' OR 'x,y': 10,10
		>> COORDINATE VALUES SHOULD RANGE FROM 1 TO 3
		>> TYPE 'quit' OR 'x,y': quit
		>> QUITTING THE GAME...

		=> errorlevel: (returnVal::result_quit)

	Gomoku
		H:\labs\lab4\lab4-chenseochang\lab4\Debug>lab4.exe Gomoku

		 19
		 18
		 17
		 16
		 15
		 14
		 13
		 12
		 11
		 10
		  9
		  8
		  7
		  6
		  5
		  4
		  3
		  2
		  1
		  X  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19

		>> TURN: PLAYER B
		>> TYPE 'quit' OR 'x,y': invalid inputs
		>> TYPE 'quit' OR 'x,y': are ignored
		>> TYPE 'quit' OR 'x,y': 25,25
		>> COORDINATE VALUES SHOULD RANGE FROM 1 TO 19
		>> TYPE 'quit' OR 'x,y': 1,30
		>> COORDINATE VALUES SHOULD RANGE FROM 1 TO 19
		>> TYPE 'quit' OR 'x,y': quit
		>> QUITTING THE GAME...

		=> errorlevel: (returnVal::result_quit)


3) Done Gomoku (won) 
	- Diagonal (/)

		  5              W
		  4           W
		  3        B
		  2     B
		  1  B
		  X  1  2  3  4  5


		>> PLAYER B: 1,1; 2,2; 3,3;
		>> PLAYER B WON

		=> errorlevel: 0(returnVal::success)

	- Diagonal (/) (board size 19x19, winning val = 5)

		 19
		 18
		 17
		 16
		 15
		 14
		 13                                W
		 12                             B
		 11                          B  W
		 10                       B  W  B  W
		  9                    B     W  B  W
		  8                 B        B  W
		  7
		  6
		  5
		  4
		  3
		  2
		  1
		  X  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19


		>> PLAYER B: 6,8; 9,8; 7,9; 10,9; 8,10; 10,10; 9,11; 10,12;
		>> PLAYER B WON

		=> errorlevel: 0(returnVal::success)

	- Horizontal win (board size: 19x19, winning val: 5)
	   
		 19
		 18
		 17
		 16
		 15
		 14
		 13
		 12
		 11                             W
		 10                             B
		  9                             B  W  B
		  8                             B  B  W
		  7                             B     W  W
		  6                             B
		  5
		  4
		  3
		  2
		  1                                                        W
		  X  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19


		>> PLAYER B: 10,6; 10,7; 10,8; 11,8; 10,9; 12,9; 10,10;
		>> PLAYER B WON

		=> errorlevel: 0(returnVal::success)

	-Diagonal (\) Boardsize: 5x5, winning val: 3
	    
		  5           W  B
		  4        W  B
		  3        B
		  2
		  1
		  X  1  2  3  4  5


		>> PLAYER B: 3,3; 4,4; 5,5;
		>> PLAYER B WON

		=> errorlevel: 0(returnVal::success)

	- vertical (Board size: 7x7, winning val 4)
		  7
		  6        B
		  5           W
		  4           B  W
		  3           B  W  W
		  2           B  W
		  1           B        B
		  X  1  2  3  4  5  6  7


		>> PLAYER B: 4,1; 7,1; 4,2; 4,3; 4,4; 3,6;
		>> PLAYER B WON

		=> errorlevel: 0(returnVal::success)



4) Draw Gomoku (board size: 3x3, winning val: 3) (using extra credit)
		input: H:\repos\Lab4\lab4\x64\Debug>lab4.exe Gomoku 3 3

		  3  B  W  W
		  2  W  B  B
		  1  B     W
		  X  1  2  3

		>> PLAYER W: 3,1; 1,2; 2,3; 3,3;
		>> DRAW

		// last move was (2,3) for white stone

		=> errorlevel: 3 (returnVal::result_draw)
	
 Draw Gomoku (board size: 5x5, winning val: 4) (using extra credit)
		input: :\repos\Lab4\lab4\x64\Debug>lab4.exe Gomoku 5 4
		  5  B     B  W  B
		  4  B  B  W     W
		  3  W  B  W  B  W
		  2  W  W  B  W  B
		  1  B  W  B  W  B
		  X  1  2  3  4  5
		  
		  >> PLAYER B: 1,1; 3,1; 5,1; 3,2; 5,2; 2,3; 4,3; 1,4; 2,4; 1,5; 3,5; 5,5;
		  >> DRAW

		=> errorlevel: 3 (returnVal::result_draw)

5) Draw TicTacToe
		 4
		 3  X X O
		 2  O O X
		 1  X O O
		 0
		  0 1 2 3 4

		>> PLAYER O: 2,1; 3,1; 1,2; 2,2; 3,3;
		>> DRAW

		=> errorlevel: 3 (returnVal::result_draw)

6) Done Gomoku (default dimensions and win values)

		- Vertical win
			 4
			 3    X
			 2  O X
			 1  O X O
			 0
			  0 1 2 3 4

			>> PLAYER X: 2,1; 2,2; 2,3;
			>> PLAYER X WON

			=> errorlevel: 0(returnVal::success)

		- Horizontal win
			 4
			 3      X
			 2    X
			 1  O O O
			 0
			  0 1 2 3 4

			>> PLAYER O: 1,1; 2,1; 3,1;
			>> PLAYER O WON

			=> errorlevel: 0(returnVal::success)

		- Diagonal win (/)
			 4
			 3  O
			 2    O
			 1  X X O
			 0
			  0 1 2 3 4

			>> PLAYER O: 3,1; 2,2; 1,3;
			>> PLAYER O WON

			=> errorlevel: 0(returnVal::success)

		- Diagonal win(\)
			 4
			 3  X O O
			 2    X O
			 1      X
			 0
			  0 1 2 3 4

			>> PLAYER X: 3,1; 2,2; 1,3;
			>> PLAYER X WON

			=> errorlevel: 0(returnVal::success)

	
=Additional Features==========================================================

Users can type in dimension and winning numbers to make custom gomoku. (only works for gomoku)
	size of the board should be greater than or equal to 3X3
	winning number should be greater than or equal to 3 and width/height of the board.

	Tested Cases:

	1) wrong game name for customized board

			H:\labs\lab4\lab4-chenseochang\lab4\Debug>lab4.exe TicTacToe 3 3
				usage: lab4.exe 'TicTacToe' or 'Gomoku' or 'Gomoku 5 5'

			=> errorlevel: 1 (returnVal::not_expected_argnum)




	2) correct arguments for customized board

			H:\labs\lab4\lab4-chenseochang\lab4\Debug>lab4.exe Gomoku 5 3

				5
				4
				3
				2
				1
				X  1  2  3  4  5


			>> TURN: PLAYER B



	3) 3X3 board, winning number: 3 / Diagonal win

			>> TURN: PLAYER B
			>> TYPE 'quit' OR 'x,y': 3,3

			  3        B
			  2     B
			  1  B  W  W
			  X  1  2  3


			>> PLAYER B: 1,1; 2,2; 3,3;
			>> PLAYER B WON

			=> errorlevel: 0 (success)




	4) 10X10 board, winning number: 4 / Vertical win

			>> TURN: PLAYER B
			>> TYPE 'quit' OR 'x,y': 1,4

			 10
			  9
			  8
			  7
			  6
			  5                       W
			  4  B
			  3  B
			  2  B                          W
			  1  B                          W
			  X  1  2  3  4  5  6  7  8  9 10


			>> PLAYER B: 1,1; 1,2; 1,3; 1,4;
			>> PLAYER B WON

			=> errorlevel: 0 (success)




	5) 20X20 board, winning number: 5 / horizontal win

			>> TURN: PLAYER B
			>> TYPE 'quit' OR 'x,y': 5,1

				20
				19
				18
				17
				16
				15
				14
				13
				12
				11
				10                             W
				9
				8                    W
				7
				6
				5
				4           W
				3
				2  B  W              W
				1  B  B  B  B  B
				X  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20


			>> PLAYER B: 1,1; 2,1; 3,1; 4,1; 5,1; 1,2;
			>> PLAYER B WON

			=> errorlevel: 0 (success)




	6) 6X6 board, winning number: 4 (oppostie diagonal win) 

			>> TURN: PLAYER B
			>> TYPE 'quit' OR 'x,y': 5,2

			  6
			  5     B
			  4        B
			  3  W        B
			  2              B
			  1  W  W
			  X  1  2  3  4  5  6


			>> PLAYER B: 5,2; 4,3; 3,4; 2,5;
			>> PLAYER B WON

			=> errorlevel: 0 (success)




	7) when the user only specifies the dimension
		If width/height >= 5, winning number is set to 5.
		If width/height is < 5, winning number is set to width/height


		(1) width/height >= 5 

			H:\labs\lab4\lab4-chenseochang\lab4\Debug>lab4.exe Gomoku 5
		
			  5
			  4
			  3
			  2
			  1
			  X  1  2  3  4  5


			   ====== after some moves..... =====


			>> TURN: PLAYER B
			>> TYPE 'quit' OR 'x,y': 5,5

			  5              B
			  4           B
			  3     W  B
			  2     B  W  W
			  1  B  W
			  X  1  2  3  4  5


			>> PLAYER B: 1,1; 2,2; 3,3; 4,4; 5,5;
			>> PLAYER B WON
			
			//player had to make 5 connecting pieces to win. 
			//If the winning number is not specified and width/height >= 5, then winning number = 5.

		
		(2) width/height < 5

		
			H:\labs\lab4\lab4-chenseochang\lab4\Debug>lab4.exe Gomoku 4

			  4
			  3
			  2
			  1
			  X  1  2  3  4


			  ====== after some moves..... =====


			>> TURN: PLAYER B
			>> TYPE 'quit' OR 'x,y': 4,1

				4
				3        B  W
				2     W  W  W
				1  B  B  B  B
				X  1  2  3  4


			>> PLAYER B: 1,1; 2,1; 3,1; 4,1; 3,3;
			>> PLAYER B WON
		
			//player had to make 4 connecting pieces to win. 
			//If the winning number is not specified and width/height >= 5, then winning number = width/height.





	8) Testing cases for dimension / winning number 

		(1) wrong values
			H:\labs\lab4\lab4-chenseochang\lab4\Debug>lab4.exe Gomoku wrong values
				Dimension and Winning numbers should be integers: invalid stoi argument
				usage: lab4.exe 'TicTacToe' or 'Gomoku' or 'Gomoku 5 5'

			=> errorlevel: 1 (returnVal::unexpected_argnum)

			//program checks the board size and winning number and prints out an appropriate error message (invalid stoi argument) along with a usage message.


		(2) if some other chracters follow after integer
			H:\labs\lab4\lab4-chenseochang\lab4\Debug>lab4.exe Gomoku 5,

			  5
			  4
			  3
			  2
			  1
			  X  1  2  3  4  5


			>> TURN: PLAYER B
			>> TYPE 'quit' OR 'x,y':

			//stoi() function ignores data types other than integers, so it prints out correct integer value of the input argument.
			//this is a correct behavior.

		(3) if input winning number is greater than input board size
			H:\labs\lab4\lab4-chenseochang\lab4\Debug>lab4.exe Gomoku 5 6
				Dimensions should be bigger than Winning numbers
				usage: lab4.exe 'TicTacToe' or 'Gomoku' or 'Gomoku 5 5'

			//program checks the board size and winning number and prints out an appropriate error message along with a usage message.
