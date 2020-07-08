#include "Grid.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Game.h"
#include "Utils.h"


using namespace std;

#define GRID_SECTION_UNKNOWN -1
#define GRID_SECTION_SETTINGS 0
#define GRID_SECTION_OBJECTS 2


 Grid* Grid::_currentInstance = NULL;
void Grid::LoadSetting(string line)
{
	vector<string> tokens = split(line);
	if (tokens.size() < 2)
	{
		return;
	}

	cellSize = atof(tokens[0].c_str());
	numXCells = atof(tokens[1].c_str());
	numYCells = atof(tokens[2].c_str());

	cells = new LPCELL[numXCells];

	for (int i = 0; i < numXCells; i++)
		cells[i] = new Cell[numYCells];
}

bool checkContainId(vector<LPGAMEOBJECT>* list_object, LPGAMEOBJECT e)
{
	LPGAMEOBJECT obj;
	for (int i = 0; i < list_object->size(); i++)
	{
		obj = list_object->at(i);
		if (obj->GetObjId() == e->GetObjId()) {
			return true;
		}
	}
	return false;
}
void Grid::Insert(CGameObject* obj)
{
	int top = (int)(obj->y / cellSize);
	int bottom = (int)((obj->y + obj->_height) / cellSize);
	int left = (int)(obj->x / cellSize);
	int right = (int)((obj->x + obj->_width) / cellSize);

	for (int i = left; i <= right; i++)
		for (int j = top; j <= bottom; j++)
			cells[i][j].Insert(obj);
}
void Grid::UpdateGrid() {
	//Get all grid objects
	vector<LPGAMEOBJECT> allGridObjects;
	for (int i = 0; i < numXCells; i++) {
		for (int j = 0; j < numYCells; j++)
		{
			vector<LPGAMEOBJECT> currentCellObjects = cells[i][j].GetListObjects();
			for (int k = 0; k < currentCellObjects.size(); k++) {
				LPGAMEOBJECT e = currentCellObjects[k];
				if (!checkContainId(&allGridObjects, e)) {
					allGridObjects.push_back(e);
				}
			}
		}
	}
	for (int i = 0; i < numXCells; i++)
		for (int j = 0; j < numYCells; j++)
		{
			cells[i][j].Unload();
		}

	for (int i = 0; i < allGridObjects.size(); i++) {
		Insert(allGridObjects[i]);
	}
}

Grid* Grid::Create(int cellSize, int numXCell, int numYCell, vector<LPGAMEOBJECT>* listObject) {
	_currentInstance = new Grid(cellSize, numXCell, numYCell, listObject);
	return _currentInstance;
}
Grid* Grid::GetCurrentInstance() {
	return _currentInstance;
}
void Grid::LoadObject(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 2)
	{
		return;
	}

	int indexX = atoi(tokens[0].c_str());
	int indexY = atoi(tokens[1].c_str());
	int idObject;

	for (int j = 2; j < tokens.size(); j++)
	{
		idObject = atoi(tokens[j].c_str());

		if (idObject == 2)
		{
			int i = 100;
		}
		cells[indexX][indexY].Insert(listObject->at(idObject));
	}
}

Grid::Grid(int cellSize, int numXCell, int numYCell, vector <LPGAMEOBJECT>* listObject)
{

	this->listObject = listObject;

	this->cellSize = cellSize;
	this->numXCells = numXCell;
	this->numYCells = numYCell;

	cells = new LPCELL[numXCells];

	for (int i = 0; i < numXCells; i++)
		cells[i] = new Cell[numYCells];


	for (int i = 0; i < listObject->size(); i++)
		this->Insert(listObject->at(i));

}



Grid::~Grid()
{

}



void Grid::GetListOfObjects(vector<LPGAMEOBJECT>* list_object, int screenWidth, int screenHeight)
{
	float cx = 0, cy = 0;
	CGame::GetInstance()->GetCamPos(cx, cy);
	//DebugOut(L"cx=%f cy=%f", cx, cy);
	list_object->clear();
	int left, top, right, bottom;
	int i, j, k;

	left = (int)cx / cellSize;
	top = (int)cy / cellSize;

	right = (int)(cx + screenWidth) / cellSize
		+ ((int)(cx + screenWidth) % cellSize ? 1 : 0);

	bottom = (int)(cy + screenHeight) / cellSize
		+ ((int)(cy + screenHeight) % cellSize ? 1 : 0);

	LPGAMEOBJECT e;

	if (right < 0 || left > numXCells || bottom < 0 && top > numYCells)
	{
		return;
	}

	if (right > numXCells)
	{
		right = numXCells;
	}
	if (bottom > numYCells)
	{
		bottom = numYCells;
	}

	if (left < 0)
	{
		left = 0;
	}
	if (top > 0)
	{
		top = 0;
	}

	LPCELL cell;
	for (i = left; i < right; i++)
	{
		for (j = top; j < bottom; j++)
		{
			LPCELL cell = &cells[i][j];
			if (cell)
			{
				if (cells[i][j].GetListObjects().size() != 0)
				{
					for (k = 0; k < cells[i][j].GetListObjects().size(); k++)
					{
						e = cells[i][j].GetListObjects().at(k);
						if (!checkContainId(list_object, e)) {
							list_object->push_back(e);
						}
					}
				}
			}

		}
	}

}

void Grid::Unload()
{
	if (cells)
	{
		for (int i = 0; i < numXCells; i++)
		{
			for (int j = 0; j < numYCells; j++)
			{
				cells[i][j].Unload();
			}
		}
		delete cells;
		cells = NULL;
	}
}

