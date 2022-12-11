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
#include <SDL_mixer.h>

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

	Uint32 GetTime() { return mTicksCount - mStartCount; }

	SDL_Texture* GetTexture(const std::string& fileName);
	std::vector<class Bamboo*>& GetBamboos() { return mBamboos; }

private:
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();
	void LoadGameScene();
	void UnloadGameScene();

	void LoadResultScene();
	void UnloadResultScene();

	void UpdateCollisionDetection();

	std::unordered_map<std::string, SDL_Texture*> mTextures;

	std::vector<class Actor*> mActors;
	std::vector<class Actor*> mPendingActors;

	std::vector<class SpriteComponent*> mSprites;

	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;
	class Font* mFont;
	//TTF_Font* mFont;
	//SDL_Texture* mTexture;
	Mix_Music* mMusic;

	Uint32 mTicksCount;
	Uint32 mStartCount;
	Uint32 mResultCount;
	bool mIsRunning;


	bool mUpdatingActors;

	class Player* mPlayer;
	class Grid* mGrid;
	std::vector<class Bamboo*> mBamboos;
	char mTime[50];
	bool mGameSceneActive = false;
};
