#pragma once

#include "Weapon.h"

#define BLUE_WIDTH 32
#define BLUE_HEIGHT 26

#define BLUE_STATE_BOTTLE 1
#define BLUE_STATE_FIRE 2


class wBlue : public Weapon
{

public:

	wBlue();
	~wBlue();

	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects, vector<LPGAMEOBJECT>* coItem);

	void Attack(float X, float Y, int Direction);

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);

	void RenderIcon(float X, float Y);

	void Render();


};