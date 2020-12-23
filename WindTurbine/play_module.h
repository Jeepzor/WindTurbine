#ifndef TEST_MODULE_H
#define TEST_MODULE_H

#include "wind_turbine.h"

class PlayModule : public wind::GameModule {
public:
	PlayModule();
	void handleEvents(SDL_Event* current_event);
	void update(double dt);
	void draw();
	void clean();
	std::string getName() { return "playing"; };

private:
	wind::Image test;
	wind::Image bg;
};

#endif


