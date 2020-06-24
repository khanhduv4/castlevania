#pragma once
#include "Item.h"
class Money :
	public CItem
{
public:
	Money(float X = 0, float Y = 0);
	~Money();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

