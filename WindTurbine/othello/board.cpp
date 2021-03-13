#include <string>
#include "board.h"

Board::Board(double x, double y) {
	xPos = x - size * column / 2;
	yPos = y - size * row / 2;
	text = new wind::Font("game/assets/bit.ttf", 64);
	xHover = 5;
	yHover = 6;
	p1 = wind::Image::getInstance("othello/assets/1.png");
	p2 = wind::Image::getInstance("othello/assets/2.png");

	currentPosition = Position();
	findLegalMoves(currentPosition);
}

Board::~Board() {
	delete text;
}

void Board::update(double dt) {
	double mouseX = wind::turbine.getMouseX();
	double mouseY = wind::turbine.getMouseY();
	if (mouseX > xPos && mouseX < xPos + width && mouseY > yPos && mouseY < yPos + height) {
		xHover = (mouseX - xPos) / size;
		yHover = (mouseY - yPos) / size;
	}
	else {
		xHover = -1;
		yHover = -1;
	}
}

std::vector<Move> Board::findLegalMoves(Position& pos) {
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

int counter = 0;
bool swap = true;
void Board::click() {
	if (swap) {
		placeDisc(xHover, yHover, currentPosition);
		
	}
	else {
		if (currentPosition.getTurn() == COMPUTER) {
			std::cout << "COMPUTER \n";
			Move bestMove = findBestMove(currentPosition, 5, -999999, 999999, false);
			std::cout << "Looked at " << counter << " positions \n";
			std::cout << "Value: " << bestMove.value << "\n";
			placeDisc(bestMove.x, bestMove.y, currentPosition);
			calculateScores();
		}
	}
	swap = !swap;
	calculateScores();
	counter = 0;
}


Move Board::test(int depth) {
	if (depth == 0) {
		return Move(13, 3, 1337);
	}
	return test(depth - 1);
}

Move Board::findBestMove(Position& pos, int depth, int alpha, int beta, bool maxPlayer) {
	if (depth == 0 || getNumberOfLegalMoves(pos) == 0) {
		counter++;
		return Move(0,0, pos.evaluate());
	}
	else if (maxPlayer == true) {
		pos.setTurn(1);
		std::vector<Move> legalMoves = findLegalMoves(pos);
		Move bestValue = Move(0, 0, -99999);
		for (int i = 0; i < legalMoves.size(); i++)
		{
			Position newPosition = Position();
			newPosition.deepCopy(pos);
			placeDisc(legalMoves[i].x, legalMoves[i].y, newPosition);
			Move maxEval = findBestMove(newPosition, depth - 1, alpha, beta, false);
			if (maxEval.value >= bestValue.value) {
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
		pos.setTurn(2);
		std::vector<Move> legalMoves = findLegalMoves(pos);
		Move bestValue = Move(0, 0, 99999);
		for (int i = 0; i < legalMoves.size(); i++)
		{
			Position newPosition = Position();
			newPosition.deepCopy(pos);
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

bool Board::isLegalMove(int x, int y, Position& pos) {
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

bool Board::wouldFlipDiscs(int x, int y, Position& pos) {
	return checkFlip(x, y, 1, 0, pos) || checkFlip(x, y, -1, 0, pos) || checkFlip(x, y, 0, 1, pos) || checkFlip(x, y, 0, -1, pos)
		|| checkFlip(x, y, 1, 1, pos) || checkFlip(x, y, -1, -1, pos) || checkFlip(x, y, -1, 1, pos) || checkFlip(x, y, 1, -1, pos);
}

bool Board::checkFlip(int x, int y, int dx, int dy, Position& pos) {
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

int Board::getOponent(Position& pos) {
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


void Board::draw() {
	drawSquares();
	drawChars();
	drawDiscs();
	drawScore();
}

void Board::drawScore() {
	wind::graphics.setColor(0, 0, 0, 255);
	text->draw("Player Score: " + std::to_string(scoreP1), 50, 10);
	text->draw("Computer Score: " + std::to_string(scoreP2), 700, 10);
}

void Board::drawSquares() {
	for (int r = 0; r < row; r++) {
		for (int c = 0; c < column; c++)
		{
			if (r == xHover && c == yHover) {
				wind::graphics.setColor(255, 0, 0, 55);
				wind::graphics.rectangle("fill", xPos + size * r, yPos + size * c, size, size);
			}
			else {
				wind::graphics.setColor(0, 0, 0);
				wind::graphics.rectangle("line", xPos + size * r, yPos + size * c, size, size);
			}			
		}
	}
}

void Board::drawDiscs() {
	wind::graphics.setColor(255, 255, 255);
	for (int r = 0; r < row; r++) {
		for (int c = 0; c < column; c++)
		{
			if (currentPosition.getDisc(r, c) == 1) {
				p1->draw(xPos + size * r, yPos + size * c);
			}
			else if (currentPosition.getDisc(r, c) == 2) {
				p2->draw(xPos + size * r, yPos + size * c);
			}
		}
	}
}

void Board::drawChars() {	
	wind::graphics.setColor(0, 0, 0);
	for (int r = 0; r < row; r++) {
		std::string s = "A";
		text->draw(characters[r], xPos + size * r + size / 4, yPos - size);
	}

	for (int c = 0; c < column; c++) {
		std::string s = "A";
		text->draw(std::to_string(c + 1), xPos - size / 2, yPos + size * c);
	}
}
