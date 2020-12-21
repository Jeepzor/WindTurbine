#ifndef GAME_STATE_H
#define GAME_STATE_H
#include <string>
#include <iostream>

namespace wind_turbine {
	class GameState {
	public:
		virtual void handleEvents();
		virtual void update(double);
		virtual void draw();
		virtual void clean();
		virtual std::string getName() { return "Game State"; };
	};
}

#endif