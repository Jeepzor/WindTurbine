
#ifndef PAUSE_MODULE_H
#define PAUSE_MODULE_H


#include "wind_turbine.h"

class PauseModule : public wind::GameModule {
public:
	PauseModule();
	void handleEvents();
	void update(double);
	void draw();
	void clean();
	std::string getName() { return "test"; }

private: 
	wind::Image pauseImg;
};

#endif


