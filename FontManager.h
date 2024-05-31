#pragma once
#include "Game.h"

class FontManager
{
public:
	static SDL_Texture* LoadFont(const char* filename, SDL_Renderer* ren);
};

