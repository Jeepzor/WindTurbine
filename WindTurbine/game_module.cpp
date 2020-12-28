#include <string>
#include <iostream>

#include "game_module.h"

namespace wind {
	GameModule::GameModule() {}

	bool GameModule::inUpdateList(std::string state) {
		return(exist(updateOn, state));
	}
	
	bool GameModule::inDrawList(std::string state) {
		return(exist(drawOn, state));
	}
	
	bool GameModule::inEventList(std::string state) {
		return(exist(eventOn, state));
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