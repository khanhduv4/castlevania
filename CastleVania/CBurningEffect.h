#pragma once
#include "GameObject.h"
class CBurningEffect :
	public CGameObject
{
public:
	CBurningEffect(float X = 0, float Y = 0);
	void Render();

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	~CBurningEffect();
};

