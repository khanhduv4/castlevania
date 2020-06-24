#pragma once
#include "GameObject.h"
#include "Enemy.h"

#define CANDLE_BBOX_WIDTH  16
#define CANDLE_BBOX_HEIGHT 32

#define TORCH_ANI_BURNING 0

class Candle : public CEnemy
{
public:
	bool isEnable;
public:
	Candle();

	void SetEnable(bool en) { isEnable = en; }
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
};