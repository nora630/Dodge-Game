// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// ----------------------------------------------------------------


#pragma once

#include "SDL.h"
#include <vector>
#include <string>
#include <unordered_map>
#include "Font.h"

class Game
{
public:
	Game();
	bool Initialize();
	void RunLoop();
	void Shutdown();

	void AddActor(class Actor* actor);
	void RemoveActor(class Actor* actor);

	void AddSprite(class SpriteComponent* sprite);
	void RemoveSprite(class SpriteComponent* sprite);

	SDL_Texture* GetTexture(const std::string& fileName);
	std::vector<class Bamboo*>& GetBamboos() { return mBamboos; }

private:
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();
	void LoadData();
	void UnloadData();

	std::unordered_map<std::string, SDL_Texture*> mTextures;

	std::vector<class Actor*> mActors;
	std::vector<class Actor*> mPendingActors;

	std::vector<class SpriteComponent*> mSprites;

	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;
	//class Font* mFont;
	TTF_Font* mFont;
	SDL_Texture* mTexture;

	Uint32 mTicksCount;
	bool mIsRunning;


	bool mUpdatingActors;

	class Player* mPlayer;
	class Grid* mGrid;
	std::vector<class Bamboo*> mBamboos;
};
