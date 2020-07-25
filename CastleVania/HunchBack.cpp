#include "Hunchback.h"
#include "Define.h"
#include "Simon.h"

Hunchback::Hunchback()
{
	this->startX = startX;
	this->startY = startY;
	this->damage = damage;
	this->distanceAttack = 100;
	this->Health = 1;

	timeJump = 0;
	isFront = true;

	SetAnimation(18);

	SetState(HUNCHBACK_STATE_IDLE);
}

Hunchback::~Hunchback()
{
}

void Hunchback::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CEnemy::Update(dt, coObjects);

	if (!isFinish)
	{
		float simonX, simonY;


		CSimon::getInstance()->GetPosition(simonX, simonY);

		nx = this->x >= simonX ? -1 : 1;
		if (state == HUNCHBACK_STATE_IDLE)
		{
			vy += HUNCHBACK_GRAVITY * dt;
		}

		if (state == HUNCHBACK_STATE_IDLE)
		{
			if (abs(this->x - simonX) <= this->distanceAttack)
			{
				SetState(HUNCHBACK_STATE_JUMP);
			}
		}
	}
}

void Hunchback::Render()
{
	if (!isFinish)
	{
		int ani = 0;
		switch (state)
		{
		case HUNCHBACK_STATE_IDLE:
		{
			if (nx > 0)
			{
				ani = HUNCHBACK_ANI_IDLE_RIGHT;
			}
			else
			{
				ani = HUNCHBACK_ANI_IDLE_LEFT;
			}
		}
		break;
		case HUNCHBACK_STATE_JUMP:
		case HUNCHBACK_STATE_ATTACK:
		{
			if (nx > 0)
			{
				ani = HUNCHBACK_ANI_ATTACK_RIGHT;
			}
			else
			{
				ani = HUNCHBACK_ANI_ATTACK_LEFT;
			}
		}
		break;
		default:
			break;
		}

		animation_set->at(ani)->Render(x, y);
	}
	else {
		int i = 1;
	}
	RenderBoundingBox();
	CEnemy::Render();
}

void Hunchback::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (isFinish)
	{
		left = 0;
		top = 0;
		right = left + 0;
		bottom = top + 0;
	}
	else
	{
		left = x;
		right = left + 32;
		top = y;
		bottom = top + 32;
	}
}

void Hunchback::SetState(int state)
{
	CEnemy::SetState(state);
	switch (state)
	{
	case HUNCHBACK_STATE_IDLE:
		break;
	case HUNCHBACK_STATE_JUMP:
		if (nx > 0)
		{
			vx = HUNCHBACK_JUMP_SPEED_X;
		}
		else
		{
			vx = -HUNCHBACK_JUMP_SPEED_X;
		}

		vy = HUNCHBACK_JUMP_SPEED_Y;
		break;
	case HUNCHBACK_STATE_ATTACK:
	{
		if (nx > 0)
		{
			vx = HUNCHBACK_SPEED_X;
		}
		else
		{
			vx = -HUNCHBACK_SPEED_X;
		}

		DWORD now = GetTickCount();

		if (timeJump == 0)
		{
			timeJump = now;
			vy = HUNCHBACK_SPEED_Y;
		}
		else if (now - timeJump >= 2000)
		{
			timeJump = now;
			vy = HUNCHBACK_SPEED_Y * 2;
		}
		else
		{
			vy = HUNCHBACK_SPEED_Y;
		}
	}
	break;
	}
}
