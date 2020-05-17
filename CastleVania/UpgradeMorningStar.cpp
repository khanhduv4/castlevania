#include "UpgradeMorningStar.h"

 

UpgradeMorningStar::UpgradeMorningStar(float X, float Y) 
{
	this->SetAnimation(5);
	this->x = X;
	this->y = Y;

	vy = ITEM_DEFAULT_GRAVITY;
	
	//TimeDisplayed = 0;
	//TimeDisplayMax = UPGRADEMORNINGSTAR_TIMEDISPLAYMAX; // set time hiển thị tối đa
	//TimeWaited = 0;
	//TimeWaitMax = UPGRADEMORNINGSTAR_TIMEWAITMAX;
}



void UpgradeMorningStar::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (isFinish) {
		left = 0;
		top = 0;
		right = 0;
		bottom = 0;
	}
	left = x;
	top = y;
	right = x + 32;
	bottom = y + 32;
}
 
 

UpgradeMorningStar::~UpgradeMorningStar()
{
}
