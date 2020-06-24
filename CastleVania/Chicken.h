#pragma once
#include "Item.h"
class Chicken :
	public CItem
{
public:
	Chicken(float X = 0, float Y = 0);
	~Chicken();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

