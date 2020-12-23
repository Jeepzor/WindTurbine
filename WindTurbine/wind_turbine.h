#ifndef WIND_TURBINE_H
#define WIND_TURBINE_H

#include <iostream>

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include "game_module.h"
#include "state.h"

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
		void setActive(bool);
		void setMaxFPS(int limit);
		void delay(double dt);
		bool active();
		SDL_Renderer* getRenderer() const;
		bool keyboardIsDown(std::string);

	private:
		bool is_active;
		SDL_Renderer* renderer;
		SDL_Window* window;
		double previousFrameTime;
		double currentFrameTime;
		double dt;
		const Uint8* keyboard_state;
		int fpsLimit;
	};

	extern Turbine turbine;
}
#endif
