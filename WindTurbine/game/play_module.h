#ifndef PLAY_MODULE_H
#define PLAY_MODULE_H

#include<vector>

#include "../wind.h"
#include "player.h"


class PlayModule : public wind::GameModule {
public:
	PlayModule();
	void keyPressed(std::string key) override;
	void keyReleased(std::string key) override;
	void mousePressed(int button) override;
	void mouseReleased(int button) override;
	void update(double dt) override;
	void draw() override;
	void clean() override;
	void init() override;
	void addEntity(wind::Entity* entity);

	wind::PhysicsWorld* getWorld() { return world; };
	wind::Font* getFont();
	std::string getName() { return "playing"; };
private:
	void drawCursor();
	void updateEntities(double dt);
	void incrementScore(double dt);
	void drawEntities();
	void removeDeadEntities();
	void updateSpawner(double dt);
	void handleInput(std::string key);

	double score = 0;
	double spawnTimer = 0;
	double spawnRate = 3;

	std::string input;
	wind::Image* cursor;
	wind::PhysicsWorld* world;
	wind::Font* text;
	Player* playerShip;

	std::vector<std::shared_ptr<wind::Entity>> entities;
};

#endif


