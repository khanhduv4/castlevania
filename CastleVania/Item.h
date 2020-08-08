#pragma once

#include "GameObject.h" 
#include "define.h" 

#define ITEM_DEFAULT_GRAVITY 0.25f
#define ITEM_DISPLAY_TIME 3000

class CItem : public CGameObject
{
protected: 
	int displayTime;
	DWORD TimeDisplayMax; // thời gian tối đa cho phép hiển thị.
	DWORD TimeDisplayed; // Thời gian đã hiển thị.

	DWORD TimeWaited; // Thời gian đã chờ trước khi hiển thị
	DWORD TimeWaitMax; // Thời gian tối đa phải chờ trước khi hiển thị
	float xBackup;
	bool isGrounded = false;

public:
	CItem();
	virtual ~CItem(); 
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *listObject = NULL);
	virtual void Render();
	virtual bool isWaitingDisplay(); // đang chờ object hiển thi? - simon chưa được ăn

};




