#pragma once

#include "Textures.h"
#include "Sprites.h" 
#include "GameObject.h"

class Weapon : public CGameObject
{
protected:

	bool isFinish;
	int direction;
	int damage;
	DWORD LastTimeAttack; // Thời điểm tấn công cuối cùng 
	int currentFrame;

	bool isHit = 0;

public:
	Weapon();
	~Weapon();			  
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects , vector<LPGAMEOBJECT>* coItems);
	int GetDirection();
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

