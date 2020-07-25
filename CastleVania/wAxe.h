#pragma once

#include "Weapon.h"

#define AXE_WIDTH 30
#define AXE_HEIGHT 28


class wAxe : 	public Weapon
{

public:

	wAxe();
	~wAxe();

	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);

	void Attack(float X, float Y, int Direction);

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);

 	void RenderIcon(float X, float Y);
	  

};