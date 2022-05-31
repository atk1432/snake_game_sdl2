#ifndef _BOARD_GAME_HPP
#define _BOARD_GAME_HPP

#include "Game.hpp"
#include <SDL2/SDL.h>
#include "Setting.hpp"

class BoardGame {

private:
	int __rows, __columns, __wCell, __hCell;


public:
	BoardGame(int rows, int columns) {
		__rows = rows;
		__columns = columns;
		__wCell = SCREEN_WIDTH / columns;
		__hCell = SCREEN_HEIGHT / rows;
	}

	SDL_Rect convert(int x, int y) {
		SDL_Rect rect;
		rect.x = x * __wCell;
		rect.y = y * __hCell;
		rect.w = __wCell;
		rect.h = __hCell;
		return rect;
	}

	void render(int x, int y, SDL_Color *color) {
		SDL_Rect rect = convert(x, y);

		SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, color->a);
		SDL_RenderFillRect(renderer, &rect);
	}

};


BoardGame board(ROWS_BOARD, COLUMNS_BOARD);


#endif