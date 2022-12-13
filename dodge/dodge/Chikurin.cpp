// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// ----------------------------------------------------------------

#include "Chikurin.h"
#include "SpriteComponent.h"
#include "Game.h"

Chikurin::Chikurin(class Game* game)
	:Actor(game)
	, mSprite(nullptr)
{
	mSprite = new SpriteComponent(this, 5);
	UpdateTexture();
}

void Chikurin::UpdateTexture()
{
	mSprite->SetTexture(GetGame()->GetTexture("Assets/chikurin.jpg"));
}
