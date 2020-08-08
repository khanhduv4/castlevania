#include "HiddenObject.h"
#include "Utils.h"

HiddenObject::HiddenObject(int type) {
	isCollisionWithSimon = 0;
	this->type = type;
}

void HiddenObject::Render()
{
	//RenderBoundingBox();
}

void HiddenObject::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + _width;
	b = y + _height;
}