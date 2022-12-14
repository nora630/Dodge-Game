// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// ----------------------------------------------------------------

#include "Gameover.h"
#include "SpriteComponent.h"
#include "Game.h"

Gameover::Gameover(class Game* game)
	:Actor(game)
	, mSprite(nullptr)
{
	mSprite = new SpriteComponent(this, 10);
	UpdateTexture();
}

void Gameover::UpdateTexture()
{
	mSprite->SetTexture(GetGame()->GetTexture("Assets/gameover.jpg"));
}
