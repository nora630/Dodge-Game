#pragma once
#include "Game.h"


// シーンの基底クラスを作成

class Scene
{
public:
	Scene(class Game* game);
	virtual ~Scene();
	virtual void Start();
	virtual void Update(float deltaTime);
	virtual void ProcessInput();

private:
	class Game* mGame;
};