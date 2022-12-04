// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#pragma once
#include "Actor.h"

class Bamboo : public Actor
{
public:
	Bamboo(class Game* game);
	~Bamboo();
	void UpdateActor(float deltaTime) override;

private:
	float mRightSpeed;
	float mDownSpeed;
	int mBambooColum;
	int mBambooRow;

	// mBambooDirが、1の時はdown、2の時はup、3の時はright、4の時はleftに竹がやってくる
	int mBambooDir;
};
