#include "play_module.h"



PlayModule::PlayModule() {
	updateOn = { "play" };
	drawOn = { "play","paused" };
	eventOn = { "play" };

	test = wind::Image("../assets/player.png");
	bg = wind::Image("../assets/bg.png");
}

void PlayModule::keyPressed(std::string key) {
	std::cout << "Key [" << key << "] was pressed" << "\n";
	if (key == "1") {
		wind::state.setCurrentState("paused");
	}
	
	if (key == "D") {
		test.setFlip(false, false);
	}
	
	if (key == "A") {
		test.setFlip(true, false);
	}
}

void PlayModule::keyReleased(std::string key) {
	std::cout << "Key [" << key << "] was released" << "\n";
}

void PlayModule::mousePressed(int button) {
	std::cout << "button [" << button << "] was pressed" << "\n";
}

void PlayModule::mouseReleased(int button) {
	std::cout << "button [" << button << "] was released" << "\n";
}


void PlayModule::update(double dt) {
	/*
	if (wind::turbine.keyDown("W")) {
		std::cout << "[W] - is pressed" <<  "\n";
	}
	*/
	
}

void PlayModule::draw() {
	bg.draw();
	test.setAngle(90);
	test.draw(200, 200);
	//std::cout << "State is drawing" << "\n";
}

void PlayModule::clean() {
	//std::cout << "State was cleaned" << "\n";
}
