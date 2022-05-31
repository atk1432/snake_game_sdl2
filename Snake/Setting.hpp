#ifndef _SETTING_HPP
#define _SETTING_HPP


#include <SDL2/SDL.h>

/* 
*	
*	Setting
*
*/

// Color
SDL_Color RED = { 255, 0, 0 } ;
SDL_Color WHITE = { 255, 255, 255 };
SDL_Color GREEN = { 0, 128, 0 };

// FPS
#define FPS 1000 / 12

// Window
#define SCREEN_WIDTH 480
#define SCREEN_HEIGHT 480

// Boardgame
#define ROWS_BOARD 20
#define COLUMNS_BOARD 20

// Color each object
#define SNAKE_COLOR GREEN
#define FOOD_COLOR RED


// --> Snake Object
#define LEFT 1
#define RIGHT 2
#define UP 4
#define DOWN 8

// --> Font
#define FONT "/usr/share/fonts/truetype/freefont/FreeSans.ttf"
#define FONT_SIZE 20
#define TEXT_COLOR WHITE



#endif // _SETTING_HPP

