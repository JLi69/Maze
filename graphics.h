#include <windows.h>
#include <math.h>
#pragma once

namespace gamegraphics {
	//Draw rectangle function
	void rect(int x, int y, int width, int height, COLORREF color) {
		//Get the console
		HWND console = GetConsoleWindow();
		HDC dc = GetDC(console);
		//Draw the rectangle
		for (int i = y; i < y + height; i++) {
			for (int j = x; j < x + width; j++) {
				SetPixel(dc, j, i, color);
			}
		}

		ReleaseDC(console, dc);
	}

	//Draw circle function
	void circle(int x, int y, int radius, COLORREF color) {
		//Get the console
		HWND console = GetConsoleWindow();
		HDC dc = GetDC(console);
		//Draw the circle
		for (int i = y - radius; i < y + radius; i++) {
			for (int j = x - radius; j < x + radius; j++) {
				if (sqrt(pow(x - j, 2) + pow(y - i, 2)) < radius) {
					SetPixel(dc, j, i, color);
				}
			}
		}

		ReleaseDC(console, dc);
	}
}