#include "FontManager.h"


SDL_Texture* FontManager::LoadFont(const char* filename, SDL_Renderer* ren) {

	SDL_Color White = { 255, 255, 255 };
	TTF_Font* serif = TTF_OpenFont("assets/AbrilFatface-Regular.ttf", 40);
	SDL_Surface* tempSurface = TTF_RenderText_Solid(serif, "CELLULAR AUTOMATA", White);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(ren, tempSurface);
	return tex;
}