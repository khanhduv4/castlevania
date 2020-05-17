#pragma once
#include "Item.h"
class Sword :
	public CItem
{
public:
	Sword(float X = 0, float Y = 0);
	~Sword();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

