#include "test_module.h"

TestModule::TestModule() {
	updateOn = { "test","testing" };
	drawOn = { "test","testing" };
	eventOn = { "test","testing" };
}

//void handleEvents();
void TestModule::update(double dt) {
	if (wind::turbine.keyboardIsDown("w")) {
		std::cout << "[W] - is pressed" <<  dt <<  "\n";
	}
	
	if (wind::turbine.keyboardIsDown("S")) {
		std::cout << "[S] - is pressed" << "\n";
	}
}

void TestModule::draw() {
	//std::cout << "State is drawing" << "\n";
}

void TestModule::clean() {
	//std::cout << "State was cleaned" << "\n";
}

void TestModule::handleEvents() {
	//std::cout << "State-events being managed" << "\n";
}