#pragma once
#include "GameObject.h"
 

class CBrick : public CGameObject
{
private: 

public:
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void SetSize(int width,int  height) {
		_width = width;
		_height = height;
	}
};