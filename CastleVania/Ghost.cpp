#include "Ghost.h"
#include "Define.h"
#include "Simon.h"

Ghost::Ghost()
{
	this->startX = startX;
	this->startY = startY;
	this->Health = 2;
	isGravity = 0;
	isEnable = 0;
	isFinish = 0;
	SetAnimation(20);
	isFront = true;
}

Ghost::~Ghost()
{
}

void Ghost::Update(DWORD dt, vector<LPGAMEOBJECT>* coObject)
{
	CEnemy::Update(dt, coObject);


	float simonX, simonY;

	CSimon::getInstance()->GetPosition(simonX, simonY);

	if (simonX < GHOST_ENABLE_SIMON_X && !isEnable) {
		isEnable = 1;
		SetState(GHOST_STATE_FLYING);
	}

	if (!isFinish && isEnable)
	{
		x += dx;
		y += dy;


		if (state == GHOST_STATE_FLYING) {
			if (this->x - simonX > 50) {
				nx = -1;
				SetState(GHOST_STATE_FLYING);
			}
			if (this->x - simonX < -50) {
				nx = 1;
				SetState(GHOST_STATE_FLYING);

			}
		}

	}
}

void Ghost::Render()
{
	if (!isFinish && isEnable)
	{
		int ani = 0;
		switch (state)
		{
		case GHOST_STATE_WAITTING:
		case GHOST_STATE_FLYING:
		{
			if (nx > 0)
			{
				ani = GHOST_ANI_FLYING_RIGHT;
			}
			else
			{
				ani = GHOST_ANI_FLYING_LEFT;
			}
		}
		break;
		default:
			break;
		}

		animation_set->at(ani)->Render(x, y);
	}
	//RenderBoundingBox();
	CEnemy::Render();
}

void Ghost::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (isFinish || !isEnable)
	{
		left = 0;
		top = 0;
		right = left + 0;
		bottom = top + 0;
	}
	else
	{
		left = x;
		right = left + GHOST_BBOX_WIDTH;
		top = y;
		bottom = top + GHOST_BBOX_HEIGHT;
	}
}

void Ghost::SetState(int state)
{
	CEnemy::SetState(state);
	switch (state)
	{
	case GHOST_STATE_DIE:
		break;
	case GHOST_STATE_HIDE:
		break;
	case GHOST_STATE_FLYING:
		if (nx > 0)
		{
			vx = GHOST_FLYING_SPEED_X;
		}
		else
		{
			vx = -GHOST_FLYING_SPEED_X;
		}
		break;
	case GHOST_STATE_WAITTING:
		vx = 0;
		break;
	}
}
