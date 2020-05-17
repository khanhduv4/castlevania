#include "Bat.h"
#include "Define.h"
#include "Utils.h"


Bat::Bat()
{
	//this->startX = startX;
	//this->startY = startY;

	//this->hp = VAMPIRE_BAT_HP;
	//isEnable = true;

	//SetState(VAMPIRE_BAT_STATE_IDLE);
	SetAnimation(11);
	this->Health = 2;

	isFinish = 0;
}

Bat::~Bat()
{
}

void Bat::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{

		left = 0;
		top = 0;
		right = left + isFinish ? 0 : 32;
		bottom = top + isFinish ? 0 : 32;

}

void Bat::Update(DWORD dt, vector<LPGAMEOBJECT>* coObject)
{
	//CEnemy::Update(dt, coObject);


	//if (!isFinish) {
	//	x += dx;
	//	y += dy;

	//	float simonX, simonY;


	//	nx = this->x >= simonX ? -1 : 1;

	//	if (state == VAMPIRE_BAT_STATE_FLYING)
	//	{
	//		x += dx;
	//		y += dy;
	//		if (this->y - simonY >= SIMON_BBOX_HEIGHT / 2 - 5)
	//		{
	//			vy = 0;
	//			y = simonY + SIMON_BBOX_HEIGHT / 2 - 5;
	//		}
	//	}
	//	else if (state == VAMPIRE_BAT_STATE_IDLE) {
	//		if (abs(this->x - simonX) < VAMPIRE_BAT_DISTANCE_ATTACK_X && abs(this->y - simonY) < SIMON_BBOX_HEIGHT) {
	//			SetState(VAMPIRE_BAT_STATE_FLYING);
	//		}
	//	}
	//}
}

void Bat::Render()
{
	/*if (!isDeadth) {
		int posX = x, posY = y;
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
			break;
		}

		animation_set->at(ani)->Render(posX, posY);
		RenderBoundingBox();
	}

	Enemy::Render();*/
	animation_set->at(0)->Render(x, y);
	//RenderBoundingBox();
}


void Bat::SetState(int state)
{
	//Enemy::SetState(state);
	//switch (state)
	//{
	//case VAMPIRE_BAT_STATE_IDLE:
	//	break;
	//case VAMPIRE_BAT_STATE_FLYING:
	//	if (nx > 0) {
	//		vx = BLACK_KNIGHT_FLYING_SPEED_X;
	//	}
	//	else {
	//		vx = -BLACK_KNIGHT_FLYING_SPEED_X;
	//	}

	//	vy = BLACK_KNIGHT_FLYING_SPEED_y;
	//	break;
	//}
}
