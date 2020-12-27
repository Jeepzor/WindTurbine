#ifndef STATE_MANAGER_H
#define STATE_MANAGER_H

#include <string>
#include <vector>
#include <SDL.h>

#include "game_module.h"



namespace wind {
	class State {
	public:
		State();
		std::string getActiveState();
		bool exist(std::string state);
		void setCurrentState(std::string state);
		void addModule(GameModule*);

		void keyPressed(std::string key);
		void keyReleased(std::string key);
		void mousePressed(int button);
		void mouseReleased(int button);
		
		void update(double);
		void draw();
	private:
		void extractStates(GameModule*);
		std::vector<GameModule*> game_modules; //Vector containing all game-modules.
		std::vector<std::string> states; //Vector containing all names of states.
		std::string currentState;
	};

	extern State state;
}

#endif
