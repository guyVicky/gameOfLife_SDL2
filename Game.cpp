#include "Game.h"
#include "TextureManager.h"
#include "FontManager.h"

int grid[GRID_WIDTH][GRID_HEIGHT] = { 0 };
int curFrame = 1;
std::vector<std::pair<int, int>> directions = { {-1, -1}, { 0, -1 }, {1, -1}, {-1, 0}, {1, 0}, { -1, 1 }, {0, 1}, {1, 1} };

int mouseX, mouseY;
int x, y;

bool isStartedF = false;
bool isButtonDownF = false;
bool displayGridF = false;

SDL_Texture* messageText;
std::string title = "CELLULAR AUTOMATA";
const char* s = "assets/ABrilFatFace-Regular.ttf";

Game::Game() {

}
Game::~Game() {

}

bool Game::init()
{

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return false;
	}

	if (TTF_Init() < 0) {
		std::cout << TTF_GetError() << '\n';
	}


	window = SDL_CreateWindow("Pong", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == nullptr) {
		std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		return false;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr) {
		std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
		return false;
	}

	messageText = FontManager::LoadFont(s, renderer);
	generateGrid();

	return isRunningF = true;
}

void Game::handleEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type) {
	case SDL_QUIT:
		isRunningF = false;
		break;
	case SDL_KEYDOWN:
		switch (event.key.keysym.sym) {
		case SDLK_UP:
			std::cout << "Up Arrow pressed!" << std::endl;
			break;
		case SDLK_DOWN:
			std::cout << "Down Arrow pressed!" << std::endl;
			break;
		case SDLK_LEFT:
			std::cout << "Left Arrow pressed!" << std::endl;
			break;
		case SDLK_RIGHT:
			std::cout << "Right Arrow pressed!" << std::endl;
			break;
		case SDLK_SPACE:
			isStartedF = !isStartedF;
			break;
		case SDLK_RETURN:
			generateGrid();
			break;
		case SDLK_BACKSPACE:
			displayGridF = !displayGridF;


		default:
			break;
		}
	case SDL_MOUSEBUTTONDOWN:
		switch (event.button.button) {
		case SDL_BUTTON_LEFT:
			break;
		case SDL_BUTTON_RIGHT:
			std::cout << "Right mouse button released!" << std::endl;
			break;
		default:
			break;
		}
	case SDL_MOUSEBUTTONUP:
		switch (event.button.button) {
		case SDL_BUTTON_LEFT:
			break;
		}
	default:
		break;
	} 
	isButtonDownF = (bool) SDL_GetMouseState(&mouseX, &mouseY);
	
	if (isButtonDownF)
	{
		x = (mouseY - START_Y) / SQUARE_SIZE, y = (mouseX - START_X) / SQUARE_SIZE;
		if ((x >= 0 && x < GRID_WIDTH) && (y >= 0 && y < GRID_HEIGHT)) grid[x][y] = 1;
	}

}

void Game::update()
{


	if (curFrame % 10 == 0 && isStartedF) updateConway();

	if (curFrame == 60)
	{
		curFrame = 1;
	}
	
	curFrame++;
}

void Game::render()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	int text_width = (int)title.size() * 30;
	SDL_Rect Message_rect = { (SCREEN_WIDTH - text_width) / 2, 20, text_width, 72 };
	SDL_RenderCopy(renderer, messageText, NULL, &Message_rect);

	// display the underlying grid
	// if flag is set
	if (displayGridF){
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		for (int i = START_X; i <= END_X; i += SQUARE_SIZE)
			SDL_RenderDrawLine(renderer, i, START_Y, i, END_Y);
		for (int i = START_Y; i <= END_Y; i += SQUARE_SIZE)
			SDL_RenderDrawLine(renderer, START_X, i, END_X, i);
	}

	// logic to display the grid
	for (int i = 0; i < GRID_WIDTH; i++)
	{
		for (int j = 0; j < GRID_HEIGHT; j++)
		{
			if (grid[i][j]) {
				SDL_Rect rectb = {START_X + j * SQUARE_SIZE ,START_Y + i * SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE};
				SDL_RenderFillRect(renderer, &rectb);
			} 
			
		}
	}

	SDL_RenderPresent(renderer);
}

void Game::quit() {

	SDL_DestroyTexture(messageText);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}


void Game::generateGrid()
{
	std::string s;
	s += "...............";
	s += ".......###.....";
	s += ".......###.....";
	s += "...............";
	s += "......#....###.";
	s += "......#........";
	s += "......#........";
	s += "...............";
	s += "...#.#.........";
	s += "....##.........";
	s += "....#..........";
	s += "...............";
	s += ".......#.......";
	s += ".......#.......";
	s += ".......#.......";
	
	for (int i = 0; i < GRID_WIDTH; i++)
	{
		for (int j = 0; j < GRID_HEIGHT; j++)
		{
			srand(time(NULL) + i * (j + i));
			if (rand() % 6 == 3)
				grid[i][j] = 1;
			//if (s.at((i * GRID_WIDTH)+j) == '#')
			//	grid[i][j] = 1;

		}
	}
	std::cout << "Hello\n";
}

void Game::updateConway()
{
	int grid_old[GRID_WIDTH][GRID_HEIGHT] = { 0 };
	for (int i = 0; i < GRID_WIDTH; i++)
	{
		for (int j = 0; j < GRID_HEIGHT; j++)
		{
			grid_old[i][j] = grid[i][j];
			grid[i][j] = 0;
		}
	}
	for (int i = 0; i < GRID_WIDTH; i++)
	{
		for (int j = 0; j < GRID_HEIGHT; j++)
		{
			int cnt = 0;

			for (const auto& dir : directions) {
				int newR = i + dir.first;
				int newC = j + dir.second;

				if (newR >= 0 && newR < GRID_WIDTH && newC >= 0 && newC < GRID_HEIGHT)
				{
					if (grid_old[newR][newC] == 1)
						cnt++;
				}
			}

			if (grid_old[i][j] == 1) {
				if (cnt < 2 || cnt > 3) grid[i][j] = 0;
				else grid[i][j] = 1;
			}
			else if (cnt == 3)
				grid[i][j] = 1;
		}
	}
}