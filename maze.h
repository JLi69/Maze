#include <list>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include "graphics.h"
#pragma once
using namespace gamegraphics;
using namespace std;

const int cellsize = 14;

namespace maze {
	//This will be a "cell" in the maze
	class Cell {
	public:
		int x;
		int y;
		bool empty = false;

		Cell(int xcor, int ycor) {
			x = xcor;
			y = ycor;
		}
		
		Cell() {
			//Default constructor
			//Does nothing
		}
	};

	//Generate the maze (Prim's Randomized Algorithm)
	list<Cell> generate(int width, int height) {
		//Set a random seed
		srand(time(NULL));
		//This will be the maze
		list<Cell> maze;
		//Generate the cells that will be the blocks of the maze
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				Cell c = Cell(j*cellsize, i*cellsize);
				maze.push_back(c);
			}
		}

		//Generate the passages
		list<Cell> frontiercells;
		//Get a random cell
		Cell c;
		list<Cell>::iterator it = maze.begin();

		int x = (rand() % ((width - 1) / 2) + 1) * 2 - 1;
		int y = (rand() % ((height - 1) / 2) + 1) * 2 - 1;

		for (it; it != maze.end(); it++) {
			Cell c2 = *it;

			if (c2.x == x * cellsize && c2.y == y * cellsize) {
				break;
			}
		}

		c = *it;
		c.empty = true;
		*it = c;

		//Calculate the frontier cells
		for (list<Cell>::iterator it2 = maze.begin(); it2 != maze.end(); it2++) {
			Cell c2 = *it2;

			if (abs(c2.x - c.x) == 2 * cellsize && c2.y == c.y && !c2.empty) {
				frontiercells.push_back(c2);
			}
			else if (abs(c2.y - c.y) == 2 * cellsize && c2.x == c.x && !c2.empty) {
				frontiercells.push_back(c2);
			}
		}

		//Loop
		while (frontiercells.size() > 0) {
			//get a random frontier cell
			list<Cell>::iterator it2 = frontiercells.begin();
			for (int i = 0; i < (rand() % frontiercells.size()); i++) {
				it2++;
			}
			Cell c2 = *it2;
			
			//Empty the cell
			for (list<Cell>::iterator it3 = maze.begin(); it3 != maze.end(); it3++) {
				Cell c3 = *it3;

				if (c3.x == c2.x && c3.y == c2.y) {
					c3.empty = true;
					*it3 = c3;
					break;
				}
			}

			//Calculate the frontier cells of this frontier cell
			list<Cell> frontiers;
			for (list<Cell>::iterator it3 = maze.begin(); it3 != maze.end(); it3++) {
				Cell c3 = *it3;

				//Calculate the frontier cells
				if (abs(c2.x - c3.x) == 2 * cellsize && c2.y == c3.y && c3.empty) {
					frontiers.push_back(c3);
				}
				else if (abs(c2.y - c3.y) == 2 * cellsize && c2.x == c3.x && c3.empty) {
					frontiers.push_back(c3);
				}

				if (abs(c2.x - c3.x) == 2 * cellsize && c2.y == c3.y && !c3.empty) {
					//Make sure that the cell you're adding isn't a duplicate
					bool isduplicate = false;
					for (list<Cell>::iterator it4 = frontiercells.begin(); it4 != frontiercells.end(); it4++) {
						Cell c4 = *it4;
						if (c4.x == c3.x && c4.y == c3.y) {
							isduplicate = true;
							break;
						}
					}
					if (isduplicate) {
						continue;
					}
					frontiercells.push_back(c3);
				}
				else if (abs(c2.y - c3.y) == 2 * cellsize && c2.x == c3.x && !c3.empty) {
					//Make sure that the cell you're adding isn't a duplicate
					bool isduplicate = false;
					for (list<Cell>::iterator it4 = frontiercells.begin(); it4 != frontiercells.end(); it4++) {
						Cell c4 = *it4;
						if (c4.x == c3.x && c4.y == c3.y) {
							isduplicate = true;
							break;
						}
					}
					if (isduplicate) {
						continue;
					}
					frontiercells.push_back(c3);
				}
			}

			//Pick a random frontier cell from the list of frontier cells of a frontier cell
			Cell c4;
			if (frontiers.size() > 0) {
				list<Cell>::iterator it3 = frontiers.begin();
				for (int i = 0; i < (rand() % frontiers.size()); i++) {
					it3++;
				}
				c4 = *it3;
			}
			else {
				break;
			}

			//Empty the passage between them
			int x = (c2.x + c4.x) / 2;
			int y = (c2.y + c4.y) / 2;

			for (list<Cell>::iterator it4 = maze.begin(); it4 != maze.end(); it4++) {
				Cell c5 = *it4;
				if (c5.x == x && c5.y == y || c5.x == c4.x && c5.y == c4.y) {
					c5.empty = true;
					*it4 = c5;
				}
			}

			frontiercells.erase(it2);
		}

		//Create the exit
		for (list<Cell>::iterator it = maze.begin(); it != maze.end(); it++) {
			Cell c = *it;
			if (c.x == width*cellsize - 2*cellsize && c.y == 0) {
				c.empty = true;
				*it = c;
			}
		}
				
		//Return the maze
		return maze;
	}

	//Generate the maze (Wilson's Maze Generation Algorithm)
	list<Cell> generate2(int width, int height) {
		list<Cell> maze;

		//Return the maze
		return maze;
	}

	//Draw the maze
	void drawMaze(list<Cell> maze) {
		for (list<Cell>::iterator it = maze.begin(); it != maze.end(); it++) {
			Cell c = *it;
			if (!c.empty) {
				if (cellsize >= 14) {
					rect(c.x + cellsize + cellsize / 2 + 1, c.y + cellsize + cellsize / 2 + 1, cellsize - 1, cellsize - 1, RGB(0, 255, 0));
				}
				else {
					rect(c.x + cellsize + cellsize / 2, c.y + cellsize + cellsize / 2, cellsize, cellsize, RGB(0, 255, 0));
				}
			}
		}
	}
}
