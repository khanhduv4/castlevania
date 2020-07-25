#include "Skeleton.h"
#include "Define.h"
#include "Simon.h"

Skeleton::Skeleton()
{
	this->startX = startX;
	this->startY = startY;
	this->Health = 2;
	this->damage = damage;
	SetAnimation(19);
	vy = 0;
	isFront = true;

	SetState(SKELETON_STATE_IDLE);
}

Skeleton::~Skeleton()
{
}

void Skeleton::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CEnemy::Update(dt, coObjects);

	//if (Enemy::isStop)
	//{
	//	return;
	//}

	//if (!isDeadth && isEnable)
	//{

	//	vy += SIMON_GRAVITY * dt;

	//	float simonX, simonY;

	//	Simon::GetInstance()->GetPosition(simonX, simonY);

	//	nx = this->x >= simonX ? -1 : 1;

	//	if (abs(this->x - simonX) <= this->distanceAttack && abs(this->y - simonY) <= SIMON_BBOX_HEIGHT * 2)
	//	{

	//		if (state == SKELETON_STATE_IDLE)
	//		{
	//			SetState(SKELETON_STATE_ATTACK);
	//		}

	//		/*if (y > simonY) {
	//			SetState(SKELETON_STATE_ATTACK);
	//		}
	//		else {
	//			SetState(SKELETON_STATE_JUMP);
	//		}*/
	//	}
	//	else
	//	{
	//		SetState(SKELETON_STATE_IDLE);
	//	}

	//	if (state == SKELETON_STATE_ATTACK)
	//	{
	//		DWORD now = GetTickCount();
	//		if (timeAttack == 0)
	//		{
	//			timeAttack = now;
	//			Bone* bone = new Bone();
	//			bone->nx = nx;
	//			if (nx > 0)
	//			{
	//				bone->SetPosition(x + SKELETON_BBOX_WIDTH, y);
	//			}
	//			else
	//			{
	//				bone->SetPosition(x, y);
	//			}
	//			bones.push_back(bone);
	//			bone->SetState(BONE_STATE_FLY);
	//		}
	//		else if (now - timeAttack >= 1000)
	//		{
	//			timeAttack = now;
	//			Bone* bone = new Bone();
	//			if (nx > 0)
	//			{
	//				bone->SetPosition(x + SKELETON_BBOX_WIDTH, y);
	//			}
	//			else
	//			{
	//				bone->SetPosition(x, y);
	//			}
	//			bone->nx = nx;
	//			bones.push_back(bone);
	//			bone->SetState(BONE_STATE_FLY);
	//		}

	//		if (vx > 0 && abs(x - startX) > SKELETON_DISTANCE_X)
	//		{
	//			x = startX + SKELETON_DISTANCE_X;
	//			vx = -vx;
	//		}

	//		if (vx < 0 && x <= startX)
	//		{
	//			x = startX;
	//			vx = -vx;
	//		}
	//	}

	//	vector<LPCOLLISIONEVENT> coEvents;
	//	vector<LPCOLLISIONEVENT> coEventsResult;

	//	coEvents.clear();

	//	CalcPotentialCollisions(coObjects, coEvents);

	//	if (coEvents.size() == 0)
	//	{
	//		x += dx;
	//		y += dy;
	//	}
	//	else
	//	{
	//		float min_tx, min_ty, nx = 0, ny;
	//		float rdx = 0;
	//		float rdy = 0;

	//		// TODO: This is a very ugly designed function!!!!
	//		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

	//		// how to push back Mario if collides with a moving objects, what if Mario is pushed this way into another object?
	//		//if (rdx != 0 && rdx!=dx)
	//		//	x += nx*abs(rdx);

	//		// block every object first!

	//		for (UINT i = 0; i < coEventsResult.size(); i++)
	//		{
	//			LPCOLLISIONEVENT e = coEventsResult[i];

	//			if (dynamic_cast<Ground*>(e->obj)) // if e->obj is Goomba
	//			{
	//				x += min_tx * dx + nx * 0.7f;
	//				y += min_ty * dy + ny * 0.7f;

	//				if (nx != 0)
	//					vx = 0;
	//				if (ny != 0)
	//					vy = 0;
	//			}
	//		}
	//	}
	//}

	//for (int i = 0; i < bones.size(); i++)
	//{
	//	bones[i]->Update(dt, coObjects);
	//}
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
			break;
		}

		//if (CEnemy::isStop)
		//{
		//	if (nx > 0) {
		//		ani = SKELETON_ANI_IDLE_RIGHT;
		//	}
		//	else {
		//		ani = SKELETON_ANI_IDLE_LEFT;
		//	}
		//}

		animation_set->at(ani)->Render(posX, posY);
	}

	CEnemy::Render();

	//if (Enemy::isStop)
	//{
	//	return;
	//}

	//for (int i = 0; i < bones.size(); i++)
	//{
	//	bones[i]->Render();
	//}
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
		isFinish = true;

		break;
	case SKELETON_STATE_IDLE:
		break;
	case SKELETON_STATE_ATTACK:
		timeAttack = 0;

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
