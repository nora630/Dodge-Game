// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// ----------------------------------------------------------------


#include "Game.h"
#include "SDL_image.h"
#include "Actor.h"
#include "SpriteComponent.h"
#include "Player.h"
#include "CryPlayer.h"
#include "Grid.h"
#include "Bamboo.h"
#include "SDL_ttf.h"
#include "SDL_rect.h"
#include "RectangleComponent.h"
#include "SDL_mixer.h"
#include "chikurin.h"

Game::Game()
	:mWindow(nullptr)
	, mRenderer(nullptr)
	, mTicksCount(0)
	, mIsRunning(true)
{

}

bool Game::Initialize()
{
	//SDLの初期化
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
	{
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}

	mWindow = SDL_CreateWindow("Dodge!!", 100, 100, 1024, 768, 0);
	if (!mWindow)
	{
		SDL_Log("Failed to create window: %s", SDL_GetError());
		return false;
	}

	mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!mRenderer)
	{
		SDL_Log("Failed to create renderer: %s", SDL_GetError());
		return false;
	}

	if (IMG_Init(IMG_INIT_PNG) == 0)
	{
		SDL_Log("Unable to initialize SDL_image: %s", SDL_GetError());
		return false;
	}

	if (TTF_Init() != 0)
	{
		SDL_Log("Failed to initialize SDL_ttf");
		return false;
	}

	/*
	if (SDL_Init(SDL_INIT_AUDIO) < 0) {
		printf("Mixer could not initialize! Mixer_Error: %s", Mix_GetError());
		return false;
	}
	*/
	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1) {
		printf("Mix_OpenAudio could not initialize! Mixer_Error: %s", Mix_GetError());
		return false;
	}
	
	mMusic = Mix_LoadMUS("Assets/bgm.ogg");
	if (mMusic == NULL) {
		return false;
	}
	if (Mix_PlayMusic(mMusic, -1) == -1) {
		return false;
	}

	Mix_VolumeMusic(1);
	
	/*
	mFont = TTF_OpenFont("Corporate-Logo-Rounded-Bold-ver3.otf", 24);
	if (mFont == nullptr)
	{
		SDL_Log("Failed to load font");
		return false;
	}
	*/
	mFont = new Font(this);
	mFont->Load("Corporate-Logo-Rounded-Bold-ver3.otf");
	
	//mFont->Load("Oranienbaum.ttf");

	mTicksCount = SDL_GetTicks();
	LoadGameScene();
	Mix_PlayingMusic();

	return true;

}

void Game::RunLoop()
{
	while (mIsRunning)
	{
		ProcessInput();
		UpdateGame();
		GenerateOutput();
	}
}

void Game::ProcessInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			mIsRunning = false;
			break;
		case SDL_KEYUP:
			return;
		}
	}

	//キーボード状態取得
	const Uint8* state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_ESCAPE])
	{
		mIsRunning = false;
	}

	if (mGameSceneActive)
	{
		mPlayer->ProcessKeyboard(state);
	}
	else {
		if (state[SDL_SCANCODE_RETURN] || state[SDL_SCANCODE_E])
		{
			LoadGameScene();
			Mix_RewindMusic();
			Mix_ResumeMusic();
		}
	}

}

void Game::UpdateGame()
{
	// Compute delta time
	// Wait until 16ms has elapsed since last frame
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16));
	//while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 60));

	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
	if (deltaTime > 0.05f)
	{
		deltaTime = 0.05f;
	}
	mTicksCount = SDL_GetTicks();

	// Update all actors
	mUpdatingActors = true;
	for (auto actor : mActors)
	{
		actor->Update(deltaTime);
	}
	mUpdatingActors = false;

	// Move any pending actors to mActors
	for (auto pending : mPendingActors)
	{
		mActors.emplace_back(pending);
	}
	mPendingActors.clear();

	// Add any dead actors to a temp vector
	std::vector<Actor*> deadActors;
	for (auto actor : mActors)
	{
		if (actor->GetState() == Actor::EDead)
		{
			deadActors.emplace_back(actor);
		}
	}

	// Delete dead actors (which removes them from mActors)
	for (auto actor : deadActors)
	{
		delete actor;
	}

	if(mPlayer->GetState() == Actor::EActive) UpdateCollisionDetection();

}

void Game::GenerateOutput()
{
	SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);
	SDL_RenderClear(mRenderer);

	// Draw all sprite components
	
	for (auto sprite : mSprites)
	{
		sprite->Draw(mRenderer);
	} 
	//SDL_RenderPresent(mRenderer);

	/*
	auto string_color = SDL_Color();
	string_color.r = 0;
	string_color.g = 0;
	string_color.b = 255;
	string_color.a = 255;

	auto string_surface = TTF_RenderUTF8_Solid(mFont, u8"こんにちは！！", string_color);
	mTexture = SDL_CreateTextureFromSurface(mRenderer, string_surface);
	
	int w, h;
	w = 30;
	h = 20;
	SDL_QueryTexture(mTexture, nullptr, nullptr, &w, &h);

	SDL_Rect txtRect = { 0,0,w,h };
	SDL_Rect pasteRect = { 800,0,w,h };

	SDL_RenderCopy(mRenderer, mTexture, nullptr, &pasteRect);
	//windowにレンダリングする 
	*/
	

	if (mGameSceneActive) 
	{
		auto string_color = SDL_Color();
		string_color.r = 0;
		string_color.g = 0;
		string_color.b = 0;
		string_color.a = 255;

		SDL_Rect pasteRect = { 800,0,100,50 };

		//mTime = std::to_string(mTicksCount / 1000 / 60) + " :" + std::to_string((mTicksCount / 1000) % 60);

		sprintf_s(mTime, sizeof(mTime), "%02d : %02d", (mTicksCount-mStartCount) / 1000 / 60, ((mTicksCount - mStartCount) / 1000) % 60);
		mFont->RenderText(mTime, &pasteRect, &string_color,
			72, mRenderer);
	}
	else {
		auto string_color = SDL_Color();
		string_color.r = 0;
		string_color.g = 0;
		string_color.b = 0;
		string_color.a = 255;
		SDL_Rect pasteRect = { 300,150,400,400 };

		//mTime = std::to_string(mTicksCount / 1000 / 60) + " :" + std::to_string((mTicksCount / 1000) % 60);

		sprintf_s(mTime, sizeof(mTime), "Result\n %02d : %02d", mResultCount / 1000 / 60, (mResultCount / 1000) % 60);
		mFont->RenderText(mTime, &pasteRect, &string_color,
			72, mRenderer);
	}
	

	SDL_RenderPresent(mRenderer);


}

void Game::LoadGameScene()
{	
	mGrid = new Grid(this);

	mPlayer = new Player(this);

	//mBamboo = new Bamboo(this);

	mChikurin = new Chikurin(this);

	mGameSceneActive = true;

	mStartCount = mTicksCount;

}

void Game::UnloadGameScene()
{
	// Delete actors
	// Because ~Actor calls RemoveActor, have to use a different style loop
	while (!mActors.empty())
	{
		delete mActors.back();
	}

	// Destroy textures
	for (auto i : mTextures)
	{
		SDL_DestroyTexture(i.second);
	}
	mTextures.clear();

	mGameSceneActive = false;

	Mix_PauseMusic();
	//Mix_RewindMusic();
}

void Game::LoadResultScene()
{

}

void Game::UnloadResultScene()
{
	
}

void Game::Shutdown()
{
	UnloadGameScene();
	UnloadResultScene();
	mFont->Unload();
	Mix_FreeMusic(mMusic);
	Mix_CloseAudio();
	TTF_Quit();
	IMG_Quit();
	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
}

SDL_Texture* Game::GetTexture(const std::string& fileName)
{
	SDL_Texture* tex = nullptr;
	// Is the texture already in the map?
	auto iter = mTextures.find(fileName);
	if (iter != mTextures.end())
	{
		tex = iter->second;
	}
	else
	{
		// Load from file
		SDL_Surface* surf = IMG_Load(fileName.c_str());
		if (!surf)
		{
			SDL_Log("Failed to load texture file %s", fileName.c_str());
			return nullptr;
		}

		// Create texture from surface
		tex = SDL_CreateTextureFromSurface(mRenderer, surf);
		SDL_FreeSurface(surf);
		if (!tex)
		{
			SDL_Log("Failed to convert surface to texture for %s", fileName.c_str());
			return nullptr;
		}

		mTextures.emplace(fileName.c_str(), tex);
	}
	return tex;
}

void Game::AddActor(Actor* actor)
{
	// If we're updating actors, need to add to pending
	if (mUpdatingActors)
	{
		mPendingActors.emplace_back(actor);
	}
	else
	{
		mActors.emplace_back(actor);
	}
}

void Game::RemoveActor(Actor* actor)
{
	// Is it in pending actors?
	auto iter = std::find(mPendingActors.begin(), mPendingActors.end(), actor);
	if (iter != mPendingActors.end())
	{
		// Swap to end of vector and pop off (avoid erase copies)
		std::iter_swap(iter, mPendingActors.end() - 1);
		mPendingActors.pop_back();
	}

	// Is it in actors?
	iter = std::find(mActors.begin(), mActors.end(), actor);
	if (iter != mActors.end())
	{
		// Swap to end of vector and pop off (avoid erase copies)
		std::iter_swap(iter, mActors.end() - 1);
		mActors.pop_back();
	}
}

void Game::AddSprite(SpriteComponent* sprite)
{
	// Find the insertion point in the sorted vector
	// (The first element with a higher draw order than me)
	int myDrawOrder = sprite->GetDrawOrder();
	auto iter = mSprites.begin();
	for (;
		iter != mSprites.end();
		++iter)
	{
		if (myDrawOrder < (*iter)->GetDrawOrder())
		{
			break;
		}
	}

	// Inserts element before position of iterator
	mSprites.insert(iter, sprite);
}

void Game::RemoveSprite(SpriteComponent* sprite)
{
	// (We can't swap because it ruins ordering)
	auto iter = std::find(mSprites.begin(), mSprites.end(), sprite);
	mSprites.erase(iter);
}

void Game::UpdateCollisionDetection()
{
	for (Bamboo* b : mBamboos)
	{
		if (Intersect(*(b->GetRectangle()), *(mPlayer->GetCircle())))
		{
			CryPlayer* cryPlayer = new CryPlayer(this);
			cryPlayer->SetPosition(mPlayer->GetPosition());
			mPlayer->SetState(mPlayer->EDead);
			mResultCount = mTicksCount - mStartCount;
			//GetGame()->Shutdown();
			UnloadGameScene();
			break;
		}
	}
}