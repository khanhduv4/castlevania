#pragma once

#define MORNINGSTAR_TIME_WAIT_ANI 200 // thời gian chờ chuyển frame của MorningStar

#define MORNINGSTAR_ANI_LEVEL0_LEFT 0
#define MORNINGSTAR_ANI_LEVEL0_RIGHT 1
#define MORNINGSTAR_ANI_LEVEL1_LEFT 2
#define MORNINGSTAR_ANI_LEVEL1_RIGHT 3
#define MORNINGSTAR_ANI_LEVEL2_LEFT 4
#define MORNINGSTAR_ANI_LEVEL2_RIGHT 5

#define MORNINGSTAR_LV0_BBOX_WIDTH	46
#define MORNINGSTAR_LV0_BBOX_HEIGHT 16
#define MORNINGSTAR_LV2_BBOX_WIDTH	78
#define MORNINGSTAR_LV2_BBOX_HEIGHT 12

#define SIMON_WIDTH  32
#define SIMON_HEIGHT 59
#define SIMON_SITTING_HEIGHT 45
#define SIMON_JUMPING_HEIGHT 45

#include "Weapon.h"
#include "GameObject.h"




class MorningStar : public Weapon
{
protected:

	int level; 
	int ani;
	float leftBound;
	float topBound;
	float rightBound;
	float bottomBound;
	float simonX, simonY;

public:
	MorningStar();
	~MorningStar();


	void SetFinish(bool isVisible);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects, vector<LPGAMEOBJECT>* coItems);
	void Render();
	

	void Attack(float X, float Y, int Direction);

	void ResetAnimation();
	void SetActiveBoundingBox(bool isFinish);
	void UpdatePositionFitSimon();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void RenderIcon(float X, float Y);

	void UpgradeLevel();
	int GetLevel();
	bool isCollision(CGameObject* obj);
};




