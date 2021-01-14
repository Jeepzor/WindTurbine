

#include <iostream>
#include <string>

#include "wind.h"

#include "game/play_module.h"
#include "game/pause_module.h"

int main(int argc, char* argv[]) {
	wind::turbine.create("WindTurbine Test", 1280, 720); 
	//wind::turbine.setMaxFPS(60);
	wind::state.addModule(new PlayModule());
	wind::state.addModule(new PauseModule());
	wind::state.setCurrentState("paused");
	wind::turbine.run();

	return 0;
}