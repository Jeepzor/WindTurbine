

#include <iostream>
#include <string>

#include "wind.h"

#include "game/play_module.h"
#include "game/pause_module.h"
#include "game/gameover_module.h"
#include "arcade/arcade_module.h"
#include "othello/othello_module.h"

int main(int argc, char* argv[]) {
	wind::turbine.create("WindTurbine Test", 1280, 720); 
	//wind::turbine.setMaxFPS(60);
	
	//wind::turbine.toggleCursor();
	wind::state.addModule(PlayModule::getInstance());
	wind::state.addModule(PauseModule::getInstance());
	wind::state.addModule(ArcadeModule::getInstance());
	wind::state.addModule(GameoverModule::getInstance());
	wind::state.addModule(OthelloModule::getInstance());
	wind::state.setCurrentState("othello");

	wind::turbine.run(); 

	return 0;
}