
#include "wind_turbine.h"
#include "state.h"
#include "module.h"

class TestModule : public wind::Module {
public:
	TestModule();
	void handleEvents();
	void update(double);
	void draw();
	void clean();
	std::string getName() { return "test"; }

	std::vector<std::string> getUpdateList() { return updateOn; };
	std::vector<std::string> getDrawList() { return drawOn; };
	std::vector<std::string> getEventList() { return eventOn; };

private:
	std::vector<std::string> updateOn;
	std::vector<std::string> drawOn;
	std::vector<std::string> eventOn;
};


