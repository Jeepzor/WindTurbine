#ifndef TEST_MODULE_H
#define TEST_MODULE_H

#include "wind_turbine.h"
#include "state.h"
#include "module.h"

class TestModule : public wind::Module {
public:
	TestModule();
	void handleEvents();
	void update(double);
	void draw();
	void clean();
	std::string getName() { return "test"; };

private:

};

#endif


