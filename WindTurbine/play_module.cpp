#include "play_module.h"
#include "player.h"
#include "vec2.h"


PlayModule::PlayModule() {
	updateOn = { "play" };
	drawOn = { "play","paused" };
	eventOn = { "play" };

	//TODO add removal of collider from physicsWorld in their destructor
	worldA = new wind::PhysicsWorld(0, 0);
	bodyA = new wind::RectangleCollider(worldA, 30, 30, 40, 600);
	bodyB = new wind::RectangleCollider(worldA, 700, 400, 75, 75);
	//bodyC = new wind::RectangleCollider(worldA, 500, 300, 10, 200);
	//bodyD = new wind::RectangleCollider(worldA, 1100, 330, 25, 75);
	bodyE = new wind::CircleCollider(worldA, 750, 300, 35);

	std::vector < wind::Vec2> testPoly;
	testPoly.push_back(wind::Vec2(50, 50));
	testPoly.push_back(wind::Vec2(100, 50));
	testPoly.push_back(wind::Vec2(75, 10));
	testPoly.push_back(wind::Vec2(50, 100));
	bodyG = new wind::PolygonCollider(worldA, 480, 230, testPoly);
	bodyF = new wind::PolygonCollider(worldA, 400, 200, testPoly);

	//bodyB->setVelocity(-200, 0);
	//bodyC->setVelocity(-200, 0);
	//bodyD->setVelocity(-200, 0); 
	//bodyE->setVelocity(-200, 0);
	//bodyF->setVelocity(0, 0);
	bodyG->setVelocity(-200, 10);
	bg = new wind::Image("../assets/bg.png");
	testPlayer = new Player(worldA);

	double abc = 20;
	std::cout << abc;
}

void PlayModule::keyPressed(std::string key) {
	std::cout << "Key [" << key << "] was pressed" << "\n";
	if (key == "1") {
		wind::state.setCurrentState("paused");
	}
	else if (key == "3") {
		bodyG->setVelocity(200, 0);
	}
	else if (key == "4") {
		bodyG->setVelocity(-200, 0);
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
	//wind::graphics.circle("line", 400, 400, 400);
	//std::cout << "State is drawing" << "\n";
}

void PlayModule::clean() {
	//std::cout << "State was cleaned" << "\n";
}
