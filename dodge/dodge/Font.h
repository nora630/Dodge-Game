// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// ----------------------------------------------------------------

#pragma once
#include <string>
#include <unordered_map>
#include <SDL_ttf.h>
#include "Math.h"

class Font
{
public:
	Font(class Game* game);
	~Font();

	// Load/unload from a file
	bool Load(const std::string& fileName);
	void Unload();

	void RenderText(const std::string& text,
		SDL_Rect* rect, const SDL_Color* color /*= Color::White*/,
		int pointSize /*= 24*/, SDL_Renderer* renderer);

private:
	// Map of point sizes to font data
	std::unordered_map<int, TTF_Font*> mFontData;
	class Game* mGame;
};
