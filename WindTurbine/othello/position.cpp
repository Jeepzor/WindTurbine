#include <string>
#include "Position.h"

Position::Position() {
	for (int i = 0; i < row; i++)
	{
		std::vector<int> row = { 0, 0, 0, 0, 0, 0, 0, 0 };
		discs.push_back(row);
	}
	discs[4][4] = 1;
	discs[4][3] = 2;
	discs[3][4] = 2;
	discs[3][3] = 1;
	/*
	discs[2][3] = 1;
	discs[1][3] = 1;
	discs[2][4] = 1;
	*/
}

int Position::getDisc(int x, int y) {
	return discs[x][y];
}

void Position::setDisc(int x, int y, int disc) {
	discs[x][y] = disc;
}

void Position::getScores(int& p1, int& p2) {
	p1 = 0;
	p2 = 0;
	for (int r = 0; r < row; r++)
	{
		for (int c = 0; c < column; c++)
		{
			if (discs[r][c] == 1) {
				p1 += 1;
			}
			else if (discs[r][c] == 2) {
				p2 += 1;
			}
		}
	}
}

void Position::swapTurn() {
	currentTurn = 1 * (currentTurn != 1) + 2 * (currentTurn != 2);
}

int Position::evaluate() {
	int p1 = 0;
	int p2 = 0;
	for (int r = 0; r < row; r++)
	{
		for (int c = 0; c < column; c++)
		{
			if (discs[r][c] == 1) {
				p1 += 1;
			}
			else if (discs[r][c] == 2) {
				p2 += 1;
			}
		}
	}

	return p1 - p2;
}


