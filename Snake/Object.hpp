#ifndef _OBJECT_HPP
#define _OBJECT_HPP


#include <SDL2/SDL.h>
// #include <SDL2/SDL_ttf.h>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <string>
#include "Game.hpp"
#include "BoardGame.hpp"
#include "Setting.hpp"

using namespace std;


// Globally


class Object {

protected:
	int __x, __y;
	SDL_Color *__color;

public:
	void render() {
		board.render(__x, __y, __color);
	}

};


class Text {

private:
	SDL_Texture *__texture;
	SDL_Rect __drect;
	string __text;

	void __initText(string text) {
		// cout << SDL_GetError() << endl;
		TTF_Font *font = TTF_OpenFont(FONT, FONT_SIZE);
		// cout << font << endl;
		
		SDL_Surface *surface = TTF_RenderText_Solid(font, text.c_str(), TEXT_COLOR);

		__texture = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_FreeSurface(surface);
		
	}

public:
	Text(string text, int x, int y, int w, int h) {
		__initText(text.c_str());
		__text = text;
		// TTF_CloseFont(font);
		
		__drect.x = x;
		__drect.y = y;
		__drect.w = w;
		__drect.h = h;
	}

	~Text() {
		
		SDL_DestroyTexture(__texture);
	}

	void render(string text="") {
		if (!(text == "" || text == __text)) {
			__initText(text);
		}

		SDL_RenderCopy(renderer, __texture, NULL, &__drect);
		// cout << __texture << endl;
	}

};



class Food : public Object {

public:
	int x, y;

	Food() {
		__color = &FOOD_COLOR;
		getRandom();
	}

	void getRandom() {
		srand(time(0));

		__x = x = 0 + (rand() % COLUMNS_BOARD);
		__y = y = 0 + (rand() % ROWS_BOARD);
	}
};


class PointSnake : public Object {


public:
	PointSnake(int x, int y) {
		__x = x;
		__y = y;
		__color = &SNAKE_COLOR;
	}	

	inline int x() {
		return __x;
	}

	inline int y() {
		return __y;
	}

};


class Snake {

private:
	vector<PointSnake> __snake;
	int __x, __y;
	int __length = 3;
	int __score = 0;
	bool __gameover = false;

	// Text;
	Text __gameoverText = Text("Game over", \
								(SCREEN_WIDTH / 2) - (200 / 2), \
								(SCREEN_HEIGHT / 2) - (50 / 2), \
							 	200, 50);

	Text __scoreText = Text("Score", 5, 5, 70, 22);

	// Function
	void __add() {
		__snake.insert(__snake.begin(), *(__snake.begin()));
	}

public:
	int direction = RIGHT;

	Snake(int x, int y) {
		__x = x;
		__y = y;

		for (int i = 2; i >= 0; i--) {
			PointSnake point(x - i, y);
			__snake.push_back(point);
			// cout << "Initial" << endl;
		}
	}


	void move() {
		switch (direction) {
			case UP:
				__y--;
				break;
			case DOWN:
				__y++;
				break;
			case LEFT:
				__x--;
				break;
			case RIGHT:
				__x++;
				break;
		}

		__snake.erase(__snake.begin());
		__snake.push_back(PointSnake(__x, __y))	;	
	}

	void render() {

		for (PointSnake &point : __snake) {
			point.render();
		}

		string score = "Score: " + to_string(__score);
		__scoreText.render(score);

		if (__gameover)
			__gameoverText.render();


	}


	bool isGameOver() {
		bool gameover = false;

		if (__x >= COLUMNS_BOARD || __x < 0)
			gameover = true;

		if (__y >= ROWS_BOARD || __y < 0)
			gameover = true;

		for (int i = 0; i < __snake.size() - 1; i++) 
		{
			if (__snake.at(i).x() == __x && __snake.at(i).y() == __y)
				gameover = true;
		}

		return gameover;
	}

	void doWhenEat(Food *food) {

		if (__x == food->x && __y == food->y)  {
			food->getRandom();
			__score++;
			__add();
		}
	}

	void raiseGameOver() {
		__gameover = true;
	}	

};


#endif // 
