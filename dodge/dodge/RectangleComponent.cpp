// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// ----------------------------------------------------------------

#include "RectangleComponent.h"
#include "Actor.h"
#include "Math.h"

RectangleComponent::RectangleComponent(class Actor* owner)
	:Component(owner)
{

}

bool Intersect(const RectangleComponent& a, const CircleComponent& b)
{
	float dx = Math::Max(a.GetMin().x - b.GetCenter().x, 0.0f);
	dx = Math::Max(dx, b.GetCenter().x - a.GetMax().x);

	float dy = Math::Max(a.GetMin().y - b.GetCenter().y, 0.0f);
	dy = Math::Max(dy, b.GetCenter().y - a.GetMax().y);

	float distsq = dx * dx + dy * dy;
	return distsq <= (b.GetRadius() * b.GetRadius());

}