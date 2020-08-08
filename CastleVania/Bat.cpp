#include "Bat.h"
#include "Simon.h"
#include "Define.h"
#include "Utils.h"

Bat::Bat()
{

	this->health = 1;
	isGravity = 0;
	isFinish = 0;

	isFront = true;
	damage = VAMPIRE_BAT_DAMAGE;

	SetAnimation(11);
	SetState(VAMPIRE_BAT_STATE_IDLE);
}

Bat::~Bat()
{
}

void Bat::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (isFinish) {
		left = 0;
		top = 0;
		right = left + 0;
		bottom = top + 0;
	}
	else {
		left = x;
		right = left + VAMPIRE_BAT_BBOX_WIDTH;
		top = y;
		bottom = top + VAMPIRE_BAT_BBOX_HEIGHT;
	}
}

void Bat::Update(DWORD dt, vector<LPGAMEOBJECT>* coObject)
{
	CEnemy::Update(dt, coObject);
	if (!isFinish) {

		x += dx;
		y += dy;

		float simonX, simonY;

		CSimon::GetInstance()->GetPosition(simonX, simonY);

		if (state == VAMPIRE_BAT_STATE_IDLE)
		if (abs(this->x - simonX) < VAMPIRE_BAT_DISTANCE_ATTACK_X && abs(this->y - simonY) < VAMPIRE_BAT_DISTANCE_ATTACK_Y) {
			SetState(VAMPIRE_BAT_STATE_FLYING);
		}

		if (state == VAMPIRE_BAT_STATE_FLYING)
		{
			//if (this->x - simonX > 100) {
			//	nx = -1;
			//	SetState(VAMPIRE_BAT_STATE_FLYING);
			//}
			//if (this->x - simonX < -100) {
			//	nx = 1;
			//	SetState(VAMPIRE_BAT_STATE_FLYING);

			//}
			if (y - simonY > 15)
			{
				vy = 0;
			}
		}
	}
}

void Bat::Render()
{
	if (!isFinish) {
		int ani = 0;
		switch (state)
		{
		case VAMPIRE_BAT_STATE_IDLE:
		{
			ani = VAMPIRE_BAT_ANI_IDLE;
		}
		break;
		case VAMPIRE_BAT_STATE_FLYING:
		{
			if (nx > 0) {
				ani = VAMPIRE_BAT_ANI_BLACK_FLYING_RIGHT;
			}
			else {
				ani = VAMPIRE_BAT_ANI_BLACK_FLYING_LEFT;
			}
		}
		break;
		default:
			ani = -1;
			break;
		}
		animation_set->at(ani)->Render(x, y, 255);

		//RenderBoundingBox();
	}
	CEnemy::Render();
}


void Bat::SetState(int state)
{
	CEnemy::SetState(state);

	switch (state)
	{
	case VAMPIRE_BAT_STATE_IDLE:
		break;
	case VAMPIRE_BAT_STATE_FLYING:
		if (nx == 1) {
			vx = VAMPIRE_BAT_FLYING_SPEED_X;
		}
		else {
			vx = -VAMPIRE_BAT_FLYING_SPEED_X;
		}
		vy = VAMPIRE_BAT_FLYING_SPEED_Y;
		break;
	}
}
