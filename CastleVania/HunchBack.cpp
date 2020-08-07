#include "Hunchback.h"
#include "Define.h"
#include "Simon.h"

Hunchback::Hunchback()
{
	this->damage = 3;
	this->distanceAttack = 100;
	this->health = 1;
	score = 500;
	nx = 1;

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

		CSimon::GetInstance()->GetPosition(simonX, simonY);


		DebugOut(L"NX: %d \n", nx);

		if (state == HUNCHBACK_STATE_IDLE)
		{
			if (abs(x - simonX) < ATTACK_DISTANCE) {
				jumpX = simonX;
				SetState(HUNCHBACK_STATE_JUMP);
			}
		}
		else if (state == HUNCHBACK_STATE_JUMP)
		{
			if (this->x - jumpX > 20)
			{
				SetState(HUNCHBACK_STATE_ATTACK);
			}
		}
		else if (state == HUNCHBACK_STATE_ATTACK) {
	
				nx = this->x >= simonX ? -1 : 1;

				SetState(HUNCHBACK_STATE_ATTACK);
			
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
			ani = -1;
			break;
		} 
		animation_set->at(ani)->Render(x, y, 255);

	}

	//RenderBoundingBox();
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

	}
	break;
	}
}
