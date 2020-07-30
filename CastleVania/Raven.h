#pragma once
#include "Enemy.h"

class Raven : public CEnemy
{
public:
	float startX, startY;
	float distanceAttack;
	int ny;

	DWORD timeWait;

public:
	Raven();
	~Raven();

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObject = NULL);
	virtual void Render();

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void SetState(int state);

};

