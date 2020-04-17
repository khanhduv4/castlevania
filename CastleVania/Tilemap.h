#pragma once

#include <d3dx9.h>
#include <d3d9.h>
#include <vector>
#include <unordered_map> 
#include <iostream>
#include <fstream>
#include <string>

#include"Textures.h"
#include"Sprites.h"
#include "GameObject.h"
using namespace std;
 
struct Tile {
	int tileId;
	int type; // 0 = background, 1 = solid
	int x, y;
	int size;
};

typedef CGameObject* SolidTile;

typedef vector<SolidTile> SolidTileSet;

typedef vector<Tile> Row;
typedef vector<Row> Matrix;

class TiledMap
{
private:
	static TiledMap* __instance;
	TiledMap(string, string);

	void LoadMap(LPCWSTR , LPCWSTR);
	void LoadMatrix(LPCWSTR filePath);
	void LoadTileSet(LPCWSTR tilesLocation);

	

	Row GetMatrixRow(int lineNum, string line, string delimiter);

	Matrix matrix;

	int mapWidth, mapHeight;
	int tileSetSize;
	int tileSize;
	LPCWSTR infoLocation;

	unordered_map<int, CSprite*> tileSet;
public: 
	static TiledMap* GetCurrentMap(); 
	static TiledMap* Initialize(string infoPath, string tilesetPath);
	int GetWidth();
	int GetHeight(); 

	Matrix& GetMatrix() { return matrix; }


	void Update(DWORD dt);
	void Render();
	 

	~TiledMap();
};