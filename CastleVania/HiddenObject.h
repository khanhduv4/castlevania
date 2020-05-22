#pragma once
#include "GameObject.h"

#define TYPE_STAIR_LEFT_BEGIN 0
#define TYPE_STAIR_LEFT_END 1
#define TYPE_STAIR_RIGHT_BEGIN 2
#define TYPE_STAIR_RIGHT_END 3

class HiddenObject : public CGameObject
{

private:

public:
	int type = 0;
	int stairHeight;
	int direction;
	int simonX;
	HiddenObject(int type);
	void SetStairHeight(int);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void SetSize(int width, int  height) {
		_width = width;
		_height = height;
	}
};