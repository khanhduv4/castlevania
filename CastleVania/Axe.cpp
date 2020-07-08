#include "Axe.h"

Axe::Axe(float X, float Y)
{
	this->SetAnimation(12);
	this->x = X;
	this->y = Y;
	vy = ITEM_DEFAULT_GRAVITY;
}


Axe::~Axe()
{
}

void Axe::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + 30;
	bottom = y + 28;
}
