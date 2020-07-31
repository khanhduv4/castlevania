#pragma once
#include "Enemy.h"

#define HUNCHBACK_STATE_IDLE 0
#define HUNCHBACK_STATE_JUMP 1
#define HUNCHBACK_STATE_ATTACK 2

#define ATTACK_DISTANCE 200


#define HUNCHBACK_ANI_IDLE_LEFT 1
#define HUNCHBACK_ANI_IDLE_RIGHT 3
#define HUNCHBACK_ANI_ATTACK_LEFT 1
#define HUNCHBACK_ANI_ATTACK_RIGHT 3
#define HUNCHBACK_GRAVITY 0.00055f

#define HUNCHBACK_SPEED_X 0.03f
#define HUNCHBACK_SPEED_Y 0.06f

#define HUNCHBACK_JUMP_SPEED_X 0.3f

class Hunchback : public CEnemy
{
	float jumpX;
	float distanceAttack;

	DWORD timeJump;

public:
	Hunchback();
	~Hunchback();

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	virtual void Render();

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void SetState(int state);
};
