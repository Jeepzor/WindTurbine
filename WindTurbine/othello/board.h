
#ifndef BOARD_H
#define BOARD_H

#include "../wind.h"
#include "position.h"

constexpr int PLAYER = 1;
constexpr int COMPUTER = 2;
constexpr int MAX = 999999;
class Board{
public:
	static Board* getInstance(int xPos, int yPos) {
		return new Board(xPos, yPos);
	}

	/// <summary>
	/// Calls "placeDisc" if it's the players turn.
	/// </summary>
	void click();

	/// <summary>
	/// Renders all graphical assets of the board.
	/// </summary>
	void draw() const; 

	/// <summary>
	/// 
	/// </summary>
	/// <param name="dt"> = Delta time</param>
	void update(double dt);

	/// <summary>
	/// Restarts the current game, setting the player to control the black discs if the boolean
	/// parameter "playerBlack" is set to true, otherwise the player controls the white discs.
	/// </summary>
	/// <param name="playerBlack"></param>
	void restart(bool playerBlack);
	
	~Board();
	

private:
	Board(int xPos, int yPos);
	Board(const Board& other) = delete;
	const Board& operator=(const Board& other) = delete;
	void AI();
	void placeDisc(int x, int y, Position& pos);
	bool isLegalMove(int x, int y, Position& pos) const;
	bool wouldFlipDiscs(int x, int y, Position& pos) const;
	bool checkFlip(int x, int y, int dx, int dy, Position& pos) const;
	void flipDiscs(int x, int y, int dx, int dy, Position& pos);
	void calculateScores();
	int getNumberOfLegalMoves(Position& pos);

	std::vector<Move> findLegalMoves(Position& pos);
	Move findBestMove(Position& pos, int depth, int alpha, int beta, bool maxPlayer);
	int getOponent(Position& pos) const;
	
	void drawTarget() const;
	void drawBackground() const;
	void drawSquares() const;
	void drawChars() const;
	void drawDiscs() const;
	void drawScore() const;

	Position currentPosition;
	std::string characters[8] = {"A", "B", "C", "D", "E", "F", "G", "H" };
	
	int column = 8;
	int row = 8;
	int size = 64;
	int width = row * size;
	int height = column * size;
	int yHover = 0;
	int xHover = 0;
	int scoreP1 = 2;
	int scoreP2 = 2;
	int currentTurn = PLAYER;

	int xPos;
	int yPos;
	bool skipFrame = false;
	bool justSwapped = false;
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


