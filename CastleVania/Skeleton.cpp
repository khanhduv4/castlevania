#include "Skeleton.h"
#include "Define.h"
#include "Simon.h"
#include"Grid.h"

#define SKELETON_ATTACK_TIME 3000
#define SKELETON_MAX_MOVE 20
#define SKELETON_DISTANCE_ATTACK 200
#define SKELETON_SPEED_X 0.30f
#define SKELETON_SPEED_Y 0.45f

Skeleton::Skeleton()
{
	this->health = 2;
	SetAnimation(19);
	vy = 0;
	isFront = true;
	SetState(SKELETON_STATE_IDLE);
	distanceAttack = SKELETON_DISTANCE_ATTACK;
	isEnable = false;
	maxMove = SKELETON_MAX_MOVE;
	attackTime = SKELETON_ATTACK_TIME;
	jumpCount = 0;
	bones.clear();
}


Skeleton::~Skeleton()
{
}

void Skeleton::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

	CSimon* simon = CSimon::GetInstance();
	float simonX, simonY;
	simon->GetPosition(simonX, simonY);

	if (abs(this->x - simonX) < 500 && !isEnable) {
		direction = this->x < simonX ? 1 : -1;
		nx = direction;
	}

	if (abs(this->x - simonX) < distanceAttack && !isEnable) {
		isEnable = true;
		SetState(SKELETON_STATE_ATTACK);
	}

	if (!isFinish && isEnable)
	{

		for (int i = 0; i < bones.size(); i++) {
			bones[i]->Update(dt, coObjects);
		}

		//Nhay

		if (this->state == SKELETON_STATE_JUMP) {
			vy += SIMON_GRAVITY / 2;
			if (vy >= 0) {
				this->SetState(SKELETON_STATE_ATTACK);
				startX = x;
				startY = y;
			}
		}

		//Di chuyen qua lai va dut do


		if (this->state == SKELETON_STATE_ATTACK) {

			if (attackTime <= 0 && ((nx == direction && jumpCount % 2 == 1) || (nx != direction && jumpCount % 2 == 0))) {
				vx = 0;
				attackTime = SKELETON_ATTACK_TIME;
				this->SetState(SKELETON_STATE_JUMP);
				jumpCount++;
				if (jumpCount % 2 == 1)
					vx = direction * SKELETON_SPEED_X;
				else
					vx = -direction * SKELETON_SPEED_X;
				vy = -SKELETON_SPEED_Y;
			}
			else {
				vx = 0.05 * nx;
				if (abs(x - startX) >= maxMove) {
					nx = -(x > startX ? 1 : -1);
					ani = 0;
				}
				if (ceil(attackTime / 1000) != ceil((attackTime - dt) / 1000))
				{ 
					bones.push_back(new wBone(direction, x, y - 5));
				}
			}
			attackTime -= dt;

		}
	}

	CEnemy::Update(dt, coObjects);

}

void Skeleton::Render()
{
	if (!isFinish)
	{
		for (int i = 0; i < bones.size(); i++)
			bones[i]->Render();
		 
		int ani = 0;

		if (direction > 0)
		{
			ani = SKELETON_ANI_IDLE_RIGHT;
		}
		else
		{
			ani = SKELETON_ANI_IDLE_LEFT;
		}

		animation_set->at(ani)->Render(x, y, 255);
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
