#include <iostream>
#include "maze.h";
#include "Game.h"
using namespace std;
using namespace maze;
using namespace game;

const int width = 49;
const int height = 49;

//Yoinked from stack overflow
void ShowConsoleCursor(bool showFlag){
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag; // set the cursor visibility
	SetConsoleCursorInfo(out, &cursorInfo);
}

int main() {
	// Get console window handle
	HWND w = GetConsoleWindow();
	// Move window to required position
	MoveWindow(w, 0, 0, 770, 770, TRUE);

	ShowConsoleCursor(false);

	//Loading screen
	cout << "LOADING...";
	//Generate the maze
	list<Cell> maze = generate(width, height);
	//Clear te screen
	system("cls");
	//Instantiate the player
	Player player = Player(3*cellsize/2, (height-1)*cellsize - cellsize/2);
	//Draw the maze
	drawMaze(maze);
	//Draw the player
	player.draw();
	//Main game loop
	while (true) {
		player.update(maze);

		//Check if the player beat the level
		if (player.y < cellsize/2) {
			cout << "YOU WIN!";
			break;
		}

		Sleep(15);
	}

	while (true) {

	}
	return 0;
}