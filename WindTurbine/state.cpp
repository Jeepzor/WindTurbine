#include <string>
#include <vector>
#include <stdexcept>
#include <iostream>


#include "state.h"
#include "graphics.h"


namespace wind {
	State::State() {
		states;
		game_modules;
		currentState = "";
	}

	std::string State::getActiveState() const {
		return currentState;
	}

	void State::setCurrentState(std::string next_active_state) {
		if (exist(next_active_state))
		{
			currentState = next_active_state;
		}
		else {
			std::cerr << "Error: State '" + next_active_state + "' does not exist" << "\n";
			throw std::runtime_error("Error: State '" + next_active_state + "' does not exist");
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

	bool State::exist(std::string state_to_find) const {
		if (std::find(states.begin(), states.end(), state_to_find) != states.end())
		{
			return true;
		}
		else{
			return false;
		}
	}

	void State::keyPressed(std::string key) const {
		for (auto current_game_module : game_modules) {
			if (current_game_module->inEventList(currentState)) {
				current_game_module->keyPressed(key);
			}
		}
	}	
	
	void State::keyReleased(std::string key) const {
		for (auto current_game_module : game_modules) {
			if (current_game_module->inEventList(currentState)) {
				current_game_module->keyReleased(key);
			}
		}
	}
	
	void State::mousePressed(int button) const {
		for (auto current_game_module : game_modules) {
			if (current_game_module->inEventList(currentState)) {
				current_game_module->mousePressed(button);
			}
		}
	}	
	
	void State::mouseReleased(int button) const {
		for (auto current_game_module : game_modules) {
			if (current_game_module->inEventList(currentState)) {
				current_game_module->mouseReleased(button);
			}
		}
	}

	void State::update(double dt) const {
		if (dt > 0.1) { dt = 0.1; };
		for (auto current_game_module : game_modules) {
			if (current_game_module->inUpdateList(currentState)) {
				current_game_module->update(dt);
			}
		}
	}
	
	void State::draw() const {
		for (auto current_game_module : game_modules) {
			if (current_game_module->inDrawList(currentState)) {
				wind::graphics.clearColor();
				current_game_module->draw();
			}
		}
	}

	State state;
}
