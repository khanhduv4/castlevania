#pragma once
#include "GameObject.h"

#define TORCH_BBOX_WIDTH  32
#define TORCH_BBOX_HEIGHT 16

#define TORCH_ANI_BURNING 0

#define TORCH_STATE_IDLE 0
#define TORCH_STATE_DIE 100

class CTorch : public CGameObject
{
public:
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};