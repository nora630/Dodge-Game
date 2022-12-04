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
	/*
	const float GetStartX() const { return StartX; };
	const float GetStartY() const { return StartY; };
	const size_t GetNumTiles() const { return NumTiles; };
	const size_t GetNumRows() const { return NumRows; };
	const float GetTileSize() const { return TileSize; };
	*/

private:
	// 2D vector of tiles in grid
	std::vector<std::vector<class Tile*>> mTiles;

	
};

