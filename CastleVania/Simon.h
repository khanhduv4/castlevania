#pragma once
#include <algorithm>
#include <assert.h>
#include "define.h"
#include "Utils.h"
#include "GameObject.h"
#include "HiddenObject.h"
#include "Game.h"
#include "Torch.h"
#include "Brick.h"
#include "Portal.h"
#include "Elevator.h"
#include "GameBoard.h"
// Items
#include "UpgradeMorningStar.h"
#include "LargeHeart.h"
#include "SmallHeart.h"
#include "Sword.h"
#include "Boomerang.h"
#include "Axe.h"
#include "Blue.h"
//Weapons
#include "wSword.h"
#include "wAxe.h"
#include "wBoomerang.h"
#include "wBlue.h"
#include "MorningStar.h"

class CSimon : public CGameObject
{
	//Singleton
	static CSimon* _Instance;
	CSimon();

#pragma region Simon Spec
	int heart;
	int life;
	int score;
	int weapon;
	int untouchable;
	float start_x;
	float start_y;
#pragma endregion

#pragma region Weapon

	vector<Weapon*> subWeapons;
	MorningStar* morStar;
	int currentSubWeapon;
	Weapon* newSubWeapon();

#pragma endregion

#pragma region Time vars
	DWORD untouchable_start;
	int hurtingTimeCount = 0;
	int freezingTimeCount = 0;
	int dyingToDiedTime = 0;
#pragma endregion



public:

#pragma region Status Variable
	bool isHurting;
	bool isJumping;
	bool isAttacking;
	bool isSitting;
	bool isSceneSwitching;
	bool isStair;
	bool isClimbableUp;
	bool isClimbableDown;
	bool isOnGround = 0;
	bool isDead;
	bool isClimbing;
	bool isFreeze;
	bool isInnewScene;

#pragma endregion

#pragma region Stair

	float startXStair;
	int directionOnStair;
	int stairDirection;
	int stairXDirection;
	int stairYDirection;
	HiddenObject* stair;

#pragma endregion

#pragma region Get Methods

	static CSimon* GetInstance(float x, float y) {
		if (_Instance == NULL)
			_Instance = new CSimon();

		_Instance->start_x = x;
		_Instance->start_y = y;
		_Instance->x = x;
		_Instance->y = y;
		return _Instance;
	}
	static CSimon* GetInstance() {
		if (_Instance == NULL)
			_Instance = new CSimon();
		return _Instance;
	}
	int getCurrentSubWeapon() {
		return currentSubWeapon;
	}
	int getHealth() { return health; }
	int getHeart() { return heart; }
	int getLife() { return life; }
	int getScore() { return score; }
	bool IsAttacking() { return isAttacking; }
	bool IsJumping() { return isJumping; }
	bool IsSitting() { return isSitting; }
	int getDirection() { return nx; };
	bool IsSceneSwitching() { return isSceneSwitching; }
	bool IsInNewScene() { bool result = isInnewScene; isInnewScene = false; return result; }

	MorningStar* getMorningStar() {
		return morStar;
	}

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);

#pragma endregion

#pragma region Set methods

	void SetState(int state);

	void setSceneSwitching(bool value);

	void setDirection(int direction) {
		this->nx = direction;
	}

	void SetSitting(bool status);

	void setJumping(bool status) {
		isJumping = status;
	}

	void setWeapon(int weapon) { this->weapon = weapon; }

	void SetScore(int sco) { score += sco; }

	void SetResetPosition(float x, float y) {
		startX = x;
		startY = y;
	}

#pragma endregion

#pragma region Simon Action method

	void Attack(int);
	void Climbing(int);
	void Die();

#pragma endregion

#pragma region Simon Update Status, Props methods

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL, vector<LPGAMEOBJECT>* coItems = NULL);

	void HandleCollisionSimonWithItem(LPCOLLISIONEVENT e);

	virtual void Render();

	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }

	void UpdateHurting();

	void UpdateFreeze();

	void StartOver();

	void AddHeart(int);

	void SetHurt(LPCOLLISIONEVENT e);

	void SubHeart(int);

#pragma endregion

#pragma region Utils

	void Reset();
	void ResetAttackAni();

#pragma endregion


};