// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// ----------------------------------------------------------------

// CircleComponent���Q�l�ɂ��A�����`�̏Փ˔���p�̃I�u�W�F�N�g���쐬

#pragma once
#include "Component.h"
#include "Math.h"
#include "CircleComponent.h"

class RectangleComponent : public Component
{
public:
	RectangleComponent(class Actor* owner);

	void SetMin(Vector2 min) { mMin = min; }
	void SetMax(Vector2 max) { mMax = max; }
	Vector2 GetMin() const { return mMin; }
	Vector2 GetMax() const { return mMax; }

private:
	Vector2 mMin;
	Vector2 mMax;
};

bool Intersect(const RectangleComponent& a, const CircleComponent& b);