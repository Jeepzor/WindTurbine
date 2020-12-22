#include "test_module_2.h"

TestModule2::TestModule2() {
	updateOn = { "test","somethingElse" };
	drawOn = { "test","somethingElse" };
	eventOn = { "test","somethingElse" };
}

//void handleEvents();
void TestModule2::update(double dt) {
	if (wind::turbine.keyboardIsDown("w")) {
		std::cout << "[W] - hurr durr" << dt << "\n";
	}

	if (wind::turbine.keyboardIsDown("S")) {
		std::cout << "[S] - durr hurr" << "\n";
	}
}

void TestModule2::draw() {
	//std::cout << "State is drawing" << "\n";
}

void TestModule2::clean() {
	//std::cout << "State was cleaned" << "\n";
}

void TestModule2::handleEvents() {
	//std::cout << "State-events being managed" << "\n";
}