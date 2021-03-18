
#ifndef Position_H
#define Position_H

#include "../wind.h"
#include "move.h"

class Position {
public:
	Position();
	void setTurn(int t) { currentTurn = t; };
	void swapTurn();
	void setStartPosition(bool playerBlack);
	void getScores(int& p1, int& p2) const;
	void setDisc(int x, int y, int disc);
	int getTurn() { return currentTurn; };
	int getDisc(int x, int y) const;
	int evaluate() const;

private:
	int isCorner(int x, int y) const;
	int isEdge(int x, int y) const;
	int isBad(int x, int y) const;
	
	std::vector<std::vector<int>> discs;
	int column = 8;
	int row = 8;
	int cornerValue = 15;
	int edgeValue = 3;
	int badValue = -1;
	int currentTurn = 1;
	int scoreP1 = 2;
	int scoreP2 = 2;

};

#endif


