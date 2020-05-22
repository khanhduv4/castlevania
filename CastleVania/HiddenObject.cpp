#include "HiddenObject.h"
#include "Utils.h"

HiddenObject::HiddenObject(int type) {
	this->type = type;
}

void HiddenObject::SetStairHeight(int height)
{
	stairHeight = height;
}

void HiddenObject::Render()
{
	 
	RenderBoundingBox();
}

void HiddenObject::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	 
	l = x;
	t = y;
	r = x + _width;
	b = y + _height;
}