#pragma once
#include "GameObject.h"

#define TYPE_STAIR_BEGIN 1
#define TYPE_STAIR_END 2

class HiddenObject : public CGameObject
{

private:

public:
	int type = 0;
	int direction;
	int simonX;
	HiddenObject(int type);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void SetSize(int width, int  height) {
		_width = width;
		_height = height;
	}
};