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
	void Insert(CGameObject* obj);
	void LoadObject(string line);
public:
	Grid(int cellSize, int numXCell, int numYCell, vector<LPGAMEOBJECT>* listObject);
	~Grid();
	void GetListOfObjects(vector<LPGAMEOBJECT>* list_object, int screenWidth, int screenHeight);
	void Unload();

	void UpdateGrid();
};

