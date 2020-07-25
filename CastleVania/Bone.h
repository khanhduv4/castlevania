#pragma once
#include "GameObject.h"
#include "Define.h"
#include "Simon.h"
class Bone : public CGameObject
{
private:
	int damage;
	int isBreak;
	Simon* simon;
	vector<LPGAMEOBJECT> objects;
public:
	Bone();
	~Bone();

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void SetState(int state);
};
