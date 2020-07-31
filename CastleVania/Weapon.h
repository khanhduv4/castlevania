#pragma once

#include "Textures.h"
#include "Sprites.h" 
#include "GameObject.h"
#include "Game.h"
#include "Brick.h"
#include "Define.h"

#define WEAPON_SPEED_X 0.45f
#define WEAPON_SPEED_Y 0.45f

class Weapon : public CGameObject
{
protected:

	bool isFinish;
	int direction;
	int damage;
	int heart;
	DWORD LastTimeAttack; // Thời điểm tấn công cuối cùng 
	int currentFrame;

	bool isHit = 0;

public:
	Weapon();
	~Weapon();			  
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects , vector<LPGAMEOBJECT>* coItems);
	int GetDirection();
	int GetHeart() {
		return heart;
	}
	void SetDirection(int Direction);

	virtual void Attack(float X, float Y, int Direction);
  
  	
	virtual void Render(); 
	virtual void UpdatePositionFitSimon(); 
	virtual void RenderIcon(float X, float Y) = 0;
	
	void SetFinish(bool b);
	bool IsFinish() { return isFinish; }
	
	void SetHit(bool isHit);

	bool IsHit();

	DWORD GetLastTimeAttack(); 
};

