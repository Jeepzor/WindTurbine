
#ifndef BOARD_H
#define BOARD_H

#include "../wind.h"

constexpr int PLAYER = 1;
constexpr int COMPUTER = 2;
class Board{
public:
	static Board* getInstance(double xPos, double yPos) {
		return new Board(xPos, yPos);
	}

	void placeDisc();
	void draw();
	void update(double dt);
	
	~Board();
	

private:
	Board(double xPos, double yPos);
	Board(const Board& other) = delete;
	const Board& operator=(const Board& other) = delete;

	bool isLegalMove();
	bool wouldFlipDiscs();
	bool checkFlip(int x, int y);
	void flipDiscs(int x, int y);
	void swapTurn();

	int getOponent();

	void drawSquares();
	void drawChars();
	void drawDiscs();

	std::string characters[8] = {"A", "B", "C", "D", "E", "F", "G", "H" };
	int discs[8][8];
	double column = 8;
	double row = 8;
	double size = 64;
	double width = row * size;
	double height = column * size;
	double xPos;
	double yPos;
	int xHover;
	int yHover;
	int currentTurn = PLAYER;

	wind::Font* text;
	wind::Image* p1;
	wind::Image* p2;

};

#endif


