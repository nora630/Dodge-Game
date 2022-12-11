// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "Grid.h"
#include "Tile.h"
#include "Bamboo.h"


Grid::Grid(class Game* game)
	:Actor(game)
	, mNextBamboo(1.5f)
{
	// 8 rows, 8 columns
	mTiles.resize(NumRows);
	for (size_t i = 0; i < mTiles.size(); i++)
	{
		mTiles[i].resize(NumCols);
	}

	// Create tiles
	for (size_t i = 0; i < NumRows; i++)
	{
		for (size_t j = 0; j < NumCols; j++)
		{
			mTiles[i][j] = new Tile(GetGame());
			mTiles[i][j]->SetPosition(Vector2(StartX + TileSize / 2.0f + j * TileSize, StartY + i * TileSize));
		}
	}

}



void Grid::UpdateActor(float deltaTime)
{
	Actor::UpdateActor(deltaTime);

	
	mNextBamboo -= deltaTime;
	if (mNextBamboo <= 0.0f)
	{
		new Bamboo(GetGame());
		mNextBamboo += BambooTime;
	}

}


