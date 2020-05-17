#include "Sword.h"

Sword::Sword(float X, float Y)
{
	this->SetAnimation(8);
	this->x = X;
	this->y = Y;
	vy = ITEM_DEFAULT_GRAVITY;
	//TimeDisplayMax = LARGEHEART_TIMEDISPLAYMAX; // set time hiển thị tối đa
	//TimeDisplayed = 0;
	//TimeWaited = 0;
	//TimeWaitMax = LARGEHEART_TIMEWAITMAX;
}


Sword::~Sword()
{
}

void Sword::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + 32;
	bottom = y + 18;
}
