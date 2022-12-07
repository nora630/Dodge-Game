// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// ----------------------------------------------------------------

// CircleComponentを参考にし、長方形の衝突判定用のオブジェクトを作成

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
	int GetTexHeight() const { return mTexHeight; }
	int GetTexWidth() const { return mTexWidth; }
	void SetTexHeight(int texHeight) { mTexHeight = texHeight; }
	void SetTexWidth(int texWidth) { mTexWidth = texWidth; }

private:
	Vector2 mMin;
	Vector2 mMax;
	int mTexWidth;
	int mTexHeight;
};

bool Intersect(const RectangleComponent& a, const CircleComponent& b);