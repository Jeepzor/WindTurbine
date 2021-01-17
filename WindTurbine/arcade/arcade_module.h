
#ifndef ARCADE_MODULE_H
#define ARCADE_MODULE_H


#include "../wind.h"
#include "character.h"

class ArcadeModule : public wind::GameModule {
public:
	static ArcadeModule* getInstance() {
		return new ArcadeModule();
	}

	void keyPressed(std::string key);
	void update(double dt);
	void draw();
	void clean();
	std::string getName() { return "arcade"; }

private:	
	ArcadeModule();
	ArcadeModule(const ArcadeModule& other) = delete;
	const ArcadeModule& operator=(const ArcadeModule& other) = delete;

	bool inRange = false;
	wind::PhysicsWorld* world;
	Character* character;
	wind::Image* bg;
	wind::Image* damaged;
	wind::Font* arcadeFont;
};

#endif


