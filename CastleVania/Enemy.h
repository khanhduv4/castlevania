#pragma once
#include "GameObject.h"
#include "Item.h"
class CEnemy :
	public CGameObject
{
public:
	CEnemy();
	int ani;
	bool isGrounded = false;
	int isEnable;
	int damage;
	float distanceAttack;
	float phantomDisappearingTime;
	bool isFront = false;
	int score;
	LPANIMATION_SET disappearingAnimSet;

	int isHurting2  = 0;

	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);

	void Render();
	void Disappear();
	void SubHealth(int th, vector<LPGAMEOBJECT>* coObjects, vector<LPGAMEOBJECT>* coItems);
	CItem* SpawnItem();
};

