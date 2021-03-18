#include <string>
#include "board.h"

Board::Board(int x, int y) {
	xPos = x - size * column / 2;
	yPos = y - size * row / 2;
	text = new wind::Font("game/assets/bit.ttf", 64);

	p1 = wind::Image::getInstance("othello/assets/1.png");
	p2 = wind::Image::getInstance("othello/assets/2.png");

	cornerMoves = {Move(0,0), Move(7,7), Move(7,0), Move(0,7)};

	terribleMoves = { Move(1,1), Move(6,6), Move(6,1), Move(1,6), 
					Move(0,1), Move(1,0), Move(0,6), Move(6,0),
					Move(7,1), Move(1,7), Move(7,6), Move(6,7),
	};

	badMoves = { Move(1,2), Move(1,3), Move(1,4), Move(1,5),
				  Move(6,2), Move(6,3), Move(6,4), Move(6,5),
				  Move(2,1), Move(3,1), Move(4,1), Move(5,1),
				  Move(2,6), Move(3,6), Move(4,6), Move(5,6),

	};

	wallMoves = { Move(0,2), Move(0,3), Move(0,4), Move(0,5),
				  Move(7,2), Move(7,3), Move(7,4), Move(7,5),
				  Move(2,0), Move(3,0), Move(4,0), Move(5,0),
				  Move(2,7), Move(3,7), Move(4,7), Move(5,7),

	};

	for (int x = 2; x <= 5; x++)
	{
		for (int y = 2; y <= 5; y++) {
			centerMoves.push_back(Move(x, y));
		}
	}

	currentPosition = Position();
	findLegalMoves(currentPosition);
}

void Board::restart(bool playerBlack) {
	currentPosition.setStartPosition(playerBlack);
	playerIsBlack = playerBlack;
}

Board::~Board() {
	delete text;
}

void Board::update(double dt) {
	int mouseX = wind::turbine.getMouseX();
	int mouseY = wind::turbine.getMouseY();
	if (mouseX > xPos && mouseX < xPos + width && mouseY > yPos && mouseY < yPos + height) {
		xHover = (mouseX - xPos) / size;
		yHover = (mouseY - yPos) / size;
	}
	else {
		xHover = -1;
		yHover = -1;
	}

	AI();

	
	if (getNumberOfLegalMoves(currentPosition) == 0 && !justSwapped) {
		justSwapped = true;
		currentPosition.swapTurn();
	}
	else {
		justSwapped = false;
	}
}

std::vector<Move> Board::findLegalMoves(Position& pos) {
	std::vector<Move> legalMoves;

	for (int i = 0; i < cornerMoves.size(); i++)
	{
		if (isLegalMove(cornerMoves[i].x, cornerMoves[i].y, pos)) {
			Move newMove = Move(cornerMoves[i].x, cornerMoves[i].y);
			legalMoves.push_back(newMove);
		}
	}
	
	for (int i = 0; i < wallMoves.size(); i++)
	{
		if (isLegalMove(wallMoves[i].x, wallMoves[i].y, pos)) {
			Move newMove = Move(wallMoves[i].x, wallMoves[i].y);
			legalMoves.push_back(newMove);
		}
	}
	
	for (int i = 0; i < centerMoves.size(); i++)
	{
		if (isLegalMove(centerMoves[i].x, centerMoves[i].y, pos)) {
			Move newMove = Move(centerMoves[i].x, centerMoves[i].y);
			legalMoves.push_back(newMove);
		}
	}
	
	for (int i = 0; i < badMoves.size(); i++)
	{
		if (isLegalMove(badMoves[i].x, badMoves[i].y, pos)) {
			Move newMove = Move(badMoves[i].x, badMoves[i].y);
			legalMoves.push_back(newMove);
		}
	}
	
	for (int i = 0; i < terribleMoves.size(); i++)
	{
		if (isLegalMove(terribleMoves[i].x, terribleMoves[i].y, pos)) {
			Move newMove = Move(terribleMoves[i].x, terribleMoves[i].y);
			legalMoves.push_back(newMove);
		}
	}

	return legalMoves;
}

int Board::getNumberOfLegalMoves(Position& pos) {
	std::vector<Move> legalMoves;
	for (int x = 0; x <= row; x++)
	{
		for (int y = 0; y <= column; y++)
		{
			if (isLegalMove(x, y, pos)) {
				Move newMove = Move(x, y);
				legalMoves.push_back(newMove);
			}
		}
	}

	return legalMoves.size();
}

void Board::click() {
	if (currentTurn == PLAYER){
		placeDisc(xHover, yHover, currentPosition);
		calculateScores();
		skipFrame = true;
	}
}

void Board::AI() {
	if (skipFrame) {
		skipFrame = false;
	}
	else {
		if (currentPosition.getTurn() == COMPUTER) {
			Move bestMove = findBestMove(currentPosition, 7, -MAX, MAX, false);
			placeDisc(bestMove.x, bestMove.y, currentPosition);
			calculateScores();
		}
	}
}

/// <summary>
/// Minimax algorithm which evaluates board positions at an X-depth to estimate which
/// move is most likely to be the best. Alpha Beta pruning tries to reduce the amount of positions
/// which need to be evaluated by pruning away irrelevant branches which can not result in a better position.
/// </summary>
/// <param name="pos"> = The position to be evaluated</param>
/// <param name="depth"> = How many moves it will look through</param>
/// <param name="alpha">Should be called with the worst possible evaluation for the maxPlayer</param>
/// <param name="beta">Should be called with the worst possible evaluation for the none-maxPlayer</param>
/// <param name="maxPlayer"> If true it will pick the move which is best for the player and vice versa.</param>
/// <returns>A Move object instance wich contains the coordinates of the selected best path.</returns>
Move Board::findBestMove(Position& pos, int depth, int alpha, int beta, bool maxPlayer) {
	if (depth == 0 ) {
		return Move(0,0, pos.evaluate());
	}
	else if (getNumberOfLegalMoves(pos) == 0) {
		int s1;
		int s2;
		pos.getScores(s1, s2);
		return Move(0, 0, -MAX * (s1 < s2) + MAX * (s1 > s2));
	}
	else if (maxPlayer == true) {
		std::vector<Move> legalMoves = findLegalMoves(pos);
		Move bestValue = Move(0, 0, -MAX);
		for (int i = 0; i < legalMoves.size(); i++)
		{
			Position newPosition = Position(pos);
			placeDisc(legalMoves[i].x, legalMoves[i].y, newPosition);
			Move maxEval = findBestMove(newPosition, depth - 1, alpha, beta, false);
			if (maxEval.value > bestValue.value) {
				bestValue.value = maxEval.value;
				bestValue.x = legalMoves[i].x;
				bestValue.y = legalMoves[i].y;
			}

			if (maxEval.value > alpha) {
				alpha = maxEval.value;
			}

			if (beta <= alpha) {
				break;
			}
		}
		return bestValue;
	}
	else if (maxPlayer == false){
		std::vector<Move> legalMoves = findLegalMoves(pos);
		Move bestValue = Move(0, 0, MAX);
		for (int i = 0; i < legalMoves.size(); i++)
		{
			Position newPosition = Position(pos);
			placeDisc(legalMoves[i].x, legalMoves[i].y, newPosition);
			Move minEval = findBestMove(newPosition, depth - 1, alpha, beta, true);
			if (minEval.value < bestValue.value) {
				bestValue.value = minEval.value;
				bestValue.x = legalMoves[i].x;
				bestValue.y = legalMoves[i].y;
			}

			if (minEval.value < beta) {
				beta = minEval.value;
			}

			if (beta <= alpha) {
				break;
			}
		}
		return bestValue;
	}
}

void Board::placeDisc(int x, int y, Position& pos) {
	if (x < 0 || x > 7 || y < 0 || y > 7) {
		return;
	}
	else if (pos.getDisc(x, y) != 0) {
		return;
	}

	bool legal = false;
	
	if (checkFlip(x, y, 1, 0, pos)) {
		legal = true;
		flipDiscs(x, y, 1, 0, pos);
	}
	
	if (checkFlip(x, y, 0, 1, pos)) {
		legal = true;
		flipDiscs(x, y, 0, 1, pos);
	}
	
	if (checkFlip(x, y, -1, 0, pos)) {
		legal = true;
		flipDiscs(x, y, -1, 0, pos);
	}
	
	if (checkFlip(x, y, 0, -1, pos)) {
		legal = true;
		flipDiscs(x, y, 0, -1, pos);
	}
	
	if (checkFlip(x, y, 1, 1, pos)) {
		legal = true;
		flipDiscs(x, y, 1, 1, pos);
	}
	
	if (checkFlip(x, y, -1, -1, pos)) {
		legal = true;
		flipDiscs(x, y, -1, -1, pos);
	}
	
	if (checkFlip(x, y, -1, 1, pos)) {
		legal = true;
		flipDiscs(x, y, -1, 1, pos);
	}
	
	if (checkFlip(x, y, 1, -1, pos)) {
		legal = true;
		flipDiscs(x, y, 1, -1, pos);
	}

	if (legal) {
		pos.setDisc(x, y, pos.getTurn());
		pos.swapTurn();
	}

}

bool Board::isLegalMove(int x, int y, Position& pos) const {
	if (x < 0 || x > 7 || y < 0 || y > 7) {
		return false;
	}
	else if (pos.getDisc(x,y) != 0) {
		return false;
	}
	else {
		return wouldFlipDiscs(x, y, pos);
	}
}

bool Board::wouldFlipDiscs(int x, int y, Position& pos) const {
	return checkFlip(x, y, 1, 0, pos) || checkFlip(x, y, -1, 0, pos) || checkFlip(x, y, 0, 1, pos) || checkFlip(x, y, 0, -1, pos)
		|| checkFlip(x, y, 1, 1, pos) || checkFlip(x, y, -1, -1, pos) || checkFlip(x, y, -1, 1, pos) || checkFlip(x, y, 1, -1, pos);
}

bool Board::checkFlip(int x, int y, int dx, int dy, Position& pos) const {
	if (dy == 1 && y == 7 || dy == -1 && y == 0) {
		return false;
	}
	else if (dx == 1 && x == 7 || dx == -1 && x == 0) {
		return false;
	}
	else if (pos.getDisc(x + dx, y + dy) != getOponent(pos)) {
		return false;
	}
	else {
		int i = 2;
		while(x + dx * i >= 0 && x + dx * i < row && y + dy * i >= 0 && y + dy * i < column)
		{
			if (pos.getDisc(x + dx * i,y + dy * i) == 0) {
				return false;
			}
			else if (pos.getDisc(x + dx * i, y + dy * i) == pos.getTurn()) {
				return true;
			}
			i++;
		}
		return false;
	}
}

void Board::flipDiscs(int x, int y, int dx, int dy, Position& pos) {
	int i = 1;
	while (x + dx * i >= 0 && x + dx * i < row && y + dy * i >= 0 && y + dy * i < column)
	{
		if (pos.getDisc(x + dx * i, y + dy * i) == 0) {
			return;
		}
		else if (pos.getDisc(x + dx * i, y + dy * i) == pos.getTurn()) {
			return;
		}
		else {
			pos.setDisc(x + dx * i, y + dy * i, pos.getTurn());
		}
		i++;
	}
}

int Board::getOponent(Position& pos) const {
	if (pos.getTurn() == PLAYER) {
		return COMPUTER;
	}
	else {
		return PLAYER;
	}
}

void Board::calculateScores() {
	currentPosition.getScores(scoreP1, scoreP2);
}


void Board::draw() const{
	drawBackground();
	drawSquares();
	drawChars();
	drawTarget();
	drawDiscs();
	drawScore();
}

void Board::drawBackground() const{
	wind::graphics.setColor(72, 93, 63, 255);
	wind::graphics.rectangle("fill", 0,0, 1280, 720);
}

void Board::drawScore() const{
	wind::graphics.setColor(225, 255, 225);
	text->draw("Player Score: " + std::to_string(scoreP1), 50, 10);
	text->draw("Computer Score: " + std::to_string(scoreP2), 700, 10);
}

void Board::drawTarget() const{
	wind::graphics.setColor(255, 255, 255, 80);
	int x = xPos + size * xHover;
	int y = yPos + size * yHover;
	if (playerIsBlack) {
		p1->draw(x, y);
	}
	else {
		p2->draw(x, y);
	}
}

void Board::drawSquares() const{
	for (int r = 0; r < row; r++) {
		for (int c = 0; c < column; c++)
		{
			int x = xPos + size * r;
			int y = yPos + size * c;
			wind::graphics.setColor(25,55,25);
			wind::graphics.rectangle("line", x, y, size, size);			
		}
	}
}

void Board::drawDiscs() const{
	wind::graphics.setColor(255, 255, 255);
	for (int r = 0; r < row; r++) {
		for (int c = 0; c < column; c++)
		{
			int x = xPos + size * r;
			int y = yPos + size * c;
			if (currentPosition.getDisc(r, c) == 1) {
				if (playerIsBlack) {
					p1->draw(x, y);
				}
				else {
					p2->draw(x, y);
				}
			}
			else if (currentPosition.getDisc(r, c) == 2) {
				if (playerIsBlack) {
					p2->draw(x, y);
				}
				else {
					p1->draw(x, y);
				}
			}
		}
	}
}

void Board::drawChars() const{	
	wind::graphics.setColor(225, 255, 225);
	for (int r = 0; r < row; r++) {
		int x = xPos + size * r + size / 4;
		int y = yPos - size;
		std::string s = "A";
		text->draw(characters[r], x, y);
	}

	for (int c = 0; c < column; c++) {
		int x = xPos - size / 2;
		int y = yPos + size * c;
		text->draw(std::to_string(c + 1), x, y);
	}
}
