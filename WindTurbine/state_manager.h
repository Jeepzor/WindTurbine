#ifndef STATE_MANAGER_H
#define STATE_MANAGER_H

#include <string>
#include <vector>
#include "game_state.h"



namespace wind {
	class StateManager {
	public:
		StateManager();
		GameState* getActiveState();
		void setActiveState(std::string);
		void addState(GameState*);
		bool hasState();
		void update(double);
		void draw();
	private:
		std::vector<GameState*> states;
		GameState* active_state;
	};

	extern StateManager state_manager;
}

#endif
