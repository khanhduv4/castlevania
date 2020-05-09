#pragma once

#include "Textures.h"
#include "Sprites.h" 
#include "GameObject.h"




class Weapon : public CGameObject
{
protected:   

	bool isActive;
	int direction;  
	DWORD LastTimeAttack; // Thời điểm tấn công cuối cùng 
	int currentFrame;
public:
	Weapon();
	~Weapon();			  
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	int GetDirection();
	void SetDirection(int Direction);

	virtual void Attack(float X, float Y, int Direction);
  
  	
	virtual void Render(); 
	virtual void UpdatePositionFitSimon(); 
	virtual bool isCollision(CGameObject* obj); // kiểm tra vũ khí này có va chạm với object kia hay không?
	virtual void RenderIcon(float X, float Y) = 0;
	
	void SetFinish(bool b);
	  
	DWORD GetLastTimeAttack(); 
};

