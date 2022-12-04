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
	size_t mPlayerColum;
	size_t mPlayerRow;

	// 入力受付のフラグ、trueならばキー入力を受け取る
	bool mKeyInput;

	float mRightSpeed;
	float mDownSpeed;

	// x,y軸それぞれの方向ベクトル、1ならば正、-1ならば負の方向
	int mDirX;
	int mDirY;

};
