
#ifndef PAUSE_MODULE_H
#define PAUSE_MODULE_H


#include "wind_turbine.h"

class PauseModule : public wind::GameModule {
public:
	PauseModule();
	void handleEvents(SDL_Event* current_event);
	void update(double dt);
	void draw();
	void clean();
	std::string getName() { return "paused"; }

private: 
	wind::Image pauseImg;
};

#endif


