
#ifndef ARCADE_MODULE_H
#define ARCADE_MODULE_H


#include "../wind.h"
#include "character.h"

class ArcadeModule : public wind::GameModule {
public:
	ArcadeModule();
	void keyPressed(std::string key);
	void update(double dt);
	void draw();
	void clean();
	std::string getName() { return "arcade"; }

private:	

	bool inRange = false;
	wind::PhysicsWorld* world;
	Character* character;
	wind::Image* bg;
	wind::Font* arcadeFont;
};

#endif


