#include "UpgradeMorningStar.h"

 

UpgradeMorningStar::UpgradeMorningStar(float X, float Y) 
{
	CAnimationSets* animation_sets = CAnimationSets::GetInstance();
	LPANIMATION_SET ani_set = animation_sets->Get(5);
	this->SetAnimationSet(ani_set);
	this->x = X;
	this->y = Y;

	vy = UPGRADEMORNINGSTAR_GRAVITY;
	
	TimeDisplayed = 0;
	TimeDisplayMax = UPGRADEMORNINGSTAR_TIMEDISPLAYMAX; // set time hiển thị tối đa
	TimeWaited = 0;
	TimeWaitMax = UPGRADEMORNINGSTAR_TIMEWAITMAX;

}

void UpgradeMorningStar::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + 46;
	bottom = y + 16;
}
 
 

UpgradeMorningStar::~UpgradeMorningStar()
{
}
