#pragma once
#include "Enemy.h"

#define RAVEN_WIDTH 33
#define RAVEN_HEIGHT 36

#define RAVEN_ATTACK_DELAY_TIME	200
#define RAVEN_DISTANCE_ATTACK	100

class Raven : public CEnemy
{
public: 
	long delayTime;
	long chaseTime;
	float aLine;
	float bLine;
	bool isChasing = false;
	
public:
	Raven();
	~Raven();

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObject = NULL);
 
	virtual void Render();

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void SetState(int state);

};

