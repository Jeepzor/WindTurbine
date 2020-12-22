#include <string>
#include <vector>
#include <stdexcept>
#include <iostream>


#include "state.h"
#include "module.h"


namespace wind {
	State::State() {
		states;
		modules;
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
	
	void State::addModule(Module* newModule) {
		extractStates(newModule);
		modules.push_back(newModule);
	}

	void State::extractStates(Module* module) {
		for (auto new_state : module->getUpdateList()) {
			if (!exist(new_state)) {
				states.push_back(new_state);
			}
		}
		
		for (auto new_state : module->getDrawList()) {
			if (!exist(new_state)) {
				states.push_back(new_state);
			}
		}
		
		for (auto new_state : module->getEventList()) {
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

	void State::update(double dt) {
		//getActiveState()->update(dt);
	}
	
	void State::draw() {
		
		//getActiveState()->draw();
		
	}

	State state;
}
