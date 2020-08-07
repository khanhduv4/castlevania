#pragma once

#include"Enemy.h"

#define BONE_WIDTH 30
#define BONE_HEIGHT 32

#define BONE_SPEED_X 0.12f


class wBone : 	public CEnemy
{

public:

	wBone(int direction, float x , float y);
	~wBone();
 
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);

	void Render();
	 

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	 
};