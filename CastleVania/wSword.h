#pragma once

#include "Weapon.h"

#define DAGGER_SPEED 0.45f

class wSword : 	public Weapon
{
private:
	//Camera * camera;
	bool isFinish;
public:
	wSword();
	~wSword();

	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);

	void Attack(float X, float Y, int Direction);

	void Render();

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);

 	void RenderIcon(float X, float Y);
	  

};