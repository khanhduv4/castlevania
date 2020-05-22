#pragma once
#include "Enemy.h"

class Knight : public CEnemy
{
	float startX, startY;
public:
	Knight(int, int);
	~Knight();
	int ani;
	int maxXleft;
	int maxXright;

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObject = NULL);
	virtual void Render();

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void SetState(int state);
};

