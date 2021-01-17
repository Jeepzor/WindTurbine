#include "play_module.h"
#include "player.h"
#include "missile.h"
#include "rock.h"
#include "boom.h"
#include "star.h"

PlayModule::PlayModule() {
	updateOn = { "play" };
	drawOn = { "play","paused", "gameover" };
	eventOn = { "play" };
	initOn = { "play" };
	cleanOn = { "arcade" };

	cursor = wind::Image::getInstance("game/assets/xhair.png");

	world = new wind::PhysicsWorld(0, 0);

	text = new wind::Font("game/assets/bit.ttf", 32);

	playerShip = new Player(world);
}



void PlayModule::keyPressed(std::string key) {
	handleInput(key);
	if (key == "P") {
		wind::state.setCurrentState("paused");
	}
	else if (key == "O") {
		world->toggleDebug();
	}
}

wind::Font* PlayModule::getFont() {
	return text;
}

void PlayModule::handleInput(std::string key) {
	if (key.size() == 1) { // Prevent crashes when inputting symbols like § and ´
		if (std::isdigit(key[0])) {
			if (input.size() < 3) { input += key;; };
		}
		
	}else if (key == "Backspace") {
		if (!input.empty()) {
			input.resize(input.size() - 1);
		}
	}
}

void PlayModule::keyReleased(std::string key) {}

void PlayModule::mousePressed(int button) {
	if (button == 1) {
		if (!input.empty()) {
			addEntity(Missile::getInstance(this, playerShip->getLaunchX(), playerShip->getLaunchY(), playerShip->getAngle(), input));
			input = "";
		}
	}
}

void PlayModule::mouseReleased(int button) {}

void PlayModule::addEntity(wind::Entity* entity) {
	std::shared_ptr<wind::Entity> smart_ptr(entity);
	entities.push_back(smart_ptr);
}

void PlayModule::update(double dt) {
	incrementScore(dt);
	updateSpawner(dt);
	updateEntities(dt);
	playerShip->update(dt);
	world->update(dt);
}

void PlayModule::incrementScore(double dt) {
	score += dt;
}


void PlayModule::updateEntities(double dt) {
	for (auto& instance : entities) {
		instance->update(dt);
	}
	removeDeadEntities();
}

void PlayModule::removeDeadEntities() {
	std::vector<std::shared_ptr<wind::Entity>>::iterator iter;
	for (iter = entities.begin(); iter != entities.end(); ) {
		if (!(*iter)->isAlive()) {

			iter = entities.erase(iter);
		}
		else {
			++iter;
		}
	}
}

void PlayModule::updateSpawner(double dt) {
	spawnTimer -= dt;
	if (spawnTimer <= 0) {
		spawnTimer = spawnRate;
		double position_x = 1400;
		double position_y = 920.0 * wind::math.random() - 200;
		double angle_to_player = wind::math.getAngle(position_x, position_y, playerShip->getX(), playerShip->getY());
		addEntity(Rock::getInstance(this, position_x, position_y, angle_to_player));
	}
}

void PlayModule::draw() {
	wind::graphics.setColor(0, 0, 0,255);
	wind::graphics.rectangle(0, 0, wind::turbine.getWindowWidth(), wind::turbine.getWindowHeight());
	wind::graphics.setColor(255, 255, 255,255);
	drawEntities();

	playerShip->draw();

	wind::graphics.setColor(255, 255, 255);
	text->draw("Press O for debug-mode", 30, 10);
	text->draw("Press P for pause", 30, 40);
	text->draw("Health: " + std::to_string(playerShip->getHealth()), 30, 70);
	text->draw("Score: " + std::to_string(static_cast<int>(score)), 30, 100);
	drawCursor();
	world->draw();
}

void PlayModule::drawCursor() {
	double mouse_w;
	double mouse_h;
	cursor->getDimensions(mouse_w, mouse_h);
	double mx = wind::turbine.getMouseX() ; // Just to shorten the line
	double my = wind::turbine.getMouseY() ; // Just to shorten the line

	if (input.size() > 0) {
		wind::graphics.setColor(25, 255,25);
		wind::graphics.rectangle("line", mx - 30, my - 50, 60, 30);
		const char* c = input.c_str();
		int text_width;
		TTF_SizeText(text->getFont(), c, &text_width, NULL);
		text->draw(input, wind::turbine.getMouseX() - text_width / 2, wind::turbine.getMouseY() - 50);
	}else{ 
		wind::graphics.setColor(255,25,25);
	}

	cursor->draw(mx - mouse_w / 2, my - mouse_h / 2);
	wind::graphics.clearColor();
}

void PlayModule::drawEntities() {
	for (auto& instance : entities) {
		instance->draw();
	}
}


void PlayModule::clean() {
	spawnTimer = 0;
	score = 0;
	playerShip->reset();
	input = "";
	entities.clear();
}

void PlayModule::init() {
	for (int i = 0; i < 100; i++)
	{
		addEntity(Star::getInstance(wind::turbine.getWindowWidth() * wind::math.random(), wind::turbine.getWindowHeight() * wind::math.random()));
	}

	Rock::counter = 0;
}
