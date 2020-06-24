#pragma once
#include "Item.h"
class Boomerang :
	public CItem
{
public:
	Boomerang(float X = 0, float Y = 0);
	~Boomerang();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

