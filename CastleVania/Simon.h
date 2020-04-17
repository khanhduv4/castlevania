#pragma once
#include "GameObject.h"

#define SIMON_WALKING_SPEED		0.15f 
//0.1f
#define SIMON_JUMP_SPEED_Y		0.5f
#define SIMON_JUMP_DEFLECT_SPEED 0.2f
#define SIMON_GRAVITY			0.002f
#define SIMON_DIE_DEFLECT_SPEED	 0.5f

#define SIMON_STATE_IDLE			0
#define SIMON_STATE_WALKING_RIGHT	100
#define SIMON_STATE_WALKING_LEFT	200
#define SIMON_STATE_JUMP			300
#define SIMON_STATE_DIE				400

#define SIMON_ANI_IDLE_RIGHT		0
#define SIMON_ANI_IDLE_LEFT			1

#define SIMON_ANI_WALKING_RIGHT			4
#define SIMON_ANI_WALKING_LEFT			5

#define SIMON_ANI_JUMPING_LEFT	6
#define SIMON_ANI_JUMPING_RIGHT 7

#define SIMON_ANI_DIE				8

#define SIMON_BBOX_WIDTH  32
#define SIMON_BBOX_HEIGHT 59

#define SIMON_UNTOUCHABLE_TIME 5000


class CSimon : public CGameObject
{
	bool isJumping; 
	int untouchable;
	DWORD untouchable_start;

	float start_x;			// initial position of Mario at scene
	float start_y; 
public: 
	CSimon(float x = 0.0f, float y = 0.0f);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	virtual void Render();

	void SetState(int state);

	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }

	void Reset();

	void LandOnGround();

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};