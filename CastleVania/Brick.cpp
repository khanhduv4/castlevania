#include "Brick.h"

void CBrick::Render()
{
	RenderBoundingBox();
}

void CBrick::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = x + _width;
	b = y + _height;
}