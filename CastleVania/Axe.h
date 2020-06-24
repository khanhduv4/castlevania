#pragma once
#include "Item.h"
class Axe :
	public CItem
{
public:
	Axe(float X = 0, float Y = 0);
	~Axe();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

