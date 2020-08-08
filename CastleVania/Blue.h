#pragma once
#include "Item.h"

#define BLUE_WIDTH 32
#define BLUE_HEIGHT 32

class Blue :
	public CItem
{
public:
	Blue(float X = 0, float Y = 0);
	~Blue();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

