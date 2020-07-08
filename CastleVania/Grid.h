#pragma once
#include "GameObject.h"
#include <vector>
#include "Game.h"
#include "Cell.h"

class Grid
{
	friend class CGameObject;
	int cellSize;
	Cell** cells = NULL;
	int numXCells = 0;
	int numYCells = 0;
	vector <LPGAMEOBJECT>* listObject;
	void LoadSetting(string line);
	
	void LoadObject(string line);
	static Grid* _currentInstance;
public:
	void Insert(CGameObject* obj);
	Grid(int cellSize, int numXCell, int numYCell, vector<LPGAMEOBJECT>* listObject);
	~Grid();
	void GetListOfObjects(vector<LPGAMEOBJECT>* list_object, int screenWidth, int screenHeight);
	void Unload();
	static Grid* Create(int cellSize, int numXCell, int numYCell, vector<LPGAMEOBJECT>* listObject);
	static Grid* GetCurrentInstance();
	void UpdateGrid();
};

