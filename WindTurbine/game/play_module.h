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
	void clean();
	std::string getName() { return "playing"; };

private:
	double our_dt;
	wind::Image* bg;
	Player* playerShip;
	wind::PhysicsWorld* world;
	wind::Font* fpsFont;
	std::vector<wind::Entity*> missiles;
};

#endif


