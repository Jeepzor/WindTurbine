
#ifndef Position_H
#define Position_H

#include "../wind.h"

constexpr int PLAYER = 1;
constexpr int COMPUTER = 2;
class Position {
public:
	Position();
	void getScores(int& p1, int& p2);
	~Position();
	bool isLegalMove(int x, int y);

private:
	//Position(const Position& other);
	//const Position& operator=(const Position& other);
	void calculateScores();
	bool wouldFlipDiscs();
	bool checkFlip(int x, int y, int dx, int dy);
	void flipDiscs(int x, int y, int dx, int dy);
	void swapTurn();
	void placeDisc(int x, int y);
	int getOponent();
	int column = 8;
	int row = 8;
	int discs[8][8];
	int currentTurn = PLAYER;
	int scoreP1 = 2;
	int scoreP2 = 2;
};

#endif


