
#ifndef Position_H
#define Position_H

#include "../wind.h"
#include "move.h"

class Position {
public:
	static int counter;
	Position();
	void setTurn(int t) { currentTurn = t; };
	void swapTurn();
	void getScores(int& p1, int& p2);
	void setDisc(int x, int y, int disc);
	int getTurn() { return currentTurn; };
	int getDisc(int x, int y);
	int evaluate();
	void deepCopy(Position other);

private:
	bool isCorner(int x, int y);
	int column = 8;
	int row = 8;
	std::vector<std::vector<int>> discs;
	int currentTurn = 1;
	int scoreP1 = 2;
	int scoreP2 = 2;
};

#endif


