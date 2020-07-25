#include "Bone.h"
#include "Define.h"

Bone::Bone()
{
	isEnable = true;
	damage = BONE_DAMAGE;

	simon = Simon::GetInstance();

	SetAnimationSet(771);
}

Bone::~Bone()
{
}

void Bone::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

	if (isEnable)
	{
		// Calculate dx, dy 
		CGameObject::Update(dt);

		// Simple fall down
		if (state != BONE_STATE_DIE)
			vy += BONE_GRAVITY * dt;


		objects.clear();
		objects.push_back(simon);

		vector<LPCOLLISIONEVENT> coEvents;
		vector<LPCOLLISIONEVENT> coEventsResult;

		coEvents.clear();

		CalcPotentialCollisions(&objects, coEvents);

		// No collision occured, proceed normally
		if (coEvents.size() == 0)
		{
			x += dx;
			y += dy;
		}
		else
		{
			float min_tx, min_ty, nx = 0, ny;
			float rdx = 0;
			float rdy = 0;

			bool isCollisionWithSimon = false;

			// TODO: This is a very ugly designed function!!!!
			FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

			// Collision logic with Goombas
			for (UINT i = 0; i < coEventsResult.size(); i++)
			{
				LPCOLLISIONEVENT e = coEventsResult[i];

				if (dynamic_cast<Simon*>(e->obj))
				{
					// block 
					x += min_tx * dx + nx * 0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
					y += min_ty * dy + ny * 0.4f;

					if (nx != 0) vx = 0;
					if (ny != 0) vy = 0;

					simon->Hurted(damage);
					isEnable = false;
					isCollisionWithSimon = true;
				}
			}
			if (!isCollisionWithSimon) {
				x += dx;
				y += dy;
			}
		}

		// clean up collision events
		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	}
	else {
		x = 0;
		y = 0;
	}
}

void Bone::Render()
{
	if (isEnable)
	{
		animation_set->at(0)->Render(x, y);
		RenderBoundingBox();
	}
}

void Bone::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (isEnable)
	{
		left = x;
		top = y;

		if (animation_set->at(0)->GetCurrentFrame() == 0) {
			right = left + 6;
			bottom = top + 16;
		}
		else {
			right = left + 15;
			bottom = top + 13;
		}
	}
	else {
		left = 0;
		top = 0;
		right = 0;
		bottom = 0;
	}
}

void Bone::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case BONE_STATE_FLY:
		vx = nx * 0.06;
		vy = -0.2;
		break;
	}
}
