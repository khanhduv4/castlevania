#include "Money.h"

Money::Money(float X, float Y)
{
	score = 100;
	this->SetAnimation(41);
	this->x = X;
	this->y = Y;
	vy = ITEM_DEFAULT_GRAVITY;
}


Money::~Money()
{
}

void Money::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + 30;
	bottom = y + 30;
}

void Money::Render() {
	CItem::Render();
	if (displayTime > 0 && isFinish) {

		animation_set->at(1)->Render(x, y);
	}
}

void Money::SetFinish(bool b)
{
	isFinish = b;
	displayTime = 1000;
}