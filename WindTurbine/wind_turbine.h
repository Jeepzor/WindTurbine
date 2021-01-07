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
		void draw() const;
		void clean();
		void setActive(bool next_state);
		void setMaxFPS(int limit);
		void delay(double dt);
		void updateMousePosition();

		SDL_Renderer* getRenderer() const;
		std::pair<int, int> getMousePosition() const;
		int getMouseX() const;
		int getMouseY() const;
		int getFPS() const;

		bool active() const;
		bool keyDown(std::string key) const;
		bool mouseDown(int button) const;

	private:
		void updateCurrentFPS(double dt);
		double fpsTimer = 0.0; //Time since last update of FPS counter (in seconds)
		double fpsRate = 1.0; //How often should the FPS counter update (in seconds)

		double fpsCurrent;
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
