

#include <iostream>
#include <string>

#include "wind_turbine.h"

#include "play_module.h"

int main(int argc, char* argv[]) {
	wind::turbine.create("WindTurbine Test", 1280, 720);
	wind::state.addModule(new PlayModule());
	wind::state.setCurrentState("play");
	wind::turbine.run();

	return 0;
}