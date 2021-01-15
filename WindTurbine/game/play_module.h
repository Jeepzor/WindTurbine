#ifndef PLAY_MODULE_H
#define PLAY_MODULE_H

#include<vector>

#include "../wind.h"
#include "player.h"


class PlayModule : public wind::GameModule {
public:
	PlayModule();
	void keyPressed(std::string key);
	void keyReleased(std::string key);
	void mousePressed(int button);
	void mouseReleased(int button);
	void update(double dt);
	void draw();

	void addEntity(wind::Entity* entity);

	wind::PhysicsWorld* getWorld() { return world; };

	void clean();
	std::string getName() { return "playing"; };

private:

	void updateEntities(double dt);
	void drawEntities();
	void removeDeadEntities();
	void updateSpawner(double dt);

	double spawnTimer = 0;
	double spawnRate = 3;

	Player* playerShip;
	wind::PhysicsWorld* world;
	wind::Font* fpsFont;
	std::vector<wind::Entity*> entities;
};

#endif


