// Snake Game
// by Claire Cashmore
#include <iostream>
#include <conio.h>
#include <ctime>
#include <cstdlib>
#include <windows.h>
using namespace std;
bool gameOver = false;
bool playAgain = true;
const int width = 20;
const int height = 20;
int badGuyTime = 0;
int x, y, fruitX, fruitY, badGuyX, badGuyY, score;
int tailX[100], tailY[100];
int nTail;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
//Stores the direction in dir
eDirection dir;

//Color Function
void SetColor(int value) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), value);
}
// Original Settings of the game
void Setup() {
	gameOver = false;
	// The direction is 0 so snake is not moving originally
	dir = STOP;
	// Coordinates of head to start in center screen
	x = width / 2;
	y = height / 2;

	//Randomly generates fruits on screen
	srand(time(0));
	fruitX = rand() % width;
	fruitY = rand() % height;
	score = 0;

	//Bad Guy's original location
	badGuyX = width / 2;
	badGuyY = height /2;
}
// Draws everything to screen
void Draw() {
	//clears console window terminal
	system("cls");

	// Creates the top wall
	for (int i = 0; i < width + 2; i++)
		cout << "_";
	cout << endl;

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			//Left wall
			if (j == 0)
				cout << "|";
			// Creates the head
			if (i == y && j == x) {
				SetColor(2);
				cout << "O";
				SetColor(7);
			}
			// creates the fruit
			else if (i == fruitY && j == fruitX) {
				SetColor(14);
				cout << "*";
				SetColor(7);
			}
			//creates bad guy AFTER player eats first fruit
			else if (i == badGuyY && j == badGuyX && score > 1) {
				SetColor(4);
				cout << "&";
				SetColor(7);
			}
			// Empty Playing Space or tail   
			else {
				// Draws the tail of the snake
				bool print = false;
				for( int k = 0; k < nTail; k++){
					if (tailX[k] == j && tailY[k] == i) {
						srand(time(0));
						SetColor(rand() % 15);
						cout << "o";
						SetColor(7);
						print = true;
					}
					
				}
				// If there isn't tail, print blank space
				if (!print)
					cout << " ";
			}
			// Right wall    
			if (j == width - 1)
				cout << "|";

		}
		cout << endl;
	}
	// Bottom wall
	for (int i = 0; i < width + 2; i++) {
		cout << "-";
	}
	cout << endl;
	cout << "Score: " << score << endl;
}
//Takes in the input from user
void Input() {

	// Sets  W A S D to UP LEFT DOWN RIGHT
	if (_kbhit()) {
		switch (_getch()) {
		case 'w':
			dir = UP;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'a':
			dir= LEFT;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 'x' :
			gameOver = true;
			break;
		}
	}

}
//Actual functions of the pieces we've built
void Logic() {

	//BAD GUY
	
	// this deals with the situation of going "through" walls
	if (badGuyX >= width) {
		badGuyX = 0;
		badGuyTime = rand() % 10;
	}
	else if (badGuyX < 0) {
		badGuyX = width - 1;
		badGuyTime = rand() % 10;
	}
	else if (badGuyY >= height) {
		badGuyY = 0;
		badGuyTime = rand() % 10;
	}
	else if (badGuyY < 0) {
		badGuyY = height - 1;
		badGuyTime = rand() % 10;
	}
	//This deals with movement of bad guy around playing field 
	//Notes: badGuyTime is to have random X and Y movements around the map
	else {
		if (badGuyTime < 25) {
			badGuyX++;
			badGuyTime = rand() % 100;
		}
		else if (badGuyTime > 24 && badGuyTime < 50) {
			badGuyY--;
			badGuyTime = rand() % 100;
		}
		else if (badGuyTime > 49 && badGuyTime < 75) {
			badGuyX--;
			badGuyTime = rand() % 100;
		}
		else if (badGuyTime > 74 && badGuyTime < 100) {
			badGuyY--;
			badGuyTime = rand() % 100;
		}
		else if (badGuyTime == 100) {
			badGuyTime = 0;
		}
	}

	
	//Creates tail following
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = x;
	tailY[0] = y;
	// Keeps previous location of tail and set new tail to that location
	for (int i = 1; i < nTail; i++) {
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
		
	}
	// Movement of head
	switch(dir){
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	default:
		break;
	}
	
	// Ends game if you hit bad guy
	if (x == badGuyX && y == badGuyY) {
		gameOver = true;
	}
	// Ends game if you run into walls
	if (x > width || x < 0 || y > height || y < 0)
		gameOver = true;
	for (int i = 0; i < nTail; i++) {
		if ((tailX[i] == x && tailY[i] == y) || (tailX[i] == badGuyX && tailY[i] == badGuyY))
			gameOver = true;
	}
	// IF we eat fruit
	if (x == fruitX && y == fruitY) {
		//Increase score by 10
		score += 10;
		//Randomly generates NEW fruits on screen
		srand(time(0));
		fruitX = rand() % width;
		fruitY = rand() % height;
		nTail++;
	}

}
// Asks to play again
void anotherRound() {
	char userInput;
	cout << "Would you like to play again? 'y' or 'n' " ;
	cin >> userInput;

	//while (userInput != 'y' || userInput != 'n') {
		if (userInput == 'y') {
			system("cls");
			nTail = 0;
			tailX[100] = 0;
			tailY[100] = 0;
			score = 0;
			gameOver = false;
			playAgain = true;
		}
		else if (userInput == 'n') {
			system("cls");
			cout << ":( Cowards! :( " << endl;
			playAgain = false;
		}

		//Trying to make it so it will ask again if you type the wrong thing
		//else {
			//system("cls");
			//cout << "That is not an option, try again." << endl;
			//cout << "Would you like to play again? 'y' or 'n' ";
			//cin >> userInput;

		}
	//}
//}
int main()
{
	while (playAgain == true) {
		Setup();
		while (!gameOver) {
			Draw();
			Input();
			Logic();
		}
		cout << "YOU lOST TRY AGAIN" << endl;
		anotherRound();
	}

	return 0;
}
