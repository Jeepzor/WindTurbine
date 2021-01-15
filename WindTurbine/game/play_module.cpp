#include "play_module.h"
#include "player.h"
#include "missile.h"
#include "rock.h"

double timer = 0;
double rate = 0.3;


PlayModule::PlayModule() {
	updateOn = { "play" };
	drawOn = { "play","paused" };
	eventOn = { "play" };
	initOn = { "play" };
	cleanOn = { "restart" };



	double our_dt = 0; // Debug, remove later

	//TODO add removal of collider from physicsWorld in their destructor
	world = new wind::PhysicsWorld(0, 0);

	fpsFont = new wind::Font("../assets/bit.ttf", 32);

	playerShip = new Player(world);


	//wind::hibernate.it( [=]() mutable {}, 5);
}

void PlayModule::keyPressed(std::string key) {
	std::cout << "Key [" << key << "] was pressed" << "\n";
	if (key == "1") {
		wind::state.setCurrentState("paused");
	}
	else if (key == "3") {
		
	}
	else if (key == "8") {
		world->toggleDebug();
	}else if (key == "9") {
		wind::turbine.toggleCursor();
	}
}

void PlayModule::keyReleased(std::string key) {
	std::cout << "Key [" << key << "] was released" << "\n";
}

void PlayModule::mousePressed(int button) {
	if (button == 1) {
		entities.push_back(Missile::getInstance(world, playerShip->getLaunchX(), playerShip->getLaunchY(), playerShip->getAngle()));
	}
	else if (button == 3) {
		entities.push_back(Rock::getInstance(world, 700, 300, -playerShip->getAngle()));
	}
}

void PlayModule::mouseReleased(int button) {
	std::cout << "button [" << button << "] was released" << "\n";
}

void PlayModule::update(double dt) {
	timer += dt;
	if (timer >= rate) {
		timer = 0;
		our_dt = dt;
	}

	
	updateEntities(dt);
	playerShip->update(dt);
	world->update(dt);
}


void PlayModule::updateEntities(double dt) {
	for (auto instance : entities) {
		instance->update(dt);
	}
	removeDeadEntities();
}

void PlayModule::removeDeadEntities() {
	entities.erase(std::remove_if(entities.begin(), entities.end(), [](wind::Entity* i) { return !(i->isAlive()); }), entities.end());
}

void PlayModule::draw() {
	wind::graphics.setColor(0, 0, 0,255);
	wind::graphics.rectangle(0, 0, wind::turbine.getWindowWidth(), wind::turbine.getWindowHeight());
	wind::graphics.setColor(255, 255, 255,255);

	playerShip->draw();
	drawEntities();
	world->draw();

	wind::graphics.setColor(0, 0, 0);
	fpsFont->draw("DT            " + std::to_string(our_dt), 32, 32);
	wind::graphics.setColor(255, 255, 255);
	fpsFont->draw("DT            " + std::to_string(our_dt), 30, 30);
}

void PlayModule::drawEntities() {
	for (auto instance : entities) {
		instance->draw();
	}
}



void PlayModule::clean() {
	//std::cout << "State was cleaned" << "\n";

}