#include <string>
#include "arcade_module.h"

ArcadeModule::ArcadeModule() {
	updateOn = { "arcade" };
	drawOn = { "arcade" };
	eventOn = { "arcade" };
	arcadeFont = new wind::Font("arcade/assets/bit.ttf", 24);
	world = new wind::PhysicsWorld(0,0);
	character = Character::getInstance(world);
	bg = wind::Image::getInstance("arcade/assets/bg.png");

	//Walls
	world->addObject(wind::RectangleCollider::getInstance(world, 0,0, 1280, 100));
	world->addObject(wind::RectangleCollider::getInstance(world, 0, 620, 1280, 100));
	world->addObject(wind::RectangleCollider::getInstance(world, 0, 0, 130, 720));
	world->addObject(wind::RectangleCollider::getInstance(world, 1150, 0, 130, 720));

	//Arcade hitboxes
	world->addObject(wind::RectangleCollider::getInstance(world, 170, 100, 90, 40));
	world->addObject(wind::RectangleCollider::getInstance(world, 575, 100, 90, 40));
	world->addObject(wind::RectangleCollider::getInstance(world, 775, 100, 90, 40));
	world->addObject(wind::RectangleCollider::getInstance(world, 1000, 100, 90, 40));
	world->addObject(wind::RectangleCollider::getInstance(world, 1100, 320, 70, 90));
}

void ArcadeModule::keyPressed(std::string key) {
	if (key == "E" && inRange) {
		wind::fade.in(0.3);
		wind::hibernate.it([=]() {wind::state.setCurrentState("play"); wind::fade.out(0.3);}, 0.3);
	}
}

void ArcadeModule::update(double dt) {
	character->update(dt);
	world->update(dt);
	
	if (wind::math.distance(character->getX(), character->getY(),820, 100) < 100) {
		inRange = true;
	}
	else {
		inRange = false;
	}
}

void ArcadeModule::draw() {
	wind::graphics.setColor(255, 255, 255, 255);
	bg->draw();
	character->draw();
	world->draw();

	if (inRange) {
		arcadeFont->draw("PRESS [E] TO PLAY", 745, 15);
	}

	//wind::graphics.circle("line", 820, 100, 100); // Debugg for visualizing arcade range
}

void ArcadeModule::clean() {

}