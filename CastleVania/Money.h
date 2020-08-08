#pragma once
#include "Item.h"
class Money :
	public CItem
{
	int score;
public:
	int GetScore() { return score; }
	Money(float X = 0, float Y = 0);
	~Money();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Render();
	void SetFinish(bool b);
};

