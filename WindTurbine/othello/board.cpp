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

	if (currentTurn == COMPUTER) {
		xHover = 8 * wind::math.random();
		yHover = 8 * wind::math.random();
		placeDisc();
	}
}

void Board::placeDisc() {
	if (isLegalMove()) {
		discs[xHover][yHover] = currentTurn;
	}
	else {
		return;
	}

	if (checkFlip(1, 0)) {
		flipDiscs(1, 0);
	}
	
	if (checkFlip(0, 1)) {
		flipDiscs(0, 1);
	}
	
	if (checkFlip(-1, 0)) {
		flipDiscs(-1, 0);
	}
	
	if (checkFlip(0, -1)) {
		flipDiscs(0, -1);
	}
	
	if (checkFlip(1, 1)) {
		flipDiscs(1, 1);
	}
	
	if (checkFlip(-1, -1)) {
		flipDiscs(-1, -1);
	}
	
	if (checkFlip(-1, 1)) {
		flipDiscs(-1, 1);
	}
	
	if (checkFlip(1, -1)) {
		flipDiscs(1, -1);
	}
	
	swapTurn();
	calculateScores();
}

void Board::swapTurn() {
	currentTurn = PLAYER * (currentTurn != PLAYER) + COMPUTER * (currentTurn != COMPUTER);
}

bool Board::isLegalMove() {
	if (xHover < 0 || xHover > 7 || yHover < 0 || yHover > 7) {
		return false;
	}
	else if (discs[xHover][yHover] != 0) {
		return false;
	}
	else {
		return wouldFlipDiscs();
	}
}

bool Board::wouldFlipDiscs() {
	return checkFlip(1, 0) || checkFlip(-1, 0) || checkFlip(0, 1) || checkFlip(0, -1) 
		|| checkFlip(1, 1) || checkFlip(-1, -1) || checkFlip(-1, 1) || checkFlip(1, -1);
}

bool Board::checkFlip(int x, int y) {
	if (y == 1 && yHover == 7 || y == -1 && yHover == 0) {
		return false;
	}
	else if (x == 1 && xHover == 7 || x == -1 && xHover == 0) {
		return false;
	}
	else if (discs[xHover + x][yHover + y] != getOponent()) {
		return false;
	}
	else {
		int i = 1;
		while(xHover + x * i >= 0 && xHover + x * i < row && yHover + y * i >= 0 && yHover + y * i < column)
		{
			if (discs[xHover + x * i][yHover + y * i] == 0) {
				return false;
			}
			else if (discs[xHover + x * i][yHover + y * i] == currentTurn) {
				return true;
			}
			i++;
		}
		return false;
	}
}

void Board::flipDiscs(int x, int y) {
	int i = 1;
	while (xHover + x * i >= 0 && xHover + x * i < row && yHover + y * i >= 0 && yHover + y * i < column)
	{
		if (discs[xHover + x * i][yHover + y * i] == 0) {
			return;
		}
		else if (discs[xHover + x * i][yHover + y * i] == currentTurn) {
			return;
		}
		else {
			discs[xHover + x * i][yHover + y * i] = currentTurn;
		}
		i++;
	}
}

int Board::getOponent() {
	if (currentTurn == PLAYER) {
		return COMPUTER;
	}
	else {
		return PLAYER;
	}
}

void Board::calculateScores() {
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
			if (discs[r][c] == 1) {
				p1->draw(xPos + size * r, yPos + size * c);
			}
			else if (discs[r][c] == 2) {
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
