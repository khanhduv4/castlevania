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
#include "Sword.h"
#include "Boomerang.h"
#include "Axe.h"

//Weapons
#include "wSword.h"
#include "wAxe.h"
#include "wBoomerang.h"
#include "MorningStar.h"

#define SIMON_ATTACK_MAIN_WEAPON	0
#define SIMON_ATTACK_SUB_WEAPON	1


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

	DWORD untouchable_start;
	int hurtingTimeCount = 0;
	int freezingTimeCount = 0;

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

	static CSimon* getInstance(float x, float y) {
		if (_Instance == NULL)
			_Instance = new CSimon();

		_Instance->start_x = x;
		_Instance->start_y = y;
		_Instance->x = x;
		_Instance->y = y;
		return _Instance;
	}
	static CSimon* getInstance() {
		if (_Instance == NULL)
			_Instance = new CSimon();
		return _Instance;
	}
	int getCurrentSubWeapon() {
		return currentSubWeapon;
	}
	int getHealth() { return Health; }
	int getHeart() { return heart; }
	int getLife() { return life; }
	int getScore() { return score; }
	bool IsAttacking() { return isAttacking; }
	bool IsJumping() { return isJumping; }
	bool IsSitting() { return isSitting; }
	int getDirection() { return nx; };

	MorningStar* getMorningStar() {
		return morStar;
	}

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);

#pragma endregion

#pragma region Set methods
	void SetState(int state);

	void setSceneSwitching(bool value) {
		stair = NULL;
		isClimbing = 0;
		isClimbableUp = isClimbableDown = 0;
		this->isSceneSwitching = value;
	}

	void setDirection(int direction) {
		this->nx = direction;
	}

	void SetSitting(bool status);

	void setJumping(bool status) {
		isJumping = status;
	}

	void setWeapon(int weapon) { this->weapon = weapon; }

#pragma endregion

#pragma region Simon Action method
	void Attack(int);
	void Climbing(int);

#pragma endregion

#pragma region Simon Update Status methods

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL, vector<LPGAMEOBJECT>* coItems = NULL);

	virtual void Render();

	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }

	void Reset();

	void HandleCollisionSimonWithItem(LPCOLLISIONEVENT e);

	void ResetAttackAni();

	void UpdateHurting();

	void UpdateFreeze();

	void AddHeart(int);

	void SetHurt(LPCOLLISIONEVENT e);

#pragma endregion

};