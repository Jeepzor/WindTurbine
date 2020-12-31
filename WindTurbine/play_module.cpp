#include "play_module.h"
#include "player.h"



PlayModule::PlayModule() {
	updateOn = { "play" };
	drawOn = { "play","paused" };
	eventOn = { "play" };

	worldA = new wind::PhysicsWorld(0, 0);
	bodyA = new wind::Collider(worldA, 30, 30, 40, 600);
	bodyB = new wind::Collider(worldA, 300, 330, 75, 75);
	bodyC = new wind::Collider(worldA, 500, 300, 10, 200);
	bodyD = new wind::Collider(worldA, 750, 300, 35);
	bodyE = new wind::Collider(worldA, 900, 360, 75);
	bodyF = new wind::Collider(worldA, 1100, 330, 25, 75);
	bodyG = new wind::Collider(worldA, 1350, 330, 10);

	bodyB->setVelocity(-200, 0);
	bodyC->setVelocity(-200, 0);
	bodyD->setVelocity(-200, 0);
	bodyE->setVelocity(-200, 0);
	bodyF->setVelocity(-200, 0);
	bodyG->setVelocity(-200, 0);
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
	testPlayer->draw();
	worldA->draw();
	wind::graphics.setColor(255, 0, 0);
	//wind::graphics.circle("line", 300, 300, 40);
	//wind::graphics.circle("fill", 400, 400, 25);
	//std::cout << "State is drawing" << "\n";
}

void PlayModule::clean() {
	//std::cout << "State was cleaned" << "\n";
}
