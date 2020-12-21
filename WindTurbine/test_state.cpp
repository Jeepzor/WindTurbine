#include "test_state.h"

//void handleEvents();
void TestState::update(double dt) {
	if (wind::turbine.keyboard_is_down("w")) {
		std::cout << "[W] - is pressed" <<  dt <<  "\n";
	}
	
	if (wind::turbine.keyboard_is_down("S")) {
		std::cout << "[S] - is pressed" << "\n";
	}
}

void TestState::draw() {
	//std::cout << "State is drawing" << "\n";
}

void TestState::clean() {
	//std::cout << "State was cleaned" << "\n";
}

void TestState::handleEvents() {
	//std::cout << "State-events being managed" << "\n";
}