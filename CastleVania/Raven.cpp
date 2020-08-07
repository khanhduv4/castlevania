#include "Raven.h"
#include "Define.h"
#include "Simon.h"

Raven::Raven()
{
	this->damage = 1;
	isEnable = false;
	isGravity = false;
	delayTime = RAVEN_ATTACK_DELAY_TIME;
	health = 1;
	distanceAttack = RAVEN_DISTANCE_ATTACK;
	SetState(RAVEN_STATE_IDLE);
}

Raven::~Raven()
{

}

void Raven::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{	
	float simonX, simonY;

	CSimon* simon = CSimon::GetInstance();

	simon->GetPosition(simonX, simonY);

	if (!isEnable && abs(simon->x - startX) < distanceAttack) {
		SetState(RAVEN_STATE_ATTACK);
		isEnable = true;
	}
	if (!isEnable || isFinish) return;
	CEnemy::Update(dt, coObjects);
	
	nx = simon->x - x;
	
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
		if(y <= simonY+10 )
			y += dt * vy;
		x += dt * vx;

		if (chaseTime <= 0) {
			isChasing = false;
			delayTime = (rand()) % 500 + 500;
		}

	}

}
 

void Raven::Render()
{
	if ( !isFinish) {
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

		//RenderBoundingBox();
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
}
