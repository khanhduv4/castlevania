#pragma once
#include "Enemy.h"
//#include "Bone.h"
#include <vector>

//Skeleton
#define SKELETON_DISTANCE_X 30
#define SKELETON_DISTANCE_ATTACK_X 80

#define SKELETON_ANI_ATTACK_LEFT 2
#define SKELETON_ANI_ATTACK_RIGHT 3
#define SKELETON_ANI_IDLE_LEFT 0
#define SKELETON_ANI_IDLE_RIGHT 1

#define SKELETON_STATE_DIE 0
#define SKELETON_STATE_IDLE 1
#define SKELETON_STATE_ATTACK 2
#define SKELETON_STATE_JUMP 3

#define SKELETON_WALKING_SPEED 0.05f

#define SKELETON_BBOX_WIDTH 34
#define SKELETON_BBOX_HEIGHT 64

//bone
#define BONE_GRAVITY 0.0007f
#define BONE_DAMAGE 1

#define BONE_STATE_DIE 0
#define BONE_STATE_FLY 1
class Skeleton : public CEnemy
{
	float maxXRight, maxXLeft;
	float distanceAttack; 
	//vector<Bone *> bones;

public:
	Skeleton();
	~Skeleton();

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render();

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void SetState(int state);
};
