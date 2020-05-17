#pragma once
#include "GameObject.h"
class CEnemy :
	public CGameObject
{
public:
	CEnemy();
	LPANIMATION_SET disappearingAnimSet;

	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	void Render();
	void Disappear();
};

