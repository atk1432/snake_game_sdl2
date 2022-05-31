#ifndef _GAME_HPP
#define _GAME_HPP

#include <SDL2/SDL.h>
// #include <SDL2/SDL_ttf.h>
#include "Setting.hpp"


using namespace std;


SDL_Window *window;
SDL_Renderer *renderer;

class Game {

public:
	bool running = true;
	bool stop = false;

	Game(string title, int xpos, int ypos, int width=SCREEN_WIDTH, \
		 int height=SCREEN_HEIGHT) 
	{

		SDL_Init(SDL_INIT_VIDEO);
		TTF_Init();

		window = SDL_CreateWindow(title.c_str(), xpos, ypos, width, height, \
			SDL_WINDOW_SHOWN);

		renderer = SDL_CreateRenderer(window, -1, 0);

	}

	~Game() {

		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);

		TTF_Quit();
		SDL_Quit();

	}

	inline void clear() {
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		SDL_RenderClear(renderer);
	}

	inline void update() {
		SDL_RenderPresent(renderer);
	}

	inline void limit() {
		SDL_Delay(FPS);
	}

};


#endif