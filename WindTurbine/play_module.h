#ifndef TEST_MODULE_H
#define TEST_MODULE_H

#include "wind_turbine.h"

class PlayModule : public wind::GameModule {
public:
	PlayModule();
	void handleEvents();
	void update(double);
	void draw();
	void clean();
	std::string getName() { return "test"; };

private:

};

#endif


