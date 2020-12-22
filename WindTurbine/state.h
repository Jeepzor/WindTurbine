#ifndef STATE_MANAGER_H
#define STATE_MANAGER_H

#include <string>
#include <vector>
#include "module.h"



namespace wind {
	class State {
	public:
		State();
		std::string getActiveState();
		bool exist(std::string state);
		void setCurrentState(std::string state);
		void addModule(Module*);
		void update(double);
		void draw();
	private:
		void extractStates(Module*);
		std::vector<Module*> modules; //Vector containing all modules.
		std::vector<std::string> states; //Vector containing all names of states.
		std::string currentState;
	};

	extern State state;
}

#endif
