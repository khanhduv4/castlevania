#include "Raven.h"
#include "Define.h"
#include "Simon.h"

Raven::Raven()
{
	this->damage = 1;
	isEnable = true;
	isGravity = 0;
	delayTime = 200;
	SetState(RAVEN_STATE_IDLE);
}

Raven::~Raven()
{

}

void Raven::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	
	CEnemy::Update(dt, coObjects);
	float simonX, simonY;

	CSimon* simon = CSimon::GetInstance();
	
	simon->GetPosition(simonX, simonY);
	nx = simon->x - x;
	if (!isEnable && simon->x - startX < 200) {
		SetState(RAVEN_STATE_ATTACK);
		isEnable = true;
	}
	if (!isEnable) return;

	if (delayTime > 0) { delayTime -= dt; vx = 0; vy = 0; return; }
	else if (delayTime <= 0 && !isChasing) {
		isChasing = true;
		chaseTime = (rand()) % 700 + 500;
		
		vx = x > simon->x ? -0.05f - float(rand() % 10) / 20 : 0.05f + float(rand() % 10) / 20;
		vy = y < simon->y ? 0.05f + float(rand() % 10) / 20 : -0.05f - float(rand() % 10) / 20;
		vx /= 5;
		vy /= 5;
	}
	 
	if (isChasing) {
		chaseTime -= dt;
		x += dt * vx;
		y += dt * vy;
		//DebugOut(L"X Bat = %f Y Bat  = %f", x - startX, y);
		if (chaseTime <= 0) {
			isChasing = false;
			delayTime = (rand()) % 500 + 500;
		}

	}

}
 

void Raven::Render()
{
	if (isEnable) {
		int ani = 0;
		switch (state)
		{
		case RAVEN_STATE_IDLE:
		{
			if (nx > 0) {
				ani = RAVEN_ANI_IDLE_RIGHT;
			}
			else {
				ani = RAVEN_ANI_IDLE_LEFT;
			}
			break;
		}
		case RAVEN_STATE_FLY:
		case RAVEN_STATE_WAIT:
		case RAVEN_STATE_ATTACK:
		{
			if (nx > 0) {
				ani = RAVEN_ANI_FLY_RIGHT;
			}
			else {
				ani = RAVEN_ANI_FLY_LEFT;
			}
			break;
		}
		default:
			break;
		}
		animation_set->at(ani)->Render(x, y);

		RenderBoundingBox();
	}

	CEnemy::Render();
}

void Raven::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (isFinish) {
		left = 0;
		top = 0;
		right = left + 0;
		bottom = top + 0;
	}
	else {
		left = x;
		top = y;
		right = left + RAVEN_WIDTH;
		bottom = top + RAVEN_HEIGHT;
	}
}

void Raven::SetState(int state)
{
	CEnemy::SetState(state);
	//switch (state)
	//{
	//case RAVEN_STATE_DIE:
	//	//isDeadth = true;
	//	isEnable = false;
	//	break;
	//case RAVEN_STATE_IDLE:
	//	break;
	//case RAVEN_STATE_FLY:
	//	if (nx > 0) {
	//		vx = RAVEN_FLYING_SPEED_X;
	//	}
	//	else {
	//		vx = -RAVEN_FLYING_SPEED_X;
	//	}

	//	if (ny > 0) {
	//		vy = RAVEN_FLYING_SPEED_Y;
	//	}
	//	else {
	//		vy = -RAVEN_FLYING_SPEED_Y;
	//	}

	//	break;
	//case RAVEN_STATE_WAIT:
	//	timeWait = GetTickCount();
	//	vx = 0;
	//	vy = 0;
	//	break;
	//}
}
