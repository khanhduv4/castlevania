#ifndef __ITEM_H__
#define __ITEM_H__

#include "GameObject.h" 
#include "define.h" 

class CItem : public CGameObject
{
protected: 

	DWORD TimeDisplayMax; // thời gian tối đa cho phép hiển thị.
	DWORD TimeDisplayed; // Thời gian đã hiển thị.

	DWORD TimeWaited; // Thời gian đã chờ trước khi hiển thị
	DWORD TimeWaitMax; // Thời gian tối đa phải chờ trước khi hiển thị

	bool isFinish; // đã kết thúc chưa?

public:
	CItem();
	virtual ~CItem(); 
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *listObject = NULL);
	virtual void Render();
	virtual bool isWaitingDisplay(); // đang chờ object hiển thi? - simon chưa được ăn
 
 	bool GetFinish();
	void SetFinish(bool b);
};

 
 
#endif // !__ITEM_H__




