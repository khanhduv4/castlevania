#pragma once
#include "Game.h"
#include "Textures.h"
#include "Scence.h"
#include "GameObject.h"
#include "Brick.h"
#include "Simon.h"
#include "MorningStar.h" 
#include "Grid.h"

class CPlayScene: public CScene
{
protected: 
	CSimon *player;// A play scene has to have player, right? 
	static CPlayScene* __instance;

	vector<LPGAMEOBJECT> objects;
	vector<LPGAMEOBJECT> items;

	Grid* _grid;
	 

	void _ParseSection_TEXTURES(string line);
	void _ParseSection_TILEMAP(string line);
	void _ParseSection_GRID(string line);
	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);
	void _ParseSection_ANIMATION_SETS(string line);
	void _ParseSection_OBJECTS(string line);

	
public: 
	CPlayScene(int id, LPCWSTR filePath);
	static CPlayScene* _getInstance(int id= 0, LPCWSTR filePath = NULL) {
		if (__instance == NULL) __instance = new CPlayScene(id, filePath);
		return __instance;
	}

	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	void CheckCollisionWeaponWithObject(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetNewItem(int x, int y, int id);
	virtual void Unload();

	CSimon * GetPlayer() { return player; } 

	//friend class CPlayScenceKeyHandler;
};

class CPlayScenceKeyHandler : public CScenceKeyHandler
{
public: 
	virtual void KeyState(BYTE *states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
	CPlayScenceKeyHandler(CScene *s) :CScenceKeyHandler(s) {};
};