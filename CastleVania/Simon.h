#pragma once
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

#define SIMON_STATE_IDLE	0
#define SIMON_STATE_WALKING	1
#define SIMON_STATE_JUMPING	2
#define SIMON_STATE_ATTACKING	3
#define SIMON_STATE_JUMPING_ATTACK	4
#define SIMON_STATE_SITTING	5
#define SIMON_STATE_ON_STAIR	6
#define SIMON_STATE_CLIMBING_UP	7
#define SIMON_STATE_CLIMBING_DOWN	8
#define SIMON_STATE_HURTING	9
#define SIMON_STATE_DIE	9

#define SIMON_ANI_IDLE_RIGHT		0
#define SIMON_ANI_IDLE_LEFT			1

#define SIMON_ANI_WALKING_RIGHT			2
#define SIMON_ANI_WALKING_LEFT			3

#define SIMON_ANI_JUMPING_LEFT	4
#define SIMON_ANI_JUMPING_RIGHT 5

#define SIMON_ANI_ATTACKING_LEFT	6
#define SIMON_ANI_ATTACKING_RIGHT	7

#define SIMON_ANI_SITTING_LEFT	8
#define SIMON_ANI_SITTING_RIGHT 9
#define SIMON_ANI_SITTING_ATTACK_LEFT	10
#define SIMON_ANI_SITTING_ATTACK_RIGHT	11

#define SIMON_ANI_STAIR_CLIMB_UP_RIGHT	12
#define SIMON_ANI_STAIR_CLIMB_UP_LEFT	14
#define SIMON_ANI_STAIR_IDLE_UP_RIGHT	13
#define SIMON_ANI_STAIR_IDLE_UP_LEFT	15
#define SIMON_ANI_STAIR_CLIMB_DOWN_RIGHT	16
#define SIMON_ANI_STAIR_CLIMB_DOWN_LEFT	18
#define SIMON_ANI_STAIR_IDLE_DOWN_RIGHT	17
#define SIMON_ANI_STAIR_IDLE_DOWN_LEFT	19
#define SIMON_ANI_STAIR_UP_ATTACK_RIGHT	20
#define SIMON_ANI_STAIR_UP_ATTACK_LEFT	21
#define SIMON_ANI_STAIR_DOWN_ATTACK_RIGHT	22
#define SIMON_ANI_STAIR_DOWN_ATTACK_LEFT	23

#define SIMON_ANI_HURTING 24
#define SIMON_ANI_DIE	99

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

	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }

	void Reset();

	void ResetAttackAni();

	void UpdateHurting();

	void AddHeart();

	void InvertClimbDirection();

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);

	void SetHurt(LPCOLLISIONEVENT e);
};