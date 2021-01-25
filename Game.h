#include <windows.h>
#include "maze.h"
#include "graphics.h"
#pragma once
using namespace maze;
using namespace gamegraphics;

namespace game {
	class Player {
	public:
		int x;
		int y;

		void update(list<Cell> maze) {
			if (GetAsyncKeyState(VK_UP)) {
				for (list<Cell>::iterator it = maze.begin(); it != maze.end(); it++) {
					Cell c = *it;
					if (c.x == x - cellsize / 2 && c.y == y - 3*cellsize/2 && !c.empty) {
						return;
					}
				}
				rect(x - cellsize / 2 + 3 * cellsize / 2, y - cellsize / 2 + 3 * cellsize / 2, cellsize, cellsize, RGB(0, 0, 0));
				y -= cellsize;
				draw();
			}
			else if (GetAsyncKeyState(VK_DOWN)) {
				for (list<Cell>::iterator it = maze.begin(); it != maze.end(); it++) {
					Cell c = *it;
					if (c.x == x - cellsize / 2 && c.y == y + cellsize/2 && !c.empty) {
						return;
					}
				}
				rect(x - cellsize / 2 + 3 * cellsize / 2, y - cellsize / 2 + 3 * cellsize / 2, cellsize, cellsize, RGB(0, 0, 0));
				y += cellsize;
				draw();
			}
			else if (GetAsyncKeyState(VK_LEFT)) {
				for (list<Cell>::iterator it = maze.begin(); it != maze.end(); it++) {
					Cell c = *it;
					if (c.x == x - 3*cellsize/2 && c.y == y - cellsize / 2 && !c.empty) {
						return;
					}
				}
				rect(x - cellsize / 2 + 3 * cellsize / 2, y - cellsize / 2 + 3 * cellsize / 2, cellsize, cellsize, RGB(0, 0, 0));
				x -= cellsize;
				draw();
			}
			else if (GetAsyncKeyState(VK_RIGHT)) {
				for (list<Cell>::iterator it = maze.begin(); it != maze.end(); it++) {
					Cell c = *it;
					if (c.x == x + cellsize / 2 && c.y== y - cellsize / 2 && !c.empty) {
						return;
					}
				}
				rect(x - cellsize / 2 + 3 * cellsize / 2, y - cellsize / 2 + 3 * cellsize / 2, cellsize, cellsize, RGB(0, 0, 0));
				x += cellsize;
				draw();
			}
		}

		void draw() {
			circle(x + 3*cellsize/2, y + 3*cellsize/2, cellsize / 2, RGB(255, 255, 0));
		}

		//Constructor
		Player(int xcor, int ycor) {
			x = xcor;
			y = ycor;
		}
	};
}