// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// ----------------------------------------------------------------

#pragma once
#include "Actor.h"

class Chikurin : public Actor
{
public:
	Chikurin(class Game* game);

private:

	void UpdateTexture();
	class SpriteComponent* mSprite;
};
