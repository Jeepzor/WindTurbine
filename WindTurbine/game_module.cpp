#include <string>
#include <iostream>

#include "game_module.h"

namespace wind {
	GameModule::GameModule() {
		updateOn;
		drawOn;
		eventOn;
	}

	void GameModule::handleEvents() {

	}

	void GameModule::update(double dt) {

	}

	void GameModule::draw() {

	}

	void GameModule::clean() {

	}

	bool GameModule::inUpdateList(std::string state) {
		return(exist(updateOn, state));
	}
	
	bool GameModule::inDrawList(std::string state) {
		return(exist(updateOn, state));
	}
	
	bool GameModule::inEventList(std::string state) {
		return(exist(updateOn, state));
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