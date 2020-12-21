#ifndef WIND_TURBINE_H
#define WIND_TURBINE_H

#include <iostream>

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

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
		bool active();
		SDL_Renderer* getRenderer() const;
		bool keyboard_is_down(std::string);

	private:
		bool is_active;
		SDL_Renderer* renderer;
		SDL_Window* window;
		double previousFrameTime;
		double currentFrameTime;
		double dt;
		const Uint8* keyboard_state;
	};

	extern Turbine turbine;
}
#endif
