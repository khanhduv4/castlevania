#include "Axe.h"

Axe::Axe(float X, float Y)
{
	this->SetAnimation(12);
	this->x = X;
	this->y = Y;
	vy = ITEM_DEFAULT_GRAVITY;
	//TimeDisplayMax = LARGEHEART_TIMEDISPLAYMAX; // set time hiển thị tối đa
	//TimeDisplayed = 0;
	//TimeWaited = 0;
	//TimeWaitMax = LARGEHEART_TIMEWAITMAX;
}


Axe::~Axe()
{
}

void Axe::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + 28;
	bottom = y + 13;
}
