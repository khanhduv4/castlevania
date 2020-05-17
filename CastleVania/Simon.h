#pragma once
#include "GameObject.h"
#include "MorningStar.h"

#define SIMON_WALKING_SPEED	0.12f 
//0.1f
#define SIMON_JUMP_SPEED_Y	0.27f
#define SIMON_JUMP_DEFLECT_SPEED 0.2f
#define SIMON_GRAVITY	0.0007f
#define SIMON_DIE_DEFLECT_SPEED	 0.5f

#define SIMON_STATE_IDLE	0
#define SIMON_STATE_WALKING	1
#define SIMON_STATE_JUMPING	2
#define SIMON_STATE_ATTACKING	3
#define SIMON_STATE_JUMPING_ATTACK	4
#define SIMON_STATE_SITTING	5

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
 
#define SIMON_ANI_DIE	99

#define SIMON_BBOX_WIDTH  32
#define SIMON_BBOX_HEIGHT 59
#define SIMON_BBOX_SITTING_HEIGHT 45
#define SIMON_BBOX_JUMPING_HEIGHT 45

#define SIMON_UNTOUCHABLE_TIME 5000


class CSimon : public CGameObject
{
	// Simon Spec
	int heart;
	int life;

	// Check state var
	bool isJumping;
	bool isAttacking;
	bool isSitting;
	bool isOnGround = 0;
	bool isDead;

	int untouchable;
	DWORD untouchable_start;

	MorningStar* morStar;
	Weapon* currentSubWeapon;

	float start_x;// initial position of Mario at scene
	float start_y; 
public: 
	CSimon(float x = 0.0f, float y = 0.0f);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL, vector<LPGAMEOBJECT>* coItems = NULL);
	virtual void Render();

	void SetState(int state);
	void setDirection(int direction);

	int getDirection();
	bool IsAttacking() { return isAttacking; }
	bool IsJumping () { return isJumping; }
	bool IsSitting() { return isSitting;  }

	void Attack();

	MorningStar* getMorningStar() {
		return morStar;
	}

	void setSitting(bool status);

	void setJumping(bool status);

	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }

	void Reset();

	void Idle();

	void AddHeart();

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};