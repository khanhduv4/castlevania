#pragma once
#include "Enemy.h"

class Raven : public Enemy
{
public:
	float startX, startY;
	int ny;

	//bool isStickToGround;
	//bool isIdle;
	//DWORD idleCast;

public:
	Raven(float startX, float startY, int hp, int damage, int point);
	~Raven();

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObject = NULL);
	virtual void Render();

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void SetState(int state);

	//virtual void CalcPotentialCollisions(vector<LPGAMEOBJECT>* coObjects, vector<LPCOLLISIONEVENT>& coEvents);
};

