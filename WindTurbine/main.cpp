

#include <iostream>
#include <string>

#include "wind.h"

#include "game/play_module.h"
#include "game/pause_module.h"
#include "arcade/arcade_module.h"

int main(int argc, char* argv[]) {
	wind::turbine.create("WindTurbine Test", 1280, 720); 
	//wind::turbine.setMaxFPS(60);
	wind::turbine.toggleCursor();
	wind::state.addModule(new PlayModule());
	wind::state.addModule(new PauseModule());
	wind::state.addModule(new ArcadeModule());
	wind::state.setCurrentState("arcade");
	wind::turbine.run();

	return 0;
}