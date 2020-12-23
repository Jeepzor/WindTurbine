#include "play_module.h"

PlayModule::PlayModule() {
	updateOn = { "play" };
	drawOn = { "play","pause" };
	eventOn = { "play" };
}

//void handleEvents();
void PlayModule::update(double dt) {
	if (wind::turbine.keyboardIsDown("w")) {
		std::cout << "[W] - is pressed" <<  "\n";
	}
	
	if (wind::turbine.keyboardIsDown("S")) {
		std::cout << "[S] - is pressed" << "\n";
	}
}

void PlayModule::draw() {
	//std::cout << "State is drawing" << "\n";
}

void PlayModule::clean() {
	//std::cout << "State was cleaned" << "\n";
}

void PlayModule::handleEvents() {
	//std::cout << "State-events being managed" << "\n";
}