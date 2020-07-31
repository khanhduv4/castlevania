#pragma once

#include "Weapon.h"

#include "Simon.h"

#define BOOMERANG_WIDTH 28
#define BOOMERANG_HEIGHT 28
#define	BOOMERANG_MAX_DISTANCE 210


class wBoomerang : 	public Weapon
{

public:

	wBoomerang();
	~wBoomerang();

	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects, vector<LPGAMEOBJECT>* coItems);

	 

	void Attack(float X, float Y, int Direction);

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);

 	void RenderIcon(float X, float Y);
	  

};