#ifndef WIND_TURBINE_H
#define WIND_TURBINE_H

#include <iostream>

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include "game_module.h"
#include "state.h"
#include "image.h"

namespace wind {
	class Turbine {
	public:
		Turbine();
		~Turbine();

		void create(const char* title, int screen_width, int screen_height);
		void run();
		void handleEvents();
		void update();
		void draw();
		void clean();
		void setActive(bool next_state);
		void setMaxFPS(int limit);
		void delay(double dt);
		void storeMousePosition(int x, int y);

		SDL_Renderer* getRenderer() const;
		std::pair<int, int> getMousePosition();
		int getMouseX();
		int getMouseY();

		bool active();
		bool keyDown(std::string key);
		bool mouseDown(int button);

	private:
		int fpsLimit;
		bool is_active;
		double previousFrameTime;
		double currentFrameTime;
		double dt;

		const Uint8* keyboard_state;
		Uint32 mouse_state;
		std::pair<int, int> mousePosition;

		SDL_Renderer* renderer;
		SDL_Window* window;
	};

	extern Turbine turbine;
}
#endif
