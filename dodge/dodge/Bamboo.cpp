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
#include "CircleComponent.h"
#include "RectangleComponent.h"

Bamboo::Bamboo(class Game* game) 
	:Actor(game)
	, mRightSpeed(0.0f)
	,mDownSpeed(0.0f)
	,mBambooColum(0)
	,mBambooRow(0)
	,mBambooDir(0)
{
	game->GetBamboos().emplace_back(this);

	//mCircle = new CircleComponent(this);
	//mCircle->SetRadius(80.0f);

	
	SpriteComponent* sc = new SpriteComponent(this);
	SetScale(0.4f);

	


	//bamboo初期リスポーン地点
	mBambooDir = Random::GetIntRange(1, 4);

	switch (mBambooDir)
	{
	case 1:
		sc->SetTexture(game->GetTexture("Assets/bambooDown.png"));
		while (mBambooColum == (Random::GetIntRange(0, 7)+1)%8 || mBambooColum == (Random::GetIntRange(0, 7)-1) % 8);
		mBambooColum = Random::GetIntRange(0, 7);
		SetPosition(Vector2(StartX + TileSize / 2.0f + mBambooColum * TileSize, 0));
		if (GetGame()->GetTime() > 20000)
		{
			mDownSpeed = 300.0f;
		}
		else {
			mDownSpeed = 500.0f;
		}
			
		break;

	case 2:
		sc->SetTexture(game->GetTexture("Assets/bambooUp.png"));
		while (mBambooColum == (Random::GetIntRange(0, 7) + 1) % 8 || mBambooColum == (Random::GetIntRange(0, 7) - 1) % 8);
		mBambooColum = Random::GetIntRange(0, 7);
		SetPosition(Vector2(StartX + TileSize / 2.0f + mBambooColum * TileSize, 768));
		if (GetGame()->GetTime() > 20000)
		{
			mDownSpeed = -300.0f;
		}
		else {
			mDownSpeed = -500.0f;
		}
		break;

	case 3:
		sc->SetTexture(game->GetTexture("Assets/bambooRight.png"));
		while (mBambooRow == (Random::GetIntRange(0, 7) + 1) % 8 || mBambooRow == (Random::GetIntRange(0, 7) - 1) % 8);
		mBambooColum = Random::GetIntRange(0, 7);
		mBambooRow = Random::GetIntRange(0, 7);
		SetPosition(Vector2(0, StartY + mBambooRow * TileSize));
		if (GetGame()->GetTime() > 20000)
		{
			mRightSpeed = 300.0f;
		}
		else {
			mRightSpeed = 500.0f;
		}
		break;

	case 4:
		sc->SetTexture(game->GetTexture("Assets/bambooleft.png"));
		while (mBambooRow == (Random::GetIntRange(0, 7) + 1) % 8 || mBambooRow == (Random::GetIntRange(0, 7) - 1) % 8);
		mBambooRow = Random::GetIntRange(0, 7);
		SetPosition(Vector2(1024, StartY + mBambooRow * TileSize));
		if (GetGame()->GetTime() > 20000)
		{
			mRightSpeed = -300.0f;
		}
		else {
			mRightSpeed = -500.0f;
		}
		break;
	default:
		break;
	}

	mRectangle = new RectangleComponent(this);
	mRectangle->SetTexHeight(sc->GetTexHeight()-80);
	mRectangle->SetTexWidth(sc->GetTexWidth()-80);
	mRectangle->SetMin(Vector2(GetPosition().x - mRectangle->GetTexWidth() * GetScale() / 2, GetPosition().y - mRectangle->GetTexHeight() * GetScale() / 2));
	mRectangle->SetMax(Vector2(GetPosition().x + mRectangle->GetTexWidth() * GetScale() / 2, GetPosition().y + mRectangle->GetTexHeight() * GetScale() / 2));
}

Bamboo::~Bamboo()
{
	auto iter = std::find(GetGame()->GetBamboos().begin(),
		GetGame()->GetBamboos().end(),
		this);
	GetGame()->GetBamboos().erase(iter);
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

	mRectangle->SetMin(Vector2(GetPosition().x - mRectangle->GetTexWidth() * GetScale() / 2, GetPosition().y - mRectangle->GetTexHeight() * GetScale() / 2));
	mRectangle->SetMax(Vector2(GetPosition().x + mRectangle->GetTexWidth() * GetScale() / 2, GetPosition().y + mRectangle->GetTexHeight() * GetScale() / 2));
}

