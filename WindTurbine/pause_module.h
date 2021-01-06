
#ifndef PAUSE_MODULE_H
#define PAUSE_MODULE_H


#include "wind_turbine.h"
#include "font.h"

class PauseModule : public wind::GameModule {
public:
	PauseModule();
	void keyPressed(std::string key);
	void update(double dt);
	void draw();
	void clean();
	std::string getName() { return "paused"; }

private: 
	wind::Image* pauseImg;
	wind::Font* pauseFont;
};

#endif


