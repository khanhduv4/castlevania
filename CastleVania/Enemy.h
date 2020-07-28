#pragma once
#include "GameObject.h"
#include "Item.h"
class CEnemy :
	public CGameObject
{
public:
	CEnemy();
	int ani;
	int isEnable;
	int damage;
	bool isFront = false;
	int score;
	LPANIMATION_SET disappearingAnimSet;

	int isFlickering  = 0;

	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	void Render();
	void Disappear();
	void SubHealth(int th, vector<LPGAMEOBJECT>* coObjects, vector<LPGAMEOBJECT>* coItems);
	CItem* SpawnItem();
};

