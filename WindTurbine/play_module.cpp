#include "play_module.h"



PlayModule::PlayModule() {
	updateOn = { "play" };
	drawOn = { "play","paused" };
	eventOn = { "play" };

	test = wind::Image("../assets/player.png");
	bg = wind::Image("../assets/bg.png");
}
 
void PlayModule::handleEvents(SDL_Event* current_event) {

}

void PlayModule::update(double dt) {
	if (wind::turbine.keyDown("w")) {
		std::cout << "[W] - is pressed" <<  "\n";
	}
	
	if (wind::turbine.keyDown("S")) {
		std::cout << "[S] - is pressed" << "\n";
	}

	if (wind::turbine.keyDown("R")) {
		std::cout << "[R] - is pressed" << "\n";
		wind::state.setCurrentState("paused");
	}
}

void PlayModule::draw() {
	bg.draw();
	test.draw(200, 200);
	//std::cout << "State is drawing" << "\n";
}

void PlayModule::clean() {
	//std::cout << "State was cleaned" << "\n";
}
