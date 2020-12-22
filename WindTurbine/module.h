#ifndef GAME_STATE_H
#define GAME_STATE_H
#include <string>
#include <vector>
#include <iostream>

namespace wind {
	class Module {
	public:
		Module();
		virtual void handleEvents();
		virtual void update(double);
		virtual void draw();
		virtual void clean();
		virtual std::string getName() { return "Game State"; };

		bool exist(std::vector<std::string> list, std::string state);
		bool inUpdateList(std::string state);
		bool inDrawList(std::string state);
		bool inEventList(std::string state);

		virtual std::vector<std::string> getUpdateList() { return updateOn; };
		virtual std::vector<std::string> getDrawList() { return drawOn; };
		virtual std::vector<std::string> getEventList() { return eventOn; };
	private:
		std::vector<std::string> updateOn;
		std::vector<std::string> drawOn;
		std::vector<std::string> eventOn;
	};
}

#endif