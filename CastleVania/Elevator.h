#pragma once
#include "GameObject.h"
#include "Brick.h"

#define ELEVATOR_SPEED 0.05f;

class Elevator : public CGameObject
{
private:

public:
	Elevator();
	void GetSpeed(float& vx, float& vy) {
		vx = this->vx;
		vy = this->vy;
	}
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObject);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void SetSize(int width, int  height) {
		_width = width;
		_height = height;
	}
};