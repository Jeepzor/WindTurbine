
#ifndef BOARD_H
#define BOARD_H

#include "../wind.h"
#include "position.h"

constexpr int PLAYER = 1;
constexpr int COMPUTER = 2;
class Board{
public:
	static Board* getInstance(int xPos, int yPos) {
		return new Board(xPos, yPos);
	}
	void click();
	void draw(); 
	void update(double dt);
	void restart(bool playerBlack);
	
	~Board();
	

private:
	Board(int xPos, int yPos);
	Board(const Board& other) = delete;
	const Board& operator=(const Board& other) = delete;
	void AI();
	void placeDisc(int x, int y, Position& pos);
	bool isLegalMove(int x, int y, Position& pos);
	bool wouldFlipDiscs(int x, int y, Position& pos);
	bool checkFlip(int x, int y, int dx, int dy, Position& pos);
	void flipDiscs(int x, int y, int dx, int dy, Position& pos);
	void calculateScores();
	int getNumberOfLegalMoves(Position& pos);

	std::vector<Move> findLegalMoves(Position& pos);
	Move findBestMove(Position& pos, int depth, int alpha, int beta, bool maxPlayer);
	int getOponent(Position& pos);
	
	void drawTarget();
	void drawBackground();
	void drawSquares();
	void drawChars();
	void drawDiscs();
	void drawScore();

	Position currentPosition;
	std::string characters[8] = {"A", "B", "C", "D", "E", "F", "G", "H" };
	int column = 8;
	int row = 8;
	int size = 64;
	int width = row * size;
	int height = column * size;
	int xPos;
	int yPos;
	int xHover;
	int yHover;
	int currentTurn = PLAYER;
	int scoreP1 = 2;
	int scoreP2 = 2;
	bool skipFrame = false;
	bool playerIsBlack = false;

	std::vector<Move> cornerMoves;
	std::vector<Move> wallMoves;
	std::vector<Move> centerMoves;
	std::vector<Move> terribleMoves;
	std::vector<Move> badMoves;

	wind::Font* text;
	wind::Image* p1;
	wind::Image* p2;
};

#endif


