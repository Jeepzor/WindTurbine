#include <string>
#include "othello_module.h"


OthelloModule::OthelloModule() {
	updateOn = { "othello" };
	drawOn = { "othello" };
	eventOn = { "othello" };

	board = Board::getInstance(wind::turbine.getWindowWidth() / 2, wind::turbine.getWindowHeight() / 1.75);

}

void OthelloModule::keyPressed(std::string key) {
	
}

void OthelloModule::mousePressed(int button) {
	if (button == 1) {
		board->click();
	}
}

void OthelloModule::update(double dt) {
	board->update(dt);
	if (wind::turbine.keyDown("W")) {
		std::cout << "Game is paused" << dt << "\n";
	}
}

void OthelloModule::draw() {
	wind::graphics.setColor(0, 0, 0);
	board->draw();
}

void OthelloModule::clean() {
	//std::cout << "State was cleaned" << "\n";
}