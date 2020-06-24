#pragma once
#include "Item.h"
class II :
	public CItem
{
public:
	II(float X = 0, float Y = 0);
	~II();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

