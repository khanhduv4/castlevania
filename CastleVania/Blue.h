#pragma once
#include "Item.h"
class Blue :
	public CItem
{
public:
	Blue(float X = 0, float Y = 0);
	~Blue();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

