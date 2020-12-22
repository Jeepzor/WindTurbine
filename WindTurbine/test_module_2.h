
#ifndef TEST_MODULE_2_H
#define TEST_MODULE_2_H


#include "wind_turbine.h"
#include "state.h"
#include "module.h"

class TestModule2 : public wind::Module {
public:
	TestModule2();
	void handleEvents();
	void update(double);
	void draw();
	void clean();
	std::string getName() { return "test"; }
};

#endif


