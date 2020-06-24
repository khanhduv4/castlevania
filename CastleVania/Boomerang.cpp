#include "Boomerang.h"

Boomerang::Boomerang(float X, float Y)
{
	this->SetAnimation(14);
	this->x = X;
	this->y = Y;
	vy = ITEM_DEFAULT_GRAVITY;
}


Boomerang::~Boomerang()
{
}

void Boomerang::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + 30;
	bottom = y + 28;
}
