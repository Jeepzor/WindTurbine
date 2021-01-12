#ifndef GAME_MODULE_H
#define GAME_MODULE_H
#include <string>
#include <vector>
#include <iostream>
#include <SDL.h>


namespace wind {
	class GameModule {
	public:
		virtual void keyPressed(std::string key){};
		virtual void keyReleased(std::string key){};
		virtual void mousePressed(int button){};
		virtual void mouseReleased(int button){};

		virtual void update(double){};
		virtual void draw(){};
		virtual void clean(){};
		virtual void init(){};

		virtual std::string getName() = 0; //Explicitly abstract; needs to be overridden in child.

		virtual bool exist(std::vector<std::string> list, std::string state);
		virtual bool inUpdateStates(std::string state);
		virtual bool inDrawStates(std::string state);
		virtual bool inEventStates(std::string state);
		virtual bool inCleanStates(std::string state);
		virtual bool inInitStates(std::string state);

		virtual std::vector<std::string> getUpdateStates() { return updateOn; };
		virtual std::vector<std::string> getDrawStates() { return drawOn; };
		virtual std::vector<std::string> getEventStates() { return eventOn; };
		virtual std::vector<std::string> getCleanStates() { return cleanOn; };
		virtual std::vector<std::string> getInitStates() { return initOn; };
		
		bool isInitialized() { return initialized; };
		void setInitialized(bool flag) {initialized = flag; };
		virtual ~GameModule() = 0 {};
	protected:
		bool initialized = false;
		GameModule();

		GameModule(const GameModule& other) = delete;
		const GameModule& operator=(const GameModule& other) = delete;

		std::vector<std::string> updateOn;
		std::vector<std::string> drawOn;
		std::vector<std::string> eventOn;
		std::vector<std::string> cleanOn;
		std::vector<std::string> initOn;
	};
}

#endif