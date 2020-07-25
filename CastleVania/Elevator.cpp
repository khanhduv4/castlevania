#include "Elevator.h"

Elevator::Elevator()
{
	SetAnimation(17);
	vx = ELEVATOR_SPEED;
}



void Elevator::Render()
{
		int ani = 0;
		animation_set->at(ani)->Render(x, y, 255);
		RenderBoundingBox();
}

void Elevator::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	x += dx;

	for (UINT i = 0; i < coObjects->size(); i++)
	{
		float l1, t1, r1, b1, l2, t2, r2, b2;
		GetBoundingBox(l1, t1, r1, b1);
		coObjects->at(i)->GetBoundingBox(l2, t2, r2, b2);

		if (isCollision(coObjects->at(i)))
		{
			if (dynamic_cast<CBrick*>(coObjects->at(i))) {
				x -= dx;
				vx = -vx;
				nx = -nx;
			}

		}
	}
}

void Elevator::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + _width;
	b = y + _height;
}