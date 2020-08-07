#include "SmallHeart.h"
 
SmallHeart::SmallHeart(float X, float Y)
{
	this->SetAnimation(40);
	this->x = X;
	this->y = Y;
	xBackup = x;
	vy = ITEM_DEFAULT_GRAVITY;

}

void SmallHeart::Update(DWORD dt, vector<LPGAMEOBJECT>* listObject)
{
	timeAccu += dt;
	if (!isGrounded)
		vx = -30 * 2 * 3.14 * 1 / 1500 * sin(2 * 3.14 * 1 / 1500 * timeAccu + 3.14 / 2);
	else
		vx = 0;
	vy = 0.05f;

	CItem::Update(dt, listObject);
}
 

SmallHeart::~SmallHeart()
{
}

void SmallHeart::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + 24;
	bottom = y + 20;
}
