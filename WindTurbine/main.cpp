

#include <iostream>
#include <string>

#include "wind_turbine.h"

#include "test_state.h"

int main(int argc, char* argv[]) {
	wind::turbine.create("Test", 1280, 720);
	wind::state_manager.addState(new TestState());
	wind::state_manager.setActiveState("test");
	wind::turbine.run();

	return 0;
}