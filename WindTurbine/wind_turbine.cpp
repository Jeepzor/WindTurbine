#include "wind_turbine.h"
#include "state.h"
#include "image.h"
#include "hibernate.h"
#include "fade.h"

namespace wind {
	Turbine::Turbine() {
		isActive = false;
		window = nullptr;
		renderer = nullptr;
		previousFrameTime = 0;
		currentFrameTime = 0;
		fpsLimit = 0;
		dt = 0;
		keyboard_state = SDL_GetKeyboardState(NULL);
	}

	Turbine::~Turbine() {
		clean();
	}

	//Initializes all of the essential SDL components.
	void Turbine::create(const char* title, int screen_width, int screen_height) {
		width = static_cast<double>(screen_width);
		height = static_cast<double>(screen_height);

		//Initializes SDL-base and and validates it succeded.
		if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
			std::cerr << "SLD ERROR: " << SDL_GetError() << "\n";
			exit(-1);
		}

		//Initializes SDL Fonts and validates it succeded.
		if (TTF_Init() > 0) {
			std::cerr << "TTF INIT ERROR: " << "\n";
			exit(-1);
		}

		//Initializes SDL Audio and validates it succeded.
		if (Mix_OpenAudio(
			22050, //Frequency
			AUDIO_S16SYS, //Format
			2, //Number of channels
			4096 //Buffer chunk size
		) != 0) {
			std::cerr << "Mix OpenAudio ERROR: " << "\n";
		}

		//Initializes the Window and sets the widht and height to the passed in values.
		window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screen_width, screen_height, SDL_WINDOW_SHOWN);
		if (window == nullptr) {
			std::cerr << "SDL ERROR: " << SDL_GetError() << "\n";
			SDL_Quit();
			exit(-1);
		}

		//Initializes the renderer and validates it succeded.
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
		SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
		if (renderer == nullptr) {
			std::cerr << "SDL ERROR: " << SDL_GetError() << "\n";
			SDL_DestroyWindow(window);
			SDL_Quit();
			exit(-1);
		}

		//If everything succeded the state is set to active.
		setActive(true);
	}

	//Caps the framerate, 0 = uncapped.
	void Turbine::setMaxFPS(int limit) {
		fpsLimit = limit;
	}

	void Turbine::run() {
		while (active()) {
			handleEvents();
			update();
			draw();
		}
	}

	//Return true if passed in button is currently down; LMB = 1, MMB = 2, RMB = 3
	bool Turbine::mouseDown(int button) const {
		return (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(button));
	}

	//Return true if passed in key is currently down.
	bool Turbine::keyDown(std::string key) const {
		SDL_PumpEvents();
		const char* c = key.c_str();
		return (keyboard_state[SDL_GetScancodeFromName(c)]);
	}

	void Turbine::handleEvents() {
		updateMousePosition();
		SDL_Event current_event;
		while (SDL_PollEvent(&current_event)) { // Handle all queued up events this frame
			std::string key;
			switch (current_event.type) {
			case SDL_QUIT:
				setActive(false);
				break;
			case SDL_KEYDOWN:
				key = std::string(SDL_GetKeyName(current_event.key.keysym.sym));
				if (!current_event.key.repeat) {
					state.keyPressed(key);
				}
				break;
			case SDL_KEYUP:
				key = std::string(SDL_GetKeyName(current_event.key.keysym.sym));
				if (!current_event.key.repeat) {
					state.keyReleased(key);
				}
				break;
			case SDL_MOUSEBUTTONDOWN:
				state.mousePressed(current_event.button.button);
				break;
			case SDL_MOUSEBUTTONUP:
				state.mouseReleased(current_event.button.button);
				break;
			case SDL_MOUSEMOTION:
				// Todo
				break;
			default:
				break;
			}
		}
	}

	void Turbine::toggleCursor() {
		cursorVisible = !cursorVisible;
		SDL_ShowCursor(cursorVisible);
	}

	void Turbine::updateMousePosition() {
		int x, y;
		SDL_GetMouseState(&x, &y);

		mousePosition = Point(x, y);
	}
	
	Point Turbine::getMousePosition() const {
		return mousePosition;
	}

	double Turbine::getMouseX() const {
		return mousePosition.x;
	}
	
	double Turbine::getMouseY() const  {
		return mousePosition.y;
	}

	double Turbine::getWindowWidth() const {
		return width;
	}

	double Turbine::getWindowHeight() const {
		return height;
	}

	void Turbine::update() {
		updateDeltaTime();
		updateCurrentFPS(dt);
		state.update(dt);
		fade.update(dt);
		hibernate.update(dt);

		previousFrameTime = currentFrameTime;
		delay(dt);
	};

	void Turbine::updateDeltaTime() {
		currentFrameTime = static_cast<double>(SDL_GetTicks());
		dt = (currentFrameTime - previousFrameTime) / 1000;
	}

	void Turbine::updateCurrentFPS(double dt) {
		fpsTimer += dt;
		if (fpsTimer >= fpsRate) {
			fpsTimer = 0;
			fpsCurrent = 1.0 / dt;
		}
	}

	void Turbine::delay(double dt) {
		if (fpsLimit > 0) {
			double minimum_dt = 1000 / fpsLimit;
			double delay_amount = minimum_dt - dt;

			if (delay_amount > 0) {
				SDL_Delay(static_cast<Uint32>(delay_amount));
			} 
		}
	}

	int Turbine::getFPS() const{
		return static_cast<int>(fpsCurrent + 0.5);
	}

	void Turbine::draw() const {
		SDL_RenderClear(renderer);
		state.draw();
		fade.draw();
		SDL_RenderPresent(renderer);
	}

	bool Turbine::active() const { return isActive; }

	void Turbine::setActive(bool state) {
		isActive = state;
	}

	SDL_Renderer* Turbine::getRenderer() const {
		return renderer;
	}

	void Turbine::clean() {
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		Mix_CloseAudio();
		TTF_Quit();
		SDL_Quit();
	}

	Turbine turbine;
}