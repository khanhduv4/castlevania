#include "BossItem.h"


 
BossItem::BossItem(float X, float Y)
{
	this->SetAnimation(23);
	this->x = X;
	this->y = Y;
	vy = ITEM_DEFAULT_GRAVITY;
}
 

BossItem::~BossItem()
{
}

void BossItem::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + 26;
	bottom = y + 32;
}
