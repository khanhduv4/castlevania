#pragma once
#include "Enemy.h"
class Zombie : public CEnemy
{
	int direction;

public:
	Zombie(int);
	~Zombie();

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	virtual void Render();

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void SetState(int state);
};