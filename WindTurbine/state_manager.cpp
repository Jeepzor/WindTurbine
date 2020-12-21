#include <string>
#include <vector>
#include <stdexcept>
#include <iostream>


#include "game_state.h"
#include "state_manager.h"


namespace wind_turbine {
	StateManager::StateManager() {
		states;
		active_state = nullptr;
	}

	GameState* StateManager::getActiveState() {
		return active_state;
	}

	void StateManager::setActiveState(std::string next_active_state) {
		if (states.size() == 0) {
			std::cerr << "Error: State '" + next_active_state + "' does not exist" << "\n";
			throw std::runtime_error("Error: State '" + next_active_state + "' does not exist");
		}

		for (auto state : states) {
			bool found = false;
			if (state->getName() == next_active_state)
			{
				found = true;
				active_state = state;
			}

			if (!found) {
				std::cerr << "Error: State '" + next_active_state + "' does not exist" << "\n";

				throw std::runtime_error("Error: State '" + next_active_state + "' does not exist");
			}
		}
	}
	
	void StateManager::addState(GameState* newState) {
		states.push_back(newState);
	}

	bool StateManager::hasState() {
		return (active_state != nullptr);
	}

	void StateManager::update(double dt) {
		if (hasState()){
			getActiveState()->update(dt);
		}
	}
	
	void StateManager::draw() {
		if (hasState()) {
			getActiveState()->draw();
		}
	}

	StateManager state_manager;
}
