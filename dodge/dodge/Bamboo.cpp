// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// ----------------------------------------------------------------

#include "Bamboo.h"
#include "Game.h"
#include "SpriteComponent.h"
#include "Grid.h"
#include "Random.h"

Bamboo::Bamboo(class Game* game) 
	:Actor(game)
	, mRightSpeed(0.0f)
	,mDownSpeed(0.0f)
	,mBambooColum(0)
	,mBambooRow(0)
	,mBambooDir(0)
{
	SpriteComponent* sc = new SpriteComponent(this);
	SetScale(0.4f);


	//bamboo初期リスポーン地点

	mBambooDir = Random::GetIntRange(1, 4);

	switch (mBambooDir)
	{
	case 1:
		sc->SetTexture(game->GetTexture("Assets/bambooDown.png"));
		mBambooColum = Random::GetIntRange(0, 7);
		SetPosition(Vector2(StartX + TileSize / 2.0f + mBambooColum * TileSize, 0));
		mDownSpeed = 300.0f;
		break;

	case 2:
		sc->SetTexture(game->GetTexture("Assets/bambooUp.png"));
		mBambooColum = Random::GetIntRange(0, 7);
		SetPosition(Vector2(StartX + TileSize / 2.0f + mBambooColum * TileSize, 768));
		mDownSpeed = -300.0f;
		break;

	case 3:
		sc->SetTexture(game->GetTexture("Assets/bambooRight.png"));
		mBambooRow = Random::GetIntRange(0, 7);
		SetPosition(Vector2(0, StartY + mBambooRow * TileSize));
		mRightSpeed = 300.0f;
		break;

	case 4:
		sc->SetTexture(game->GetTexture("Assets/bambooleft.png"));
		mBambooRow = Random::GetIntRange(0, 7);
		SetPosition(Vector2(1024, StartY + mBambooRow * TileSize));
		mRightSpeed = -300.0f;
		break;
	default:
		break;
	}
}

Bamboo::~Bamboo()
{

}

void Bamboo::UpdateActor(float deltaTime)
{
	Actor::UpdateActor(deltaTime);

	Vector2 pos = GetPosition();
	pos.x += mRightSpeed * deltaTime;
	pos.y += mDownSpeed * deltaTime;

	SetPosition(pos);

	if (pos.x < 0.0f || pos.x > 1024.0f || pos.y < 0.0f || pos.y > 768.0f)
	{
		SetState(EDead);
	}

}