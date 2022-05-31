#include <iostream>
#include <string>
#include <SDL2/SDL_ttf.h>
#include "Game.hpp"
#include "Object.hpp"


using namespace std;

int main(int argc, char const *argv[])
{

	TTF_Init();

	Game game("Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);

	Snake *snake = new Snake(12, 12);
	Food *food = new Food();

	// Event
	SDL_Event event;

	// Direction of snake
	int direction;

	while (game.running) {

		game.clear();

		while (SDL_PollEvent(&event)) {
			switch (event.type) {

				case SDL_QUIT:
					game.running = false;
					break;

				case SDL_KEYDOWN:
					direction = snake->direction;

					switch (event.key.keysym.sym) {

						case SDLK_LEFT:
							if ( !(direction & (LEFT | RIGHT)) )
								snake->direction = LEFT;
							break;

						case SDLK_RIGHT:
							if ( !(direction & (LEFT | RIGHT)) )
								snake->direction = RIGHT;
							break;

						case SDLK_UP:
							if ( !(direction & (UP | DOWN)) )
								snake->direction = UP;
							break;

						case SDLK_DOWN:
							if ( !(direction & (UP | DOWN)) )
								snake->direction = DOWN;
							break;

						case SDLK_SPACE:
							if (game.stop) {								
								delete snake;
								delete food;

								snake = new Snake(12, 12);
								food = new Food();

								game.stop = false;
							}
					}

					break;
			}
		}

		if (!game.stop) {

			snake->move();
			snake->doWhenEat(food);

			if (snake->isGameOver()) {
				snake->raiseGameOver();
				game.stop = true;
			}
		}

		food->render();
		snake->render();

		game.update();

		game.limit();
	}

	delete food;
	delete snake;

	TTF_Quit();

	return 0;
}