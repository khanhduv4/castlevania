#include "Skeleton.h"
#include "Define.h"
#include "Simon.h"

Skeleton::Skeleton()
{
	this->Health = 2;
	this->damage = damage;
	SetAnimation(19);
	vy = 0;
	isFront = true;
	SetState(SKELETON_STATE_IDLE);
	distanceAttack = 100;
	maxXLeft = 0;
	maxXRight = 200;
}


Skeleton::~Skeleton()
{
}

void Skeleton::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	
	if (!isFinish && isEnable)
	{
		vx = 0.07f * nx;
		if (nx == 1) {
			if (x >= maxXRight) {
				nx = -nx;
				ani = 0;
			}
		}
		else {
			if (x <= maxXLeft) {
				ani = 1;
				nx = -nx;
			}
		}
		
	}

	CEnemy::Update(dt, coObjects);

}

void Skeleton::Render()
{
	if (!isFinish)
	{
		int posX = x, posY = y;
		int ani = 0;
		switch (state)
		{
		case SKELETON_STATE_IDLE:
		{
			if (nx > 0)
			{
				ani = SKELETON_ANI_IDLE_RIGHT;
			}
			else
			{
				ani = SKELETON_ANI_IDLE_LEFT;
			}
			break;
		}
		case SKELETON_STATE_ATTACK:
		{
			if (nx > 0)
			{
				ani = SKELETON_ANI_ATTACK_RIGHT;
			}
			else
			{
				ani = SKELETON_ANI_ATTACK_LEFT;
			}
			break;
		}
		default:
			ani = -1;
			break;
		}
		animation_set->at(0)->Render(x, y, 255);

	}

	CEnemy::Render();

}

void Skeleton::GetBoundingBox(float& left, float& top, float& right, float& bottom)
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
		right = left + SKELETON_BBOX_WIDTH;
		top = y;
		bottom = top + SKELETON_BBOX_HEIGHT;
	}
}

void Skeleton::SetState(int state)
{
	CEnemy::SetState(state);
	switch (state)
	{
	case SKELETON_STATE_DIE:

		isFinish = false;
		break;
	case SKELETON_STATE_IDLE:
		break;
	case SKELETON_STATE_ATTACK:
		//timeAttack = 0;

		if (nx > 0)
		{
			vx = SKELETON_WALKING_SPEED;
		}
		else
		{
			vx = -SKELETON_WALKING_SPEED;
		}
		break;
	}
}
