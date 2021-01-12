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

		/// <summary>
		/// Initializes the Wind Turbine Game Framework.
		/// </summary>
		/// <param name="title">Title of the game, appears in the top left corner of the window</param>
		/// <param name="screen_width">Window width, in pixels</param>
		/// <param name="screen_height">Window height, in pixels</param>
		void create(const char* title, int screen_width, int screen_height);

		/// <summary>
		/// Runs the main loop of the program, which first handles all events, updates the game accordingly and finally renders the screen.
		/// </summary>
		void run();

		/// <summary>
		/// Caps the frame rate of the game.
		/// </summary>
		/// <param name="limit"> = Maximum number of frames per second</param>
		void setMaxFPS(int limit);

		/// <summary>
		/// Get the renderer.
		/// </summary>
		/// <returns>Pointer to the renderer.</returns>
		SDL_Renderer* getRenderer() const;

		/// <summary>
		/// Returns the current position of the mouse as a pair.
		/// </summary>
		/// <returns>Pair of two ints (X and Y position of the mouse)</returns>
		std::pair<int, int> getMousePosition() const;

		/// <summary>
		/// Returns the position of the mouse on the X-axis
		/// </summary>
		/// <returns>X-Position</returns>
		int getMouseX() const;

		/// <summary>
		/// Returns the position of the mouse on the Y-axis
		/// </summary>
		/// <returns>Y-Position</returns>
		int getMouseY() const;

		/// <summary>
		/// Returns the current FPS of the game (This value updates once every 0.3 seconds).
		/// </summary>
		/// <returns>Frames per second of the program</returns>
		int getFPS() const;

		/// <summary>
		/// Used to check if a specific key is currently pressed down
		/// </summary>
		/// <param name="key">String representing the key, for example 'W' for the [W] key</param>
		/// <returns>True if key is pressed down, else false</returns>
		bool keyDown(std::string key) const;

		/// <summary>
		/// Used to check if a specific mouse button is currently pressed down
		/// </summary>
		/// <param name="key">Int representing the button, for example '1' for the [Left Mouse Button]</param>
		/// <returns>True if the button is pressed down, else false</returns>
		bool mouseDown(int button) const;

	private:
		void handleEvents();
		void update();
		void draw() const;
		void updateMousePosition();
		bool active() const;

		void clean();
		void setActive(bool next_state);
		void updateCurrentFPS(double dt);
		void delay(double dt);
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
