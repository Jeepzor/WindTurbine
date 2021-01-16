
#ifndef GAMEOVER_MODULE_H
#define GAMEOVER_MODULE_H


#include "../wind.h"

class GameoverModule : public wind::GameModule {
public:
	GameoverModule();
	void keyPressed(std::string key);
	void update(double dt);
	void draw();
	void clean();
	std::string getName() { return "paused"; }

private:
	double timeWave = 0;
	wind::Font* endFont;
};

#endif


