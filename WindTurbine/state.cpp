#include <string>
#include <vector>
#include <stdexcept>
#include <iostream>


#include "state.h"


namespace wind {
	State::State() {
		states;
		game_modules;
		currentState = "";
	}

	std::string State::getActiveState() {
		return currentState;
	}

	void State::setCurrentState(std::string next_active_state) {
		if (exist(next_active_state))
		{
			currentState = next_active_state;
		}
		else {
			std::cerr << "Error: State '" + next_active_state + "' does not exist" << "\n";
			//throw std::runtime_error("Error: State '" + next_active_state + "' does not exist");
		}
	}
	
	void State::addModule(GameModule* new_game_module) {
		extractStates(new_game_module);
		game_modules.push_back(new_game_module);
	}

	void State::extractStates(GameModule* game_module) {
		for (auto new_state : game_module->getUpdateList()) {
			if (!exist(new_state)) {
				states.push_back(new_state);
			}
		}
		
		for (auto new_state : game_module->getDrawList()) {
			if (!exist(new_state)) {
				states.push_back(new_state);
			}
		}
		
		for (auto new_state : game_module->getEventList()) {
			if (!exist(new_state)) {
				states.push_back(new_state);
			}
		}
	}

	bool State::exist(std::string state_to_find) {
		if (std::find(states.begin(), states.end(), state_to_find) != states.end())
		{
			return true;
		}
		else{
			return false;
		}
	}

	void State::keyPressed(std::string key) {
		for (auto current_game_module : game_modules) {
			if (current_game_module->inEventList(currentState)) {
				current_game_module->keyPressed(key);
			}
		}
	}

	void State::update(double dt) {
		for (auto current_game_module : game_modules) {
			if (current_game_module->inUpdateList(currentState)) {
				current_game_module->update(dt);
			}
		}
	}
	
	void State::draw() {
		for (auto current_game_module : game_modules) {
			if (current_game_module->inDrawList(currentState)) {
				current_game_module->draw();
			}
		}
	}

	State state;
}
