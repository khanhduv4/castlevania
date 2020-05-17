#include "LargeHeart.h"


 
LargeHeart::LargeHeart(float X, float Y)
{
	this->SetAnimation(7);
	this->x = X;
	this->y = Y;
	vy = ITEM_DEFAULT_GRAVITY;
	//TimeDisplayMax = LARGEHEART_TIMEDISPLAYMAX; // set time hiển thị tối đa
	//TimeDisplayed = 0;
	//TimeWaited = 0;
	//TimeWaitMax = LARGEHEART_TIMEWAITMAX;
}
 

LargeHeart::~LargeHeart()
{
}

void LargeHeart::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + 24;
	bottom = y + 20;
}
