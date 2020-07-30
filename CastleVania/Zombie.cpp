#include "Zombie.h"
#include "Define.h"
#include "Simon.h"

Zombie::Zombie(int isEnable)
{
	this->Health = 1;
	this->damage = 2;
	this->isEnable = isEnable;
	SetState(ZOOMBIE_STATE_IDLE);
	this->isFront = true;
}

Zombie::~Zombie()
{
}

void Zombie::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CEnemy::Update(dt, coObjects);

	if (!isEnable) {
		//if (s)
	}
	else {
		if (!isFinish) {

			if (state != ZOOMBIE_STATE_WALKING) {

				float simonX, simonY;

				CSimon::getInstance()->GetPosition(simonX, simonY);

				nx = this->x >= simonX ? -1 : 1;

				SetState(ZOOMBIE_STATE_WALKING);
			}

		}
	}



}

void Zombie::Render()
{
	if (!isFinish && isEnable) {
		int ani = 0;
		switch (state)
		{
		case ZOOMBIE_STATE_WALKING:
		{
			if (nx > 0) {
				ani = ZOOMBIE_ANI_WALKING_RIGHT;
			}
			else {
				ani = ZOOMBIE_ANI_WALKING_LEFT;
			}
			break;
		}
		default:
			break;
		}

		animation_set->at(ani)->Render(x, y);
		//RenderBoundingBox();
	}

	CEnemy::Render();
}

void Zombie::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (isFinish || !isEnable) {
		left = 0;
		top = 0;
		right = left + 0;
		bottom = top + 0;
	}
	else {
		left = x;
		right = left + ZOOMBIE_BBOX_WIDTH;
		top = y;
		bottom = top + ZOOMBIE_BBOX_HEIGHT;
	}
}

void Zombie::SetState(int state)
{
	CEnemy::SetState(state);
	switch (state)
	{
	case ZOOMBIE_STATE_WALKING:
	{
		vx = nx * ZOOMBIE_WALKING_SPEED;
		break;
	}
	}
}
