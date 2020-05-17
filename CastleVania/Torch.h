#pragma once
#include "GameObject.h"
#include "Enemy.h"

#define TORCH_BBOX_WIDTH  32
#define TORCH_BBOX_HEIGHT 64

#define TORCH_ANI_BURNING 0
#define BURNING_ANI_OUT 1

#define TORCH_STATE_IDLE 0
#define TORCH_STATE_DIE 100

class CTorch : public CEnemy
{
public:
	bool isEnable;
public:
	CTorch();

	void SetEnable(bool en) { isEnable = en; }
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
};