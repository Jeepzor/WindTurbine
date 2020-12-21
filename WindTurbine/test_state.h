
#include "wind_turbine.h"
#include "state_manager.h"
#include "game_state.h"

class TestState : public wind::GameState {
public:
	void handleEvents();
	void update(double);
	void draw();
	void clean();
	std::string getName() { return "test"; }

};


