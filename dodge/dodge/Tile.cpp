// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// ----------------------------------------------------------------

#include "Tile.h"
#include "SpriteComponent.h"
#include "Game.h"

Tile::Tile(class Game* game)
	:Actor(game)
	, mSprite(nullptr)
{
	mSprite = new SpriteComponent(this, 10);
	UpdateTexture();
}

void Tile::UpdateTexture()
{
	mSprite->SetTexture(GetGame()->GetTexture("Assets/TileBrownWaku.png"));
}
