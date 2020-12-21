

#include <iostream>
#include <string>

#include "wind_turbine.h"

#include "test_state.h"

int main(int argc, char* argv[]) {
	wind_turbine::engine.create("Test", 1280, 720);
	wind_turbine::state_manager.addState(new TestState());
	wind_turbine::state_manager.setActiveState("test");
	wind_turbine::engine.run();

	return 0;
}