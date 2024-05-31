#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include <iostream>
#include <vector>
#include <string>

// constants

// system core
const int FPS = 60;
const int FRAME_DELAY = 1000 / FPS;

const int SCREEN_WIDTH = 720;
const int SCREEN_HEIGHT = 720;

// program specific
const int GRID_WIDTH = 20;
const int GRID_HEIGHT = 20;

//const int SQUARE_SIZE = 20;
//const int START_X = (SCREEN_WIDTH - GRID_WIDTH * SQUARE_SIZE) / 2;
//const int START_Y = (SCREEN_HEIGHT - GRID_HEIGHT * SQUARE_SIZE) / 2;
//const int END_X = SCREEN_WIDTH - START_X;
//const int END_Y = SCREEN_HEIGHT - START_Y;

const int GRID_WIDTH_LENGTH = 480;
const int GRID_HEIGHT_LENGTH = 480;

const int START_X = (SCREEN_WIDTH - GRID_WIDTH_LENGTH) / 2;
const int START_Y = (SCREEN_HEIGHT - GRID_HEIGHT_LENGTH) / 2;
const int END_X = SCREEN_WIDTH - START_X;
const int END_Y = SCREEN_HEIGHT - START_Y;
const int SQUARE_SIZE = GRID_WIDTH_LENGTH / GRID_WIDTH;

class Game {
public:
	Game();
	~Game();

	bool init();
	void quit();

	
	void handleEvents();
	void update();
	void render();
	
	bool running() {
		return isRunningF;
	}
private:
	void generateGrid();
	void updateConway();
	bool isRunningF;
	SDL_Window* window;
	SDL_Renderer* renderer;
};