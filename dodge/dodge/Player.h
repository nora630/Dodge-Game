// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// ----------------------------------------------------------------

#pragma once
#include "Actor.h"
#include "Grid.h"

class Player : public Actor
{
public:
	Player(class Game* game);
	void UpdateActor(float deltaTime) override;
	void ProcessKeyboard(const uint8_t* state);

private:
	// プレイヤーが盤面の何番目の行、列にいるのか保持する
	size_t playerColum;
	size_t playerRow;
	bool keyInput;
	float mRightSpeed;
	float mDownSpeed;
	int dirX;
	int dirY;

};
