// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// ----------------------------------------------------------------

// プレイヤー(パンダ)の動かし方と動かせる範囲を制限できるよう追加


#include "Player.h"
#include "AnimSpriteComponent.h"
#include "Game.h"
#include "Grid.h"

Player::Player(Game* game)
	:Actor(game)
	, mPlayerColum(3)
	, mPlayerRow(3)
	, mKeyInput(true)
	, mRightSpeed(0.0f)
	, mDownSpeed(0.0f)
	, mDirX(0)
	, mDirY(0)
{
	// Create an animated sprite component
	AnimSpriteComponent* asc = new AnimSpriteComponent(this);
	std::vector<SDL_Texture*> anims = {
		game->GetTexture("Assets/panda.png"),
	};
	asc->SetAnimTextures(anims);

	SetPosition(Vector2(StartX + TileSize / 2.0f + mPlayerColum * TileSize, StartY + mPlayerRow * TileSize));
	SetScale(0.1f);
}

void Player::UpdateActor(float deltaTime)
{
	Actor::UpdateActor(deltaTime);
	// Update position based on speeds and delta time

	
	if (mKeyInput == false)
	{
		Vector2 pos = GetPosition();
		pos.x += mRightSpeed * deltaTime;
		pos.y += mDownSpeed * deltaTime;
		
		if (mDirX == 1)
		{
			if (pos.x > StartX + TileSize / 2.0f + mPlayerColum * TileSize)
			{
				SetPosition(Vector2(StartX + TileSize / 2.0f + mPlayerColum * TileSize, StartY + mPlayerRow * TileSize));
				mRightSpeed = 0;
				mDirX = 0;
				mKeyInput = true;
			}
			else {
				SetPosition(pos);
			}
			
		} 
		if (mDirX == -1)
		{
			if (pos.x < StartX + TileSize / 2.0f + mPlayerColum * TileSize)
			{
				SetPosition(Vector2(StartX + TileSize / 2.0f + mPlayerColum * TileSize, StartY + mPlayerRow * TileSize));
				mRightSpeed = 0;
				mDirX = 0;
				mKeyInput = true;
			}
			else {
				SetPosition(pos);
			}
		}
		if (mDirY == 1)
		{
			if (pos.y > StartY + mPlayerRow * TileSize)
			{
				SetPosition(Vector2(StartX + TileSize / 2.0f + mPlayerColum * TileSize, StartY + mPlayerRow * TileSize));
				mDownSpeed = 0;
				mDirY = 0;
				mKeyInput = true;
			}
			else {
				SetPosition(pos);
			}
		}
		if (mDirY == -1)
		{
			if (pos.y < StartY + mPlayerRow * TileSize) 
			{
				SetPosition(Vector2(StartX + TileSize / 2.0f + mPlayerColum * TileSize, StartY + mPlayerRow * TileSize));
				mDownSpeed = 0;
				mDirY = 0;
				mKeyInput = true;
			}
			else {
				SetPosition(pos);
			}
		}
	}
}

void Player::ProcessKeyboard(const uint8_t* state)
{
	if (mKeyInput) {
		// right/left
		if (state[SDL_SCANCODE_D] && mPlayerColum < NumCols - 1)
		{
			++mPlayerColum;
			mRightSpeed = 512.0f;
			mDirX = 1;
			mKeyInput = false;
			return;
		}
		if (state[SDL_SCANCODE_A] && mPlayerColum > 0)
		{
			--mPlayerColum;
			mRightSpeed = -512.0f;
			mDirX = -1;
			mKeyInput = false;
			return;
		}
		// up/down
		if (state[SDL_SCANCODE_S] && mPlayerRow < NumRows - 1)
		{
			++mPlayerRow;
			mDownSpeed = 512.0f;
			mDirY = 1;
			mKeyInput = false;
			return;
		}
		if (state[SDL_SCANCODE_W] && mPlayerRow > 0)
		{
			--mPlayerRow;
			mDownSpeed = -512.0f;
			mDirY = -1;
			mKeyInput = false;
			return;
		}
	}
}
