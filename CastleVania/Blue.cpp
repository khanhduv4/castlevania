﻿#include "Blue.h"

Blue::Blue(float X, float Y)
{
	this->SetAnimation(15);
	this->x = X;
	this->y = Y;
	vy = ITEM_DEFAULT_GRAVITY;
	//TimeDisplayMax = LARGEHEART_TIMEDISPLAYMAX; // set time hiển thị tối đa
	//TimeDisplayed = 0;
	//TimeWaited = 0;
	//TimeWaitMax = LARGEHEART_TIMEWAITMAX;
}


Blue::~Blue()
{
}

void Blue::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + 32;
	bottom = y + 32;
}
