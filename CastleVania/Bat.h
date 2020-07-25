#pragma once
#include "Enemy.h"

#define VAMPIRE_BAT_HP 1
#define VAMPIRE_BAT_DAMAGE 1

#define VAMPIRE_BAT_BBOX_WIDTH 32
#define VAMPIRE_BAT_BBOX_HEIGHT 32

#define VAMPIRE_BAT_STATE_IDLE 100
#define VAMPIRE_BAT_STATE_FLYING 200
#define VAMPIRE_BAT_STATE_DIE 300

#define VAMPIRE_BAT_ANI_IDLE 0
#define VAMPIRE_BAT_ANI_BLACK_FLYING_LEFT 1
#define VAMPIRE_BAT_ANI_BLACK_FLYING_RIGHT 2
#define VAMPIRE_BAT_ANI_RED_FLYING_LEFT 3
#define VAMPIRE_BAT_ANI_RED_FLYING_RIGHT 4
#define VAMPIRE_BAT_ANI_DIE 5

#define VAMPIRE_BAT_DISTANCE_ATTACK_X 150
#define VAMPIRE_BAT_DISTANCE_ATTACK_Y 100

#define VAMPIRE_BAT_FLYING_SPEED_X 0.13f
#define VAMPIRE_BAT_FLYING_SPEED_Y 0.05f

class Bat : public CEnemy
{
	float startX, startY;
	float xAttack, yAttack;

public:
	Bat();
	~Bat();

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObject = NULL);
	virtual void Render();

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void SetState(int state);
};

