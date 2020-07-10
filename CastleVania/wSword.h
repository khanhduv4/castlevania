#pragma once

#include "Weapon.h"

#define SWORD_SPEED 0.45f

class wSword : 	public Weapon
{

public:

	wSword();
	~wSword();

	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);

	void Attack(float X, float Y, int Direction);

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);

 	void RenderIcon(float X, float Y);
	  

};