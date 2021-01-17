
#ifndef GAMEOVER_MODULE_H
#define GAMEOVER_MODULE_H


#include "../wind.h"

class GameoverModule : public wind::GameModule {
public:
	static GameoverModule* getInstance() {
		return new GameoverModule();
	}

	void keyPressed(std::string key);
	void update(double dt);
	void draw();
	void clean();
	std::string getName() { return "paused"; }

private:
	GameoverModule();
	GameoverModule(const GameoverModule& other) = delete;
	const GameoverModule& operator=(const GameoverModule& other) = delete;

	double timeWave = 0;
	wind::Font* endFont;
};

#endif


