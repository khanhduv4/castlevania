#include "Blue.h"

Blue::Blue(float X, float Y)
{
	this->SetAnimation(15);
	this->x = X;
	this->y = Y;
	vy = ITEM_DEFAULT_GRAVITY;
}


Blue::~Blue()
{
}

void Blue::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + BLUE_WIDTH;
	bottom = y + BLUE_HEIGHT;
}
