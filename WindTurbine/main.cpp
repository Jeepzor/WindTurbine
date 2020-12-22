

#include <iostream>
#include <string>

#include "wind_turbine.h"

#include "test_module.h"

int main(int argc, char* argv[]) {
	wind::turbine.create("Test", 1280, 720);
	wind::state.addModule(new TestModule());
	wind::state.setCurrentState("test");
	wind::turbine.run();

	return 0;
}