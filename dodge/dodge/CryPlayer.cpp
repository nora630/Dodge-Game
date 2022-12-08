// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// ----------------------------------------------------------------

// �|�ɓ��������狃���p���_

#include "Game.h"
#include "CryPlayer.h"
#include "SpriteComponent.h"

CryPlayer::CryPlayer(Game* game)
	:Actor(game)

{
	SpriteComponent* sc = new SpriteComponent(this);
	SetScale(0.1f);
	sc->SetTexture(GetGame()->GetTexture("Assets/pandaCry.png"));

}

void CryPlayer::UpdateActor(float deltatime)
{

}