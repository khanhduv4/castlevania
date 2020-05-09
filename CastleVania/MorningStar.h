﻿#pragma once

#define MORNINGSTAR_TIME_WAIT_ANI 200 // thời gian chờ chuyển frame của MorningStar

#define MORNINGSTAR_ANI_LEVEL0_LEFT 0
#define MORNINGSTAR_ANI_LEVEL0_RIGHT 1
#define SIMON_WIDTH  32
#define SIMON_HEIGHT 59
#define SIMON_SITTING_HEIGHT 45
#define SIMON_JUMPING_HEIGHT 45

#include "Weapon.h"
#include "GameObject.h"



class MorningStar : public Weapon
{
protected:

	bool isActive;
	int level; 

	float leftBound;
	float topBound;
	float rightBound;
	float bottomBound;
public:
	MorningStar();
	~MorningStar();

	void SetActive(bool isVisible) { this->isActive = isVisible; }
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	void Render();

	bool IsActive() { return isActive; }

	void Attack(float X, float Y, int Direction);

	void ResetAnimation() {
		animation_set->at(0)->Reset();
		animation_set->at(1)->Reset(); 
		currentFrame = 0;
	}
	void SetActiveBoundingBox(bool isActive);
	void UpdatePositionFitSimon();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void RenderIcon(float X, float Y);

	void UpgradeLevel();
	int GetLevel();
	bool isCollision(CGameObject* obj);
};




