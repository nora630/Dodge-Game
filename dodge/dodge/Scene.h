#pragma once
#include "Game.h"


// �V�[���̊��N���X���쐬

class Scene
{
public:
	Scene(class Game* game);
	virtual ~Scene();
	virtual void Start();
	virtual void Update(float deltaTime);
	virtual void ProcessInput(const Uint8* state);

private:
	class Game* mGame;
};