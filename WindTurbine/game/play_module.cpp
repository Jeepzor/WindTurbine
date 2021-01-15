#include "play_module.h"
#include "player.h"
#include "missile.h"

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

	bg = wind::Image::getInstance("game/assets/universe.png");
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
		missiles.push_back(Missile::getInstance(world, playerShip->getLaunchX(), playerShip->getLaunchY(), playerShip->getAngle()));
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

	for (auto instance : missiles) {
		instance->update(dt);
	}
	
	playerShip->update(dt);
	world->update(dt);
}

void PlayModule::draw() {
	wind::graphics.setColor(0, 0, 0,255);
	wind::graphics.rectangle(0, 0, wind::turbine.getWindowWidth(), wind::turbine.getWindowHeight());
	wind::graphics.setColor(255, 255, 255,255);
	playerShip->draw();
	world->draw();

	wind::graphics.setColor(0, 0, 0);
	fpsFont->draw("DT            " + std::to_string(our_dt), 32, 32);
	wind::graphics.setColor(255, 255, 255);
	fpsFont->draw("DT            " + std::to_string(our_dt), 30, 30);

	for (auto instance : missiles) {
		instance->draw();
	}
}

void PlayModule::clean() {
	//std::cout << "State was cleaned" << "\n";

}
