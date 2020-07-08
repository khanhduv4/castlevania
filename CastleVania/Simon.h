#pragma once
#include <algorithm>
#include <assert.h>
#include "define.h"
#include "Utils.h"
#include "GameObject.h"
#include "MorningStar.h"
#include "wSword.h"
#include "Sword.h"
#include "HiddenObject.h"
#include "Game.h"
#include "Torch.h"
#include "Brick.h"

#include "UpgradeMorningStar.h"
#include "LargeHeart.h"
#include "Portal.h"
#include "Elevator.h"


#define SIMON_WALKING_SPEED	0.12f 
#define SIMON_CLIMBING_SPEED 0.09f 

//0.1f
#define SIMON_JUMP_SPEED_Y	0.27f
#define SIMON_VJUMP_HURTING 0.15f
#define SIMON_JUMP_DEFLECT_SPEED 0.2f
#define SIMON_GRAVITY	0.0007f
#define SIMON_DIE_DEFLECT_SPEED	 0.5f

#define SIMON_BBOX_WIDTH  32
#define SIMON_BBOX_HEIGHT 59
#define SIMON_BBOX_SITTING_HEIGHT 45
#define SIMON_BBOX_JUMPING_HEIGHT 45

#define SIMON_UNTOUCHABLE_TIME 2000
#define SIMON_HURTING_TIME 400

#define SIMON_ATTACK_MAIN_WEAPON	0
#define SIMON_ATTACK_SUB_WEAPON	1


class CSimon : public CGameObject
{
	//Singleton
	static CSimon* _Instance;
	CSimon();
	// Simon Spec
	int heart;
	int life;
	int weapon;
	int untouchable;
	DWORD untouchable_start;

	HiddenObject* stair;

	MorningStar* morStar;
	Weapon* currentSubWeapon;

	int hurtingTimeCount = 0;

	float start_x;// initial position of Mario at scene
	float start_y;
public:
	bool isHurting;
	bool isJumping;
	bool isAttacking;
	bool isSitting;
	bool isSceneSwitching = false;
	bool isStair;
	bool isClimbableUp;
	bool isClimbableDown;
	bool isOnGround = 0;
	bool isDead;
	bool isClimbing;

	// Stair


	float startXStair;
	int directionOnStair;
	int stairDirection;
	int stairXDirection;
	int stairYDirection;


	// End stair

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

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL, vector<LPGAMEOBJECT>* coItems = NULL);
	virtual void Render();

	void SetState(int state);
	void Climbing(int);
	void setDirection(int direction);

	int getDirection();
	bool IsAttacking() { return isAttacking; }
	bool IsJumping() { return isJumping; }
	bool IsSitting() { return isSitting; }

	void Attack(int);

	MorningStar* getMorningStar() {
		return morStar;
	}

	void setSceneSwitching(bool value) {
		stair = NULL;
		isClimbing = 0;
		isClimbableUp = isClimbableDown = 0;
		this->isSceneSwitching = value;
	}

	void setSitting(bool status);

	void setJumping(bool status);

	void setWeapon(int weapon) { this->weapon = weapon; }

	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }

	void Reset();

	void ResetAttackAni();

	void UpdateHurting();

	void AddHeart();

	void InvertClimbDirection();

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);

	void SetHurt(LPCOLLISIONEVENT e);
};