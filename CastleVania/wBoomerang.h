#pragma once

#include "Weapon.h"

#define BOOMERANG_WIDTH 28
#define BOOMERANG_HEIGHT 28


class wBoomerang : 	public Weapon
{

public:

	wBoomerang();
	~wBoomerang();

	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);

	void Attack(float X, float Y, int Direction);

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);

 	void RenderIcon(float X, float Y);
	  

};