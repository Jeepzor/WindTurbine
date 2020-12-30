#include "play_module.h"
#include "player.h"



PlayModule::PlayModule() {
	updateOn = { "play" };
	drawOn = { "play","paused" };
	eventOn = { "play" };

	worldA = new wind::PhysicsWorld(0, 0);
	bodyA = new wind::Collider(worldA, 30, 30, 10, 10);
	bodyB = new wind::Collider(worldA, 300, 30, 30, 30);

	bodyB->setVelocity(-50, 0);
	bg = new wind::Image("../assets/bg.png");
	testPlayer = new Player();
	testPlayer = new Player();
}

void PlayModule::keyPressed(std::string key) {
	std::cout << "Key [" << key << "] was pressed" << "\n";
	if (key == "1") {
		wind::state.setCurrentState("paused");
	}
}

void PlayModule::keyReleased(std::string key) {
	std::cout << "Key [" << key << "] was released" << "\n";
}

void PlayModule::mousePressed(int button) {
	std::cout << "button [" << button << "] was pressed" << "\n";

	std::cout << wind::turbine.getMousePosition().first << " " << wind::turbine.getMousePosition().second << "\n";
	std::cout << wind::turbine.getMouseX() << " " << wind::turbine.getMouseY()<< "\n";
}

void PlayModule::mouseReleased(int button) {
	std::cout << "button [" << button << "] was released" << "\n";
}

void PlayModule::update(double dt) {
	testPlayer->update(dt);
	worldA->update(dt);
}

void PlayModule::draw() {
	bg->draw();
	wind::graphics.setColor(255, 0, 0);
	testPlayer->draw();
	//wind::graphics.clearColor();
	worldA->draw();
	//std::cout << "State is drawing" << "\n";
}

void PlayModule::clean() {
	//std::cout << "State was cleaned" << "\n";
}
