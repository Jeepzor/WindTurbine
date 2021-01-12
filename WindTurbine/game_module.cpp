#include <string>
#include <iostream>

#include "game_module.h"

namespace wind {
	GameModule::GameModule() {}

	bool GameModule::inUpdateStates(std::string state) {
		return(exist(updateOn, state));
	}
	
	bool GameModule::inDrawStates(std::string state) {
		return(exist(drawOn, state));
	}
	
	bool GameModule::inEventStates(std::string state) {
		return(exist(eventOn, state));
	}

	bool GameModule::inInitStates(std::string state) {
		return(exist(initOn, state));
	}

	bool GameModule::inCleanStates(std::string state) {
		return(exist(cleanOn, state));
	}

	//Returns true if the module is subscribed to that state.
	bool GameModule::exist(std::vector<std::string> list, std::string state) {
		if (std::find(list.begin(), list.end(), state) != list.end())
		{
			return true;
		}
		else {
			return false;
		}
	}
}