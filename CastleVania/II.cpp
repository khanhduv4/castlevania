#include "II.h"

II::II(float X, float Y)
{
	this->SetAnimation(16);
	this->x = X;
	this->y = Y;
	vy = ITEM_DEFAULT_GRAVITY;
}


II::~II()
{
}

void II::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + 42;
	bottom = y + 42;
}
