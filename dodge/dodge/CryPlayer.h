// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// ----------------------------------------------------------------

#pragma once
#include "Actor.h"
#include "Grid.h"

class CryPlayer : public Actor
{
public:
	CryPlayer(class Game* game);
	void UpdateActor(float deltaTime) override;

};


