// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// ----------------------------------------------------------------

#include "Font.h"
#include <vector>
#include "Game.h"
#include "SDL.h"

Font::Font(class Game* game)
	:mGame(game)
{

}

Font::~Font()
{

}

bool Font::Load(const std::string& fileName)
{
	// We support these font sizes
	std::vector<int> fontSizes = {
		8, 9,
		10, 11, 12, 14, 16, 18,
		20, 22, 24, 26, 28,
		30, 32, 34, 36, 38,
		40, 42, 44, 46, 48,
		52, 56,
		60, 64, 68,
		72
	};

	for (auto& size : fontSizes)
	{
		TTF_Font* font = TTF_OpenFont(fileName.c_str(), size);
		if (font == nullptr)
		{
			SDL_Log("Failed to load font %s in size %d", fileName.c_str(), size);
			return false;
		}
		mFontData.emplace(size, font);
	}
	return true;
}

void Font::Unload()
{
	for (auto& font : mFontData)
	{
		TTF_CloseFont(font.second);
	}
}

 void Font::RenderText(const std::string& text,
	SDL_Rect* rect,const SDL_Color* color /*= Color::White*/,
	int pointSize /*= 24*/, SDL_Renderer* renderer)
{
	SDL_Texture* texture = nullptr;

	// Find the font data for this point size
	auto iter = mFontData.find(pointSize);
	if (iter != mFontData.end())
	{
		TTF_Font* font = iter->second;
		SDL_Surface* surf = TTF_RenderUTF8_Solid(font, text.c_str(), *color);
		if (surf != nullptr)
		{
			texture = SDL_CreateTextureFromSurface(renderer, surf);
			int w, h;
			w = rect->w;
			h = rect->h;
			SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);
			SDL_RenderCopy(renderer, texture, nullptr, rect);
		}
	}
	else
	{
		SDL_Log("Point size %d is unsupported", pointSize);
	}

	return;
}

