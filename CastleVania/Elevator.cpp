#include "Elevator.h"

Elevator::Elevator()
{
	SetAnimation(17);
}

void Elevator::Render()
{

		int ani = 0;
		animation_set->at(ani)->Render(x, y, 255);
		RenderBoundingBox();

}

void Elevator::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + 64;
	b = y + 18;
}