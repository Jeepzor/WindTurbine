#ifndef GAME_MODULE_H
#define GAME_MODULE_H
#include <string>
#include <vector>
#include <iostream>
#include <SDL.h>


namespace wind {
	class GameModule {
	public:
		GameModule();
		virtual void keyPressed(std::string key) = 0;
		virtual void update(double) = 0;
		virtual void draw() = 0;
		virtual void clean() = 0;
		virtual std::string getName() = 0;

		virtual bool exist(std::vector<std::string> list, std::string state);
		virtual bool inUpdateList(std::string state);
		virtual bool inDrawList(std::string state);
		virtual bool inEventList(std::string state);

		virtual std::vector<std::string> getUpdateList() { return updateOn; };
		virtual std::vector<std::string> getDrawList() { return drawOn; };
		virtual std::vector<std::string> getEventList() { return eventOn; };
	
	protected:
		std::vector<std::string> updateOn;
		std::vector<std::string> drawOn;
		std::vector<std::string> eventOn;
	};
}

#endif