

#include <iostream>
#include <string>

#include "wind_turbine.h"

#include "play_module.h"
#include "pause_module.h"

int main(int argc, char* argv[]) {
	wind::turbine.create("WindTurbine Test", 1280, 720);
	wind::state.addModule(new PlayModule());
	wind::state.addModule(new PauseModule());
	wind::state.setCurrentState("paused");
	wind::turbine.run();

	return 0;
}

/*
* Poly -> Circle
* "Squeeze past"
* Rotation ?
* "Square polys"
*/