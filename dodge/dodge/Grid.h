// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#pragma once
#include "Actor.h"
#include <vector>


static const size_t NumRows = 8;
static const size_t NumCols = 8;
static const size_t NumTiles = NumRows * NumCols;


// Start x position of top left corner
static const float StartX = 256.0f;
// Start y position of top left corner
static const float StartY = 192.0f;
// Width/height of each tile
static const float TileSize = 64.0f;

class Grid : public Actor
{
public:
	Grid(class Game* game);
	void UpdateActor(float deltaTime) override;

private:
	// 2D vector of tiles in grid
	std::vector<std::vector<class Tile*>> mTiles;
	
	// 竹が次にリスポーンする時間
	float mNextBamboo;

	// 竹のリスポーン間隔
	float mBambooTime;
	
};

