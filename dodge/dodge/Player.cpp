// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// ----------------------------------------------------------------

// ÉvÉåÉCÉÑÅ[ÇÃìÆÇ©Çµï˚Ç∆ìÆÇ©ÇπÇÈîÕàÕÇêßå¿Ç≈Ç´ÇÈÇÊÇ§í«â¡


#include "Player.h"
#include "AnimSpriteComponent.h"
#include "Game.h"
#include "Grid.h"

Player::Player(Game* game)
	:Actor(game)
	, posX(3)
	, posY(3)
	, keyInput(true)
	, mRightSpeed(0.0f)
	, mDownSpeed(0.0f)
	, dirX(0)
	, dirY(0)
{
	// Create an animated sprite component
	AnimSpriteComponent* asc = new AnimSpriteComponent(this);
	std::vector<SDL_Texture*> anims = {
		game->GetTexture("Assets/panda.png"),
	};
	asc->SetAnimTextures(anims);

	SetPosition(Vector2(StartX + TileSize / 2.0f + posX * TileSize, StartY + posY * TileSize));
	SetScale(0.1f);
}

void Player::UpdateActor(float deltaTime)
{
	Actor::UpdateActor(deltaTime);
	// Update position based on speeds and delta time

	
	if (keyInput == false)
	{
		Vector2 pos = GetPosition();
		pos.x += mRightSpeed * deltaTime;
		pos.y += mDownSpeed * deltaTime;
		// Restrict position to left half of screen
		/*
		if (pos.x < 0.0f)
		{
			pos.x = 0.0f;
		}
		else if (pos.x > 1024.0f)
		{
			pos.x = 1024.0f;
		}
		if (pos.y < 0.0f)
		{
			pos.y = 0.0f;
		}
		else if (pos.y > 768.0f)
		{
			pos.y = 768.0f;
		}
		*/
		//SetPosition(pos);
		if (dirX == 1)
		{
			if (pos.x > StartX + TileSize / 2.0f + posX * TileSize)
			{
				SetPosition(Vector2(StartX + TileSize / 2.0f + posX * TileSize, StartY + posY * TileSize));
				mRightSpeed = 0;
				dirX = 0;
				keyInput = true;
			}
			else {
				SetPosition(pos);
			}
			
		} 
		if (dirX == -1)
		{
			if (pos.x < StartX + TileSize / 2.0f + posX * TileSize)
			{
				SetPosition(Vector2(StartX + TileSize / 2.0f + posX * TileSize, StartY + posY * TileSize));
				mRightSpeed = 0;
				dirX = 0;
				keyInput = true;
			}
			else {
				SetPosition(pos);
			}
		}
		if (dirY == 1)
		{
			if (pos.y > StartY + posY * TileSize)
			{
				SetPosition(Vector2(StartX + TileSize / 2.0f + posX * TileSize, StartY + posY * TileSize));
				mDownSpeed = 0;
				dirY = 0;
				keyInput = true;
			}
			else {
				SetPosition(pos);
			}
		}
		if (dirY == -1)
		{
			if (pos.y < StartY + posY * TileSize) 
			{
				SetPosition(Vector2(StartX + TileSize / 2.0f + posX * TileSize, StartY + posY * TileSize));
				mDownSpeed = 0;
				dirY = 0;
				keyInput = true;
			}
			else {
				SetPosition(pos);
			}
		}
	}
}

void Player::ProcessKeyboard(const uint8_t* state)
{
	if (keyInput) {
		// right/left
		if (state[SDL_SCANCODE_D] && posX < NumCols - 1)
		{
			++posX;
			mRightSpeed = 512.0f;
			dirX = 1;
			keyInput = false;
		}
		if (state[SDL_SCANCODE_A] && posX > 0)
		{
			--posX;
			mRightSpeed = -512.0f;
			dirX = -1;
			keyInput = false;
		}
		// up/down
		if (state[SDL_SCANCODE_S] && posY < NumRows - 1)
		{
			++posY;
			mDownSpeed = 512.0f;
			dirY = 1;
			keyInput = false;
		}
		if (state[SDL_SCANCODE_W] && posY > 0)
		{
			--posY;
			mDownSpeed = -512.0f;
			dirY = -1;
			keyInput = false;
		}
	}
}
