#pragma once
#include "Enemy.h"

#define RAVEN_WIDTH 33
#define RAVEN_HEIGHT 36

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

	void makeLineLeftDown();

	void makeLineLeftDown(float simonX);

	void makeLineRightDown(float simonX);
	 
	
	void makeRandomLine();
	int calculateYLine(int x); 
	virtual void Render();

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void SetState(int state);

};

