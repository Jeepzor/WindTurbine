#include <string>
#include "pause_module.h"


PauseModule::PauseModule() {
	updateOn = { "paused" };
	drawOn = { "paused" };
	eventOn = { "paused"};
	pauseFont = new wind::Font("../assets/5x5.ttf", 64);
	pauseImg = wind::Image::getInstance("../assets/paused.png");
}

void PauseModule::keyPressed(std::string key) {
	if (key == "2") {
		wind::state.setCurrentState("play");
	}
}

void PauseModule::update(double dt) {
	if (wind::turbine.keyDown("W")) {
		std::cout << "Game is paused" << dt << "\n";
	}
}

void PauseModule::draw() {
	wind::graphics.setColor(255, 255, 255, 155);
	pauseImg->draw(0, 0);
	wind::graphics.setColor(255, 0, 0, 255);
	pauseFont->draw("hello", 200, 200);
	//std::cout << "State is drawing" << "\n";
}

void PauseModule::clean() {
	//std::cout << "State was cleaned" << "\n";
}