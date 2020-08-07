#ifndef __ITEM_H__
#define __ITEM_H__

#include "GameObject.h" 
#include "define.h" 

#define ITEM_DEFAULT_GRAVITY 0.25f

class CItem : public CGameObject
{
protected: 
	int displayTime = 3000;
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

 
 
#endif // !__ITEM_H__




