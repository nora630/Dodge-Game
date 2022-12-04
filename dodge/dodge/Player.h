// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// ----------------------------------------------------------------

#pragma once
#include "Actor.h"
#include "Grid.h"

class Player : public Actor
{
public:
	Player(class Game* game);
	void UpdateActor(float deltaTime) override;
	void ProcessKeyboard(const uint8_t* state);

private:
	// �v���C���[���Ֆʂ̉��Ԗڂ̍s�A��ɂ���̂��ێ�����
	size_t mPlayerColum;
	size_t mPlayerRow;

	// ���͎�t�̃t���O�Atrue�Ȃ�΃L�[���͂��󂯎��
	bool mKeyInput;

	float mRightSpeed;
	float mDownSpeed;

	// x,y�����ꂼ��̕����x�N�g���A1�Ȃ�ΐ��A-1�Ȃ�Ε��̕���
	int mDirX;
	int mDirY;

};
