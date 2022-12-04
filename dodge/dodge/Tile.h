// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// ----------------------------------------------------------------

#pragma once
#include "Actor.h"

class Tile : public Actor
{
public:
	Tile(class Game* game);

private:

	void UpdateTexture();
	class SpriteComponent* mSprite;
};