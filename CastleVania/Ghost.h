#pragma once
#include "Enemy.h"

#define GHOST_ENABLE_SIMON_X 1000
#define GHOST_DISTANCE_MAX 50
class Ghost : public CEnemy
{
	float startX, startY;

public:
	Ghost();
	~Ghost();

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObject = NULL);
	virtual void Render();

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void SetState(int state);
};
