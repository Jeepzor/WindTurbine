#include <string>
#include "gameover_module.h"


GameoverModule::GameoverModule() {
	updateOn = { "gameover" };
	drawOn = { "gameover" };
	eventOn = { "gameover" };
	endFont = new wind::Font("game/assets/bit.ttf", 64);
}

void GameoverModule::keyPressed(std::string key) {
	if (key == "Space") {
		wind::fade.in(0.3);
		wind::hibernate.it([=]() {wind::state.setCurrentState("arcade"); wind::fade.out(0.3);}, 0.3);
	}
}

void GameoverModule::update(double dt) {
	timeWave += dt;
	if (wind::turbine.keyDown("W")) {
		std::cout << "Game is paused" << dt << "\n";
	}
}

void GameoverModule::draw() {
	double offsetY = sin(timeWave) * 15;
	double offsetAngle = sin(timeWave * 2) * 0.03;
	wind::graphics.setColor(255, 255, 255, 155);
	wind::graphics.setColor(255, 255, 255, 255);
	endFont->draw("GAME OVER", 510, 200 + offsetY);
	endFont->draw("PRESS SPACEBAR TO CONTINUE", 290, 300 + offsetY, offsetAngle);
	//std::cout << "State is drawing" << "\n";
}

void GameoverModule::clean() {
	//std::cout << "State was cleaned" << "\n";
}