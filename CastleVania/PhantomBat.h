#pragma once
#include "Enemy.h"
//#include "BossDeadEffect.h"
class PhantomBat : public CEnemy
{
	float startX, startY;
	//BossDeadEffect* bossDeadEffect;

	D3DXVECTOR2 random;
	D3DXVECTOR2 simonPos;
	D3DXVECTOR2 batPos;
	float ny;
	float nx;
	float distance;
	bool isFlyToRandomPos;
	bool isFlyToSimonPos;
	float waitTime;
	float hurtTime;
	long delayTime;
	int previousHP;
	float introTime;
	long chaseTime;
	bool isTest = false;
	float refX = -1, refY = -1;
	bool isHurted;
	float distanceAttack;
	bool isChasing = false;
	float aCurve, bCurve, cCurve;

public:
	PhantomBat();
	~PhantomBat();

	void makeRandomCurve();
	 
	int calculateYCurve(int x);
	 
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	virtual void Render();

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void SetState(int state);


	void SubHealth(int th);
	void CalculateSimonPos(DWORD dt);
	void Fly(DWORD dt);
	void RandomPos();
	bool Intro(DWORD dt);
	void CheckHPChange();
	void CheckHurtTime(DWORD dt);
	void FlyToRandomPos(DWORD dt);
};
