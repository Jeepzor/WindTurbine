#ifndef STATE_MANAGER_H
#define STATE_MANAGER_H

#include <string>
#include <vector>
#include <SDL.h>

#include "game_module.h"



namespace wind {
	class State {
		friend class Turbine;
	public:
		State();

		/// <summary>
		/// Set the state, which determins what module(s) 
		/// will Update, Draw and litsen for Event callbacks
		/// </summary>
		/// <param name="state"> = Next state</param>
		void setCurrentState(std::string state);

		/// <summary>
		/// Insert a new module into the State manager
		/// </summary>
		/// <param name="new_module"> = Pointer to the Game Module which you wish to add</param>
		void addModule(GameModule* new_module);
	private:
		std::string getActiveState() const;

		void keyPressed(std::string key) const;
		void keyReleased(std::string key) const;
		void mousePressed(int button) const;
		void mouseReleased(int button) const;
		
		void update(double) const;
		void draw() const;
		void changed(std::string state)const;
		bool exist(std::string state) const;
		void extractStates(GameModule*);
		std::vector<GameModule*> game_modules; //Vector containing all game-modules.
		std::vector<std::string> states; //Vector containing all names of states.
		std::string currentState;
	};

	extern State state;
}

#endif
