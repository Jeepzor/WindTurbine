#ifndef GAME_MODULE_H
#define GAME_MODULE_H
#include <string>
#include <vector>
#include <iostream>
#include <SDL.h>


namespace wind {
	class GameModule {
	public:
		friend class State; // State manages all modules

		/// <summary>
		/// Callback function, triggers when a key is pressed down
		/// </summary>
		/// <param name="key"> = The key that was pressed</param>
		virtual void keyPressed(std::string key){};

		/// <summary>
		/// Callback function, triggers when a key is released
		/// </summary>
		/// <param name="key"> = The key that was released</param>
		virtual void keyReleased(std::string key){};

		/// <summary>
		/// Callback function, triggers when a mouse button is pressed
		/// </summary>
		/// <param name="key"> = The button id (int) that was pressed</param>
		virtual void mousePressed(int button){};

		/// <summary>
		/// Callback function, triggers when a mouse button is released
		/// </summary>
		/// <param name="key"> = The button id (int) that was released</param>
		virtual void mouseReleased(int button){};

		/// <summary>
		/// Updates the GameModule, should be used to for any logic/calculations which needs to be framerate independent.
		/// </summary>
		/// <param name=""> = Delta time</param>
		virtual void update(double){};

		/// <summary>
		/// Draws the GameModule, should be used to render graphics on the screen.
		/// </summary>
		virtual void draw(){};

		/// <summary>
		/// Callback function which is called when the state changes to a state which is in the GameModules "cleanOn"-list.
		/// </summary>
		virtual void clean(){};

		/// <summary>
		/// Callback function which is called when the state changes to a state which is in the GameModules "cleanOn"-list.
		/// Note: Only occurs if the GameModule is not initialized (clean(), de-initializes a GameModule).
		/// </summary>
		virtual void init(){};

		/// <summary>
		/// Get the name of the GameModule
		/// </summary>
		/// <returns>string name</returns>
		virtual std::string getName() = 0; //Explicitly abstract; needs to be overridden in child.


		

		virtual ~GameModule() = 0 {};
	protected:
		//The following functions are for the friend class State
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
		virtual bool exist(std::vector<std::string> list, std::string state);
		//The above functions are for the friend class State

		GameModule();
		GameModule(const GameModule& other) = delete;
		const GameModule& operator=(const GameModule& other) = delete;

		bool initialized = false;

		std::vector<std::string> updateOn;
		std::vector<std::string> drawOn;
		std::vector<std::string> eventOn;
		std::vector<std::string> cleanOn;
		std::vector<std::string> initOn;
	};
}

#endif