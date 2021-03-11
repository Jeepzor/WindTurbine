#include <string>
#include "Position.h"

Position::Position() {
	for (int i = 0; i < column; i++)
	{
		for (int j = 0; j < row; j++)
		{
			discs[i][j] == 0;
		}
	}

	discs[4][4] = 1;
	discs[3][3] = 1;
	discs[3][4] = 2;
	discs[4][3] = 2;
}

Position::~Position() {

}

void Position::placeDisc(int x, int y) {
	if (isLegalMove(x, y)) {
		discs[x][y] = currentTurn;
	}
	else {
		return;
	}

	if (checkFlip(x, y, 1, 0)) {
		flipDiscs(x, y, 1, 0);
	}

	if (checkFlip(x, y, 0, 1)) {
		flipDiscs(x, y, 0, 1);
	}

	if (checkFlip(x, y, -1, 0)) {
		flipDiscs(x, y, -1, 0);
	}

	if (checkFlip(x, y, 0, -1)) {
		flipDiscs(x, y, 0, -1);
	}

	if (checkFlip(x, y, 1, 1)) {
		flipDiscs(x, y, 1, 1);
	}

	if (checkFlip(x, y, -1, -1)) {
		flipDiscs(x, y, -1, -1);
	}

	if (checkFlip(x, y, -1, 1)) {
		flipDiscs(x, y, -1, 1);
	}

	if (checkFlip(x, y, 1, -1)) {
		flipDiscs(x, y, 1, -1);
	}

	swapTurn();
	calculateScores();
}

void Position::swapTurn() {
	currentTurn = PLAYER * (currentTurn != PLAYER) + COMPUTER * (currentTurn != COMPUTER);
}

bool Position::isLegalMove(int x, int y) {
	if (x < 0 || x > 7 || y < 0 || y > 7) {
		return false;
	}
	else if (discs[x][y] != 0) {
		return false;
	}
	else {
		return wouldFlipDiscs();
	}
}

bool Position::wouldFlipDiscs() {
	return checkFlip(1, 0) || checkFlip(-1, 0) || checkFlip(0, 1) || checkFlip(0, -1)
		|| checkFlip(1, 1) || checkFlip(-1, -1) || checkFlip(-1, 1) || checkFlip(1, -1);
}

bool Position::checkFlip(int x, int y, int dx, int dy) {
	if (dy == 1 && y == 7 || dy == -1 && y == 0) {
		return false;
	}
	else if (dx == 1 && x == 7 || dx == -1 && x == 0) {
		return false;
	}
	else if (discs[x + dx][y + dy] != getOponent()) {
		return false;
	}
	else {
		int i = 1;
		while (x + dx * i >= 0 && x + dx * i < row && y + dy * i >= 0 && y + dy * i < column)
		{
			if (discs[x + dx * i][y + dy * i] == 0) {
				return false;
			}
			else if (discs[x + dx * i][y + dy * i] == currentTurn) {
				return true;
			}
			i++;
		}
		return false;
	}
}

void Position::flipDiscs(int x, int y, int dx, int dy) {
	int i = 1;
	while (x + dx * i >= 0 && x + dx * i < row && y + dy * i >= 0 && y + dy * i < column)
	{
		if (discs[x + dx * i][y + dy * i] == 0) {
			return;
		}
		else if (discs[x + dx * i][y + dy * i] == currentTurn) {
			return;
		}
		else {
			discs[x + dx * i][y + dy * i] = currentTurn;
		}
		i++;
	}
}

int Position::getOponent() {
	if (currentTurn == PLAYER) {
		return COMPUTER;
	}
	else {
		return PLAYER;
	}
}

void Position::calculateScores() {
	scoreP1 = 0;
	scoreP2 = 0;
	for (int r = 0; r < row; r++)
	{
		for (int c = 0; c < column; c++)
		{
			if (discs[r][c] == PLAYER) {
				scoreP1 += 1;
			}
			else if (discs[r][c] == COMPUTER) {
				scoreP2 += 1;
			}
		}
	}
}


void Position::getScores(int& p1, int& p2) {
	p1 = 0;
	p2 = 0;
	for (int r = 0; r < row; r++)
	{
		for (int c = 0; c < column; c++)
		{
			if (discs[r][c] == PLAYER) {
				p1 += 1;
			}
			else if (discs[r][c] == COMPUTER) {
				p2 += 1;
			}
		}
	}
}


